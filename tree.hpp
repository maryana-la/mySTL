#ifndef _TREE_HPP
#define _TREE_HPP

#include <algorithm>
#include <memory>
#include "iterator.hpp"

namespace ft {
    enum Color {
        RED,
        BLACK
    };

    template<typename T>
    struct TreeNode {
        Color color;
        T value;
        struct TreeNode *left;
        struct TreeNode *right;
        struct TreeNode *parent;
/* ojobout
        TreeNode(const T& other) : value(other), red(true), left(NULL), right(NULL), parent(NULL) {}

        TreeNode* rightMost() {
            Node* tmp = this;
            while(tmp->right)
                tmp = tmp->right;
            return tmp;
        }

        TreeNode* leftMost () {
            Node *tmp = this;
            while (tmp->left)
                tmp = tmp->left;
            return tmp;
        }

        TreeNode* previousNode () {
            TreeNode* prev = this;
            if (tmp->left)
                prev = left->rightMost();
            else {
                TreeNode* tmp = this->parent;
                while (tmp && tmp->left == prev) {
                    prev = tmp;
                    tmp = tmp->parent;
                }
                if (tmp)
                    prev = tmp;
                else
                    prev = NULL;
            }
            return prev;
        }

        TreeNode*   getNext() {
            TreeNode* next = this;
            if (this->right != NULL)
                next = right->leftMost();
            else {
                TreeNode*   tmp = this->parent;
                while (tmp && tmp->right == next) {
                    next = tmp;
                    tmp = tmp->parent;
                }
                if (tmp)
                    next = tmp;
                else
                    next = NULL;
            }
            return (next);
        } */
    };  // TreeNode


    template <typename T, bool IsConst = false>
    class TreeIterator {
    public:
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef typename ft::conditional<IsConst, const T *, T *>::type pointer;
        typedef typename ft::conditional<IsConst, const T &, T &>::type reference;
        typedef std::bidirectional_iterator_tag iterator_category;
//        typedef TreeNode<T> node_type;
//        typedef node_type* node_ptr;

    protected:
        node_ptr _ptr;

    public:
        TreeIterator() : _ptr(NULL) {}
        TreeIterator(node_ptr other) : _ptr(other) {}
        TreeIterator(TreeIterator& other const) : _ptr(other._ptr) {}

        reference operator*() const { }

        pointer operator->() const { }

        TreeIterator& operator++() {}
        TreeIterator& operator--() {}

        TreeIterator operator++(int) {}
        TreeIterator operator--(int) {}

        bool operator==(const TreeIterator other) const {}
        bool operator!=(const TreeIterator other) const {}







    }  //  class BidirectionalIterator


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
        allocator_type		_alloc;
        Compare				_cmp;
        node_pointer		_nil;
        node_pointer		_begin;
        node_pointer		_end;
        size_type			_size;
        size_type			_max_size;


    }  //  class Tree






}  //  namespace ft

#endif  //  _TREE_HPP
