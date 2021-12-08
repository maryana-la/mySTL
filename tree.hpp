#ifndef _TREE_HPP
#define _TREE_HPP

#include <algorithm>
#include <memory>
#include "iterator.hpp"
#include "utils.hpp"

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
        TreeIterator(TreeIterator& other const) : _ptr(other._ptr) {}

        template<bool B>
        TreeIterator(TreeIterator<T, B> &other const, typename ft::enable_if<!B>::type* = 0) : _ptr(other._ptr) {}

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

        node_ptr maxNode(node_ptr tmp) {
            while(tmp->right)
                tmp = tmp->right;
            return tmp;
        }

        node_ptr minNode (node_ptr tmp) {
            while (tmp->left)
                tmp = tmp->left;
            return tmp;
        }
/*
        // find the predecessor of a given node
        NodePtr predecessor(NodePtr x) {
            // if the left subtree is not null,
            // the predecessor is the rightmost node in the
            // left subtree
            if (x->left != TNULL) {
                return maximum(x->left);
            }

            NodePtr y = x->parent;
            while (y != TNULL && x == y->left) {
                x = y;
                y = y->parent;
            }

            return y;
        }*/

        node_ptr predecessor (node_ptr x) {
            if (tmp->left)
                return maxNode(x->left);
            TreeNode* tmp = x->parent;
            while (tmp && tmp->left == x) {
                x = tmp;
                tmp = tmp->parent;
            }
            return tmp;
        }

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
        node_ptr   successor(node_ptr x) {
            if (x->right != NULL)
                return (minNode(x->right));
            TreeNode*   tmp = x->parent;
            while (tmp->right == x) {
                x = tmp;
                tmp = tmp->parent;
            }
            return (tmp);
        }
    }  //  class  TreeIterator

    template <typename T, bool B, bool C>
    bool operator==(const TreeIterator<T, B> &left, const TreeIterator<T, C> &right) {
        return (left._ptr == right._ptr);
    }

    template <typename T, bool B, bool C>
    bool operator!=(const TreeIterator<T, B> &left, const TreeIterator<T, C> &right) {
        return !(left == right);
    }



    template <typename Tr, typename Compare = std::less<Tr>, typename Alloc = std::allocator<Tr> >
    class Tree {
    public:
        typedef Tr      key_type;
        typedef Tr      value_type;
        typedef Compare key_compare;
        typedef    dsdsd     value_compare;
        typedef TreeNode<Tr>    node_type;
        typedef node_type*      node_pointer;

        typedef Alloc                               allocator_type;
        typedef T&                                  reference;
        typedef const T&                            const_reference;
        typedef T*                                  pointer;
        typedef const T*                            const_pointer;
        typedef ptrdiff_t                           difference_type;
        typedef size_t                              size_type;
        typedef ft::TreeIterator<Tr, false>         iterator;
        typedef ft::TreeIterator<Tr, true>          const_iterator;
        typedef ft::ReverseIterator<iterator>       reverse_iterator;
        typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

    private:
        typename allocator_type::template rebind<Node>::other _node_alloc;
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

        reverse_iterator rbegin() { return reverse_iterator(_end); }
        const_reverse_iterator rbegin() { return const_reverse_iterator(_end); }
        reverse_iterator rend() { return reverse_iterator(_begin); }
        const_reverse_iterator rend() { return const_reverse_iterator(_begin); }

        size_type size() const { return _size; }
        size_type max_size() const { return _alloc.max_size(); } //todo or node_alloc

        bool empty() const { return (_size == 0);}

        allocator_type  get_allocator() const { return _alloc; }

        key_compare key_comp() const { return _cmp; }

//        value_compare value_comp const { return(value_compare(key_comp())); };




    }  //  class Tree






}  //  namespace ft

#endif  //  _TREE_HPP
