#ifndef _TREE_HPP
#define _TREE_HPP

#include <algorithm>
#include <memory>
#include "iterator.hpp"
#include "utils.hpp"
#include "color.hpp"

namespace ft {
    enum Color {
        RED,
        BLACK
    };

    template<typename T>
    struct TreeNode {
        T value;
        Color color;
        struct TreeNode *left;
        struct TreeNode *right;
        struct TreeNode *parent;
    };  // TreeNode


    template <typename T, bool IsConst = false>
    class TreeIterator {
    public:
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef typename ft::conditional<IsConst, const T *, T *>::type pointer;
        typedef typename ft::conditional<IsConst, const T &, T &>::type reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef TreeNode<T> node_type;
        typedef node_type* node_ptr;

    protected:
        node_ptr _ptr;

    public:
        TreeIterator() : _ptr(NULL) {}
        TreeIterator(const node_ptr other) : _ptr(other) {}

        //todo diff here
//        TreeIterator(const TreeIterator& other) : _ptr(const_cast<node_ptr>(other._ptr)) { }

        template<bool B>
        TreeIterator(const TreeIterator<T, B> &other, typename ft::enable_if<!B>::type* = 0) : _ptr(other._ptr) {}

        TreeIterator& operator=(TreeIterator const &other) {
            this->_ptr = other._ptr;
            return *this;
        }

        ~TreeIterator() {}

        reference operator*() const { return static_cast<reference>(_ptr->value); }
        pointer operator->() const { return &(_ptr->value); }

        TreeIterator& operator++() {
            _ptr = successor(_ptr);
            return *this;
        }
        TreeIterator& operator--() {
            _ptr = predecessor(_ptr);
            return *this;
        }

        TreeIterator operator++(int) {
            TreeIterator tmp = *this;
            _ptr = successor(_ptr);
            return tmp;
        }
        TreeIterator operator--(int) {
            TreeIterator tmp = *this;
            _ptr = predecessor(_ptr);
            return tmp;
        }

        /* find the predecessor of a given node */
        node_ptr predecessor (node_ptr x) const {
            if (x->left)
                return maxNode(x->left);
            node_ptr prev = x;
            node_ptr tmp = x->parent;
            while (prev == tmp->left) {
                if (prev == tmp)
                    return tmp;
                prev = tmp;
                tmp = tmp->parent;
            }
            return tmp;
        }

        /* find the successor of a given node */
        node_ptr   successor(node_ptr x) const {
            if (x->right)
                return (minNode(x->right));

            node_ptr prev = x;
            node_ptr tmp = x->parent;
            while (prev == tmp->right) {
                if (prev == tmp)
                    return tmp;
                prev = tmp;
                tmp = tmp->parent;
            }
            return (tmp);
        }

        node_ptr maxNode(node_ptr node) const {
            node_ptr tmp = node;
            if (!tmp)
                return NULL;
            while(tmp->right)
                tmp = tmp->right;
            return tmp;
        }

        node_ptr minNode (node_ptr node) const {
            node_ptr tmp = node;
            if (!tmp)
                return NULL;
            while (tmp->left)
                tmp = tmp->left;
            return tmp;
        }

        node_ptr getNode () const {
            return _ptr;
        }

        template <typename T1, bool B1, bool C1>
        friend bool operator==(const TreeIterator<T1, B1> &left, const TreeIterator<T1, C1> &right);
    };  //  class  TreeIterator

    /* Templates for TreeIterator */
    template <typename T, bool B, bool C>
    bool operator==(const TreeIterator<T, B> &left, const TreeIterator<T, C> &right) {
        return (left._ptr == right._ptr);
    }

    template <typename T, bool B, bool C>
    bool operator!=(const TreeIterator<T, B> &left, const TreeIterator<T, C> &right) {
        return !(left == right);
    }



    template <typename Key, typename Value, typename Node, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, Value> > >
    class tree {
    public:
        typedef Key      key_type;
        typedef Value   mapped_type;
        typedef Node    value_type;
//        typedef ft::pair<Key, Value>      value_type;
        typedef Compare key_compare;
//        typedef Compare value_compare;

        typedef TreeNode<value_type>    node_type; //mapnode
        typedef node_type*      node_pointer;  //mapnode *

