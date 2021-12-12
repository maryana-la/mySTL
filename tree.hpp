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
        typedef std::ptrdiff_t difference_type;
        typedef typename ft::conditional<IsConst, const T *, T *>::type pointer;
        typedef typename ft::conditional<IsConst, const T &, T &>::type reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef TreeNode<T> node_type;
        typedef node_type* node_ptr;

    protected:
        node_ptr _ptr;

    public:
        TreeIterator() : _ptr(NULL) {}
//        TreeIterator(node_ptr other) : _ptr(other) {}
        TreeIterator(const TreeIterator& other) : _ptr(other._ptr) {}

        template<bool B>
        TreeIterator(const TreeIterator<T, B> &other, typename ft::enable_if<!B>::type* = 0) : _ptr(other._ptr) {}

        TreeIterator& operator=(const TreeIterator& other) {
            this->_ptr = other._ptr;
            return *this;
        }

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

        template <typename T1, bool B1, bool C1>
        friend bool operator==(const TreeIterator<T1, B1> &left, const TreeIterator<T1, C1> &right);

//        node_ptr maxNode(node_ptr tmp) {
//            while(tmp->right)
//                tmp = tmp->right;
//            return tmp;
//        }
//
//        node_ptr minNode (node_ptr tmp) {
//            while (tmp->left)
//                tmp = tmp->left;
//            return tmp;
//        }
///*
//        // find the predecessor of a given node
//        NodePtr predecessor(NodePtr x) {
//            // if the left subtree is not null,
//            // the predecessor is the rightmost node in the
//            // left subtree
//            if (x->left != TNULL) {
//                return maximum(x->left);
//            }
//
//            NodePtr y = x->parent;
//            while (y != TNULL && x == y->left) {
//                x = y;
//                y = y->parent;
//            }
//
//            return y;
//        }*/
//
//        node_ptr predecessor (node_ptr x) {
//            if (x->left)
//                return maxNode(x->left);
//            node_ptr tmp = x->parent;
//            while (tmp && tmp->left == x) {
//                x = tmp;
//                tmp = tmp->parent;
//            }
//            return tmp;
//        }

/* get next node inorder */
/*
        NodePtr successor(NodePtr x) {
            // if the right subtree is not null,
            // the successor is the leftmost node in the
            // right subtree
            if (x->right != TNULL) {
                return minimum(x->right);
            }

            // else it is the lowest ancestor of x whose
            // left child is also an ancestor of x.
            NodePtr y = x->parent;
            while (y != TNULL && x == y->right) {
                x = y;
                y = y->parent;
            }
            return y;
        } */
//        node_ptr   successor(node_ptr x) {
//            if (x->right != NULL)
//                return (minNode(x->right));
//            node_ptr   tmp = x->parent;
//            while (tmp->right == x) {
//                x = tmp;
//                tmp = tmp->parent;
//            }
//            return (tmp);
//        }

    };  //  class  TreeIterator

    template <typename T, bool B, bool C>
    bool operator==(const TreeIterator<T, B> &left, const TreeIterator<T, C> &right) {
        return (left._ptr == right._ptr);
    }

    template <typename T, bool B, bool C>
    bool operator!=(const TreeIterator<T, B> &left, const TreeIterator<T, C> &right) {
        return !(left == right);
    }



    template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
    class Tree {
    public:
        typedef T      key_type;
        typedef T      value_type;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef TreeNode<T>    node_type;
        typedef node_type*      node_pointer;

        typedef Alloc                               allocator_type;
        typedef T&                                  reference;
        typedef const T&                            const_reference;
        typedef T*                                  pointer;
        typedef const T*                            const_pointer;
        typedef ptrdiff_t                           difference_type;
        typedef size_t                              size_type;
        typedef ft::TreeIterator<T, false>         iterator;
        typedef ft::TreeIterator<T, true>          const_iterator;
        typedef ft::ReverseIterator<iterator>       reverse_iterator;
        typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

    private:
        typename allocator_type::template rebind<node_type>::other _node_alloc;
        allocator_type _alloc;
        Compare _cmp;
        node_pointer _nil;
        node_pointer _root;
        node_pointer _end;
        node_pointer _begin;
        size_type _size;

    public:
        explicit Tree(const key_compare cmp = key_compare(), const allocator_type& alloc = allocator_type()) :
            _alloc(alloc), _cmp(cmp) {
            _nil = _node_alloc.allocate(1);
            _nil = new TreeNode<T>;
            _nil->color = BLACK;
            _nil->left = _nil;
            _nil->right = _nil;
            _nil->parent = _nil;
            _root = _nil;
            _size = 0;
        }

        //todo check if constructor is needed
        Tree (const value_type *F, const value_type *L, const key_compare cmp = key_compare(), const allocator_type& alloc = allocator_type()) :
            _alloc(alloc), _cmp(cmp ){
            _nil = _node_alloc.allocate(1);
            _nil->color = BLACK;
            _nil->left = _nil;
            _nil->right = _nil;
            _nil->parent = _nil;
            _root = _nil;
            _size = 0;
            insert(F, L);
        }

        Tree (const Tree &other) : _alloc(other._alloc), _cmp(other._cmp ){
                _nil = _node_alloc.allocate(1);
                _nil->color = BLACK;
                _nil->left = _nil;
                _nil->right = _nil;
                _nil->parent = _nil;
                _root = _nil;
                _size = 0;
                //todo copy tree function
        }

        Tree& operator=(const Tree& other) {}

        iterator begin() { return iterator(_begin); }
        const_iterator begin () const { return const_iterator(_begin); }
        iterator end () { return iterator (_end); }
        const_iterator end () const { return const_iterator(_end); }

    /*    reverse_iterator rbegin() { return reverse_iterator(_end); }
        const_reverse_iterator rbegin() { return const_reverse_iterator(_end); }

        reverse_iterator rend() { return reverse_iterator(_begin); }
        const_reverse_iterator rend() { return const_reverse_iterator(_begin); }   */

        size_type size() const { return _size; }
        size_type max_size() const { return _alloc.max_size(); } //todo or node_alloc

        bool empty() const { return (_size == 0);}

        allocator_type  get_allocator() const { return _alloc; }

        key_compare key_comp() const { return _cmp; }

//        value_compare value_comp const { return(value_compare(key_comp())); };



        /* only tree functions */
        node_pointer searchTree(node_pointer node, key_type key) {
            if (node == _nil || key == node->value)
                return node;
            if (key < node->value)
                return (searchTree(node->left, key));
            return (searchTree(node->right, key));
        }

        node_pointer find(key_type key) {
            return (searchTree(_root, key));
        }

        void preOrderPrint() {
            preOrderPrintUtil(_root);
        }

        void inOrderPrint() {
            inOrderPrintUtil(_root);
        }

        void insert(const value_type val) {
            /* create new node */
            node_pointer node = _node_alloc.allocate(1);
//            node_pointer node = new TreeNode<T>;
//            node->value = val; //
            _node_alloc.construct(&node->value, val);
            node->color = RED;
            node->left = _nil;
            node->right = _nil;
            node->parent = _nil;

            /* if tree is empty, new node is root and black */
            if (_root == _nil) {
                _root = node;
                node->color = BLACK;
                return ;
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
                return ;

            balanceInsert(node);
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
//            _root->color = BLACK; //anyway shoul always be true
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


        void deleteNode(const value_type val) {
            deleteNodeUtil(_root, val);
        }

    private:
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

        void deleteNodeUtil(node_pointer root_tmp, const value_type val) {
            /* find node to delete */
            node_pointer z = searchTree(root_tmp, val);
            node_pointer x, y;
            if (z == _nil) {
                std::cout << "Requested key doesn't exist in the tree\n";
                return ;
            }
//            if (x->color == RED && (x->left == _nil || x->right == _nil))

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
            delete z;
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


        node_pointer maxNode(node_pointer tmp) {
            while(tmp->right != _nil)
                tmp = tmp->right;
            return tmp;
        }

        node_pointer minNode (node_pointer tmp) {
            while (tmp->left != _nil)
                tmp = tmp->left;
            return tmp;
        }

        /* find the predecessor of a given node */
        node_pointer predecessor (node_pointer x) {
            if (x->left)
                return maxNode(x->left);
            node_pointer tmp = x->parent;
            while (tmp && tmp->left == x) {
                x = tmp;
                tmp = tmp->parent;
            }
            return tmp;
        }

        /* find the successor of a given node */
        node_pointer   successor(node_pointer x) {
            if (x->right != NULL)
                return (minNode(x->right));
            node_pointer   tmp = x->parent;
            while (tmp->right == x) {
                x = tmp;
                tmp = tmp->parent;
            }
            return (tmp);
        }

    };  //  class Tree






}  //  namespace ft

#endif  //  _TREE_HPP