        typedef Alloc                               allocator_type;
        typedef value_type&                                  reference;
        typedef const value_type&                            const_reference;
        typedef value_type*                                  pointer;
        typedef const value_type*                            const_pointer;
        typedef ptrdiff_t                           difference_type;
        typedef size_t                              size_type;
        typedef ft::TreeIterator<value_type, false>         iterator;
        typedef ft::TreeIterator<value_type , true>          const_iterator;
        typedef ft::ReverseIterator<iterator>       reverse_iterator;
        typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

        // http://www.cplusplus.com/reference/map/map/value_comp/
        class value_compare { // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
            friend class tree;
        protected:
            Compare comp;
            explicit value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object
        public:
            bool operator()(const value_type &x, const value_type &y) const {
                return comp(x.first, y.first);
            }
        };  // class value_compare

    protected:
        typename Alloc::template rebind<node_type>::other _node_alloc;
        allocator_type _alloc;
        key_compare _cmp;
        size_type _size;

        node_pointer _nil;
        node_pointer _root;
        node_pointer _end;
        node_pointer _begin;

    public:

        /*
         *  Constructors
         */

        explicit tree(const key_compare cmp = key_compare(), const allocator_type& alloc = allocator_type()) :
            _alloc(alloc), _cmp(cmp) {

            _nil = _node_alloc.allocate(1); // _nil = new TreeNode<value_type>;
            _nil->color = BLACK;
            _nil->left = _nil;  //_nil
            _nil->right = _nil;
            _nil->parent = _nil;

            _root = _nil;
            _end = _nil;
            _begin = _nil;
            _size = 0;
        }

        tree (const tree &other) : _alloc(other._alloc), _cmp(other._cmp ){
            _nil = _node_alloc.allocate(1);
            _nil->color = BLACK;
            _nil->left = _nil;
            _nil->right = _nil;
            _nil->parent = _nil;

            _root = _nil;
            _end = _nil;
            _begin = _nil;
            _size = 0;
            insertIter(other.begin(), other.end());
        }

        tree& operator=(const tree& other) {
            if (*this == other)
                return *this;
            _alloc = other._alloc;
            _cmp = other._cmp;
            clear();
            insertIter(other.beginNode(), other.endNode());
            return *this;
        }

        ~tree() {
            clear();
//            _node_alloc.destroy(_nil);
            _node_alloc.deallocate(_nil, 1);
            _size = 0;
        }

        /*
         *  Iterators
         */

        iterator begin() { return iterator(beginNode()); }
        const_iterator begin() const { return const_iterator(beginNode()); }
        iterator end() { return iterator(endNode()); }
        const_iterator end() const { return const_iterator(endNode()); }
        reverse_iterator rbegin() { return reverse_iterator(rbeginNode()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(rbeginNode()); }
        reverse_iterator rend() { return reverse_iterator(rendNode()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(rendNode()); }

        /*
         *  Capacity
         */

        size_type size() const { return _size; }
        size_type max_size() const { return _alloc.max_size(); /* _node_alloc.max_size();*/ } //todo or node_alloc
        bool empty() const { return (_size == 0);}



        /*
         *  Modifiers
         */

        void erase(iterator position) {
            node_pointer tmp = this->searchTreeIter(position);
            if (tmp == this->_end)
                return ;
            this->deleteNodeUtil(tmp);
//            delete tmp;
            --this->_size;
        }

        size_type   erase(const key_type& k) {
            iterator it = find(k);
            if (it == this->end())
                return 0;
            erase(it);
            return 1;
        }

        void erase(iterator first, iterator last) {
            for (; first != last; first++)
                erase(first);
        }

        //todo some diff here
        void swap(tree& other) {
            std::swap(_alloc, other._alloc);
            std::swap(_cmp, other._cmp);
            std::swap(_nil, other._nil);
            std::swap(_root, other._root);
            std::swap(_end, other._end);
            std::swap(_size, _size);
        }

        void clear () {
            clearUtil(_root);
        }



        /*
         *  Operations
         */

        iterator find (const key_type& k) {
            return (iterator(findUtil(k)));
        }

        const_iterator find (const key_type& k) const {
            return (const_iterator(findUtil(k)));
        }

        size_type count (const key_type& k) const {
            node_pointer tmp = findUtil(k);
            if (tmp == _nil)
                return 0;
            return 1;
        }

        //todo make diff all 4 funcs below
        virtual iterator			lower_bound(const key_type& k) {
            iterator	it = this->begin(), ite = this->end();
            while (it != ite) {
                if (this->itemcompare(*it, k) == false)
                    break ;
                ++it;
            }
            return it;
        }
        virtual const_iterator	lower_bound(const key_type& k) const {
            const_iterator	it = this->begin(), ite = this->end();
            while (it != ite) {
                if (this->itemcompare(*it, k) == false)
                    break ;
                ++it;
            }
            return it;
        }
        virtual iterator			upper_bound(const key_type& k) {
            iterator	it = this->begin(), ite = this->end();
            while (it != ite) {
                if (this->itemcompare(k, *it))
                    break ;
                ++it;
            }
            return it;
        }
        virtual const_iterator			upper_bound(const key_type& k) const {
            const_iterator it = this->begin(), ite = this->end();
            while (it != ite) {
                if (this->itemcompare(k, *it))
                    break ;
                ++it;
            }
            return it;
        }

        ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
            return (ft::make_pair(const_iterator(lower_bound(k)), const_iterator(upper_bound(k))));
        }

        ft::pair<iterator, iterator> equal_range(const key_type &k) {
            return (ft::make_pair(iterator(lower_bound(k)), iterator(upper_bound(k))));
        }

        /*
         *  Observers
         */

        key_compare key_comp() const { return _cmp; }
        value_compare value_comp() const { return value_compare(_cmp); }

//        value_compare value_comp const { return(value_compare(key_comp())); };


        void preOrderPrint() {
            preOrderPrintUtil(_root);
        }

        void inOrderPrint() {
            inOrderPrintUtil(_root);
        }

        /*
         *  Allocator
         */

        allocator_type  get_allocator() const { return _alloc; }

    protected:


        void preOrderPrintUtil(node_pointer tmp) {
            if (tmp == _nil)
                return;
            std::cout << tmp->value << " ";
            preOrderPrintUtil(tmp->left);
            preOrderPrintUtil(tmp->right);
        }

        void inOrderPrintUtil(node_pointer tmp) {
            if (tmp == _nil)
                return;
            inOrderPrintUtil(tmp->left);
            if (tmp->color == RED)
                std::cout << RED_COL << tmp->value << " " << RESET;
            else
                std::cout << tmp->value << " ";
//            std::cout << tmp->color << "c ";
            inOrderPrintUtil(tmp->right);
        }

        /* only tree functions */
//        node_pointer searchTree(node_pointer node, key_type key) {
//            if (node == _nil || key == node->value)
//                return node;
//            if (key < node->value)
//                return (searchTree(node->left, key));
//            return (searchTree(node->right, key));
//        }

//todo combine with function above
        node_pointer findUtil(const key_type& k) const {
            node_pointer it(this->_root);
            while (it && it != this->_begin && it != this->_end) {
                if (this->itemcompare(k, it->value))
                    it = it->left;
                else if (this->itemcompare(it->value, k))
                    it = it->right;
                else return it;
            }
            return _end;
        }


        //todo change
        node_pointer searchTreeIter(iterator position) {
            node_pointer it(this->_root);
            while (it && it != this->_begin && it != this->_end) {
                if (this->itemcompare(*position, it->value))
                    it = it->left;
                else if (this->itemcompare(it->value, *position))
                    it = it->right;
                else return (it);
            }
            return this->_end;
        }

        //todo change
        inline bool	itemcompare(const key_type& k, const ft::pair<Key, Value>& p) const {
            return this->key_comp()(k, p.first);
        }
        inline bool	itemcompare(const ft::pair<Key, Value>& p, const key_type& k) const {
            return this->key_comp()(p.first, k);
        }
        inline bool	itemcompare(const key_type& k1, const key_type& k2) const {
            return this->key_comp()(k1, k2);
        }
        inline bool	itemcompare(const ft::pair<Key, Value>& p1, const ft::pair<Key, Value>& p2) const {
            return this->key_comp()(p1.first, p2.first);
        }


//        template <class InputIterator>
//        void insertIter(InputIterator first, InputIterator last,
//                        typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
//        {
//            while (first != last) {
//                insert(*first);
//                ++first;
//            }
            //todo try catch
//            InputIterator it = first;
//            try {
//                for (; it != last; it++)
//                    insertNode(*it);
//            }
//            catch (...) {
//                InputIterator it1 = first;
//                for (; it1 != it; it++)
//                    this->erase(it1);
//                throw;
//            }
//        }

        node_pointer insertNode(const value_type val) {
            /* create new node */
            node_pointer node = _node_alloc.allocate(1);
            try {
//                node_pointer node = new TreeNode<T>;
//                node->value = val; //
                _alloc.construct(&node->value, val);
                node->color = RED;
                node->left = _nil;
                node->right = _nil;
                node->parent = _nil;
            }
            catch (...) {
                _node_alloc.deallocate(node, 1);
                throw;
            }

            _size++;
            /* if tree is empty, new node is root and black */
            if (_root == _nil) {
                _root = node;
                node->color = BLACK;
                return node;
            }

            /* find position for a new node */
            node_pointer tmp = _root;
            node_pointer tmpParent = NULL;
            while (tmp != _nil) {
                tmpParent = tmp;
                if (node->value < tmp->value)
                    tmp = tmp->left;
                else
                    tmp = tmp->right;
            }

            /* insert new node on the left or right */
            node->parent = tmpParent;
            if (tmpParent->value > node->value)
                tmpParent->left = node;
            else
                tmpParent->right = node;

            /* if parent of new node is black OR grandparent is _nil - return */
            if (tmpParent->color == BLACK || node->parent->parent == _nil)
                return node;

            balanceInsert(node);
            return node;
        }

        void balanceInsert(node_pointer added) {
            node_pointer uncle;
            while (added->parent->color == RED) {
                if (added->parent == added->parent->parent->left)
                    uncle = added->parent->parent->right;
                else if (added->parent == added->parent->parent->right)
                    uncle = added->parent->parent->left;

                /* if uncle is red - recolor parent and uncle; if grandparent != root - recolor it */
                if (uncle->color == RED) {
                    uncle->color = BLACK;
                    added->parent->color = BLACK;
                    if (added->parent->parent != _root)
                        added->parent->parent->color = RED;
                    //todo add recheck
                } else {
                    if (added->parent == added->parent->parent->right) {
                        if (added == added->parent->left) {
                            added = added->parent;
                            rotateRight(added);
                        }
                        //todo first rotate, than recolor
                        added->parent->color = BLACK;
                        added->parent->parent->color = RED;
                        rotateLeft(added->parent->parent);
                    } else {
                        if (added == added->parent->right) {
                            added = added->parent;
                            rotateLeft(added);
                        }
                        added->parent->color = BLACK;
                        added->parent->parent->color = RED;
                        rotateRight(added->parent->parent);
                    }
                }
                if (added == _root)
                    break;
            }
            _root->color = BLACK; //anyway shoul always be true
        }

        /* make tmp a new head of subtree: update tmp->parent info -> update links in tmp->parent node
         * -> update node->parent -> move tmp->left to node->right -> update tmp->left info */
        void rotateLeft(node_pointer node) {
            node_pointer tmp = node->right;
            tmp->parent = node->parent;
            if (tmp->parent == _nil)
                _root = tmp;
            else if (node->parent->left == node)
                node->parent->left = tmp;
            else
                node->parent->right = tmp;
            node->parent = tmp;

            node->right = tmp->left;
            if (tmp->left != _nil)
                tmp->left->parent = node;
            tmp->left = node;

        }

        /* make tmp a new head of subtree: update tmp->parent info -> update links in tmp->parent node
         * -> update node->parent -> move tmp->right to node->left -> update tmp->right info */
        void rotateRight(node_pointer node) {
            node_pointer tmp = node->left;
            tmp->parent = node->parent;
            if (tmp->parent == _nil)
                _root = tmp;
            else if (tmp->parent->left == node)
                tmp->parent->left = tmp;
            else
                tmp->parent->right = tmp;
            node->parent = tmp;

            node->left = tmp->right;
            if (tmp->right != _nil)
                tmp->right->parent = node;
            tmp->right = node;
        }

//        void deleteIter (iterator first, iterator last) {
//            for (; first != last; first++)
//                deleteNode(*first);
//        }

//        void deleteNode(const key_type val) {
//            deleteNodeUtil(_root, val);
//        }

        void deleteNodeUtil(node_pointer z) {
            node_pointer x, y;
            if (z == _nil) {
                std::cout << "Requested key doesn't exist in the tree\n";
                return ;
            }
            _size--;
            y = z;
            int y_orig_color = y->color;

            if (z->left == _nil) {
                x = z->right;
                transplant(z, z->right);
            }
            else if (z->right == _nil) {
                x = z->left;
                transplant(z, z->left);
            }
            else {
                y = minNode(z->right);
                y_orig_color = y->color;
                x = y->right;
                if (y->parent == z)
                    x->parent = y;
                else {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
//            delete z;
            _node_alloc.destroy(z);
            _node_alloc.deallocate(z, 1);
            if (y_orig_color == BLACK)
                balanceDelete(x);
        }

        void balanceDelete(node_pointer x) {
            node_pointer s;
            while (x != _root && x->color == BLACK) {
                if (x == x->parent->left) {
                    s = x->parent->right;
                    if (s->color == RED) {
                        // case 3.1
                        s->color = BLACK;
                        x->parent->color = RED;
                        rotateLeft(x->parent);
                        s = x->parent->right;
                    }

                    if (s->left->color == BLACK && s->right->color == BLACK) {
                        // case 3.2
                        s->color = RED;
                        x = x->parent;
                    } else {
                        if (s->right->color == BLACK) {
                            // case 3.3
                            s->left->color = BLACK;
                            s->color = RED;
                            rotateRight(s);
                            s = x->parent->right;
                        }

                        // case 3.4
                        s->color = x->parent->color;
                        x->parent->color = BLACK;
                        s->right->color = BLACK;
                        rotateLeft(x->parent);
                        x = _root;
                    }
                } else {
                    s = x->parent->left;
                    if (s->color == RED) {
                        // case 3.1
                        s->color = BLACK;
                        x->parent->color = RED;
                        rotateRight(x->parent);
                        s = x->parent->left;
                    }

                    if (s->right->color == BLACK && s->right->color == BLACK) {
                        // case 3.2
                        s->color = RED;
                        x = x->parent;
                    } else {
                        if (s->left->color == BLACK) {
                            // case 3.3
                            s->right->color = BLACK;
                            s->color = RED;
                            rotateLeft(s);
                            s = x->parent->left;
                        }

                        // case 3.4
                        s->color = x->parent->color;
                        x->parent->color = BLACK;
                        s->left->color = BLACK;
                        rotateRight(x->parent);
                        x = _root;
                    }
                }
            }
            x->color = BLACK;
        }

        void transplant(node_pointer u, node_pointer v) {
            if (u->parent == _nil)
                _root = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else
                u->parent->right = v;
            v->parent = u->parent;
        }

        node_pointer maxNode(node_pointer tmp) const {
            while(tmp->right != _nil)
                tmp = tmp->right;
            return tmp;
        }

        node_pointer minNode (node_pointer tmp) const {
            while (tmp->left != _nil)
                tmp = tmp->left;
            return tmp;
        }

        /* iterators utils */
        node_pointer beginNode() const { return minNode(_root); }
//        const_iterator begin () const { return const_iterator(minNode(_root)); }
        node_pointer endNode () const { return (_end); }
//        const_iterator end () const { return const_iterator(_end); }

        node_pointer rbeginNode() const { return (maxNode(_root)); }
//        const_reverse_iterator rbegin() const { return const_reverse_iterator(maxNode(_root)); }
        node_pointer rendNode() const { return (minNode(_root)); }
//        const_reverse_iterator rend() const { return const_reverse_iterator(minNode(_root)); }


        void clearUtil(node_pointer head) {
//            deleteIter(static_cast<iterator>(beginNode()), static_cast<iterator>(endNode()));
//            _size = 0;


            if (head == _nil)
                return ;
            if (head->left)
                clearUtil(head->left);
            if (head->right)
                clearUtil(head->right);
//            _node_alloc.destroy(&head->value);
            _node_alloc.deallocate(head, 1);
        }

//        /* find the predecessor of a given node */
//        node_pointer predecessor (node_pointer x) {
//            if (x->left)
//                return maxNode(x->left);
//            node_pointer tmp = x->parent;
//            while (tmp && tmp->left == x) {
//                x = tmp;
//                tmp = tmp->parent;
//            }
//            return tmp;
//        }
//
//        /* find the successor of a given node */
//        node_pointer   successor(node_pointer x) {
//            if (x->right != NULL)
//                return (minNode(x->right));
//            node_pointer   tmp = x->parent;
//            while (tmp->right == x) {
//                x = tmp;
//                tmp = tmp->parent;
//            }
//            return (tmp);
//        }


    };  //  class tree


}  //  namespace ft

#endif  //  _TREE_HPP
