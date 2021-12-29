/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:25:54 by                   #+#    #+#             */
/*   Updated: 2021/12/29 15:27:58 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INCLUDES_TREE_ITERATOR_HPP_
#define INCLUDES_TREE_ITERATOR_HPP_

#include "tree_node.hpp"
#include "utils.hpp"

namespace ft {

template<typename T, bool IsConst = false>
class TreeIterator {
 public:
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef typename ft::conditional<IsConst, const T *, T *>::type pointer;
    typedef typename ft::conditional<IsConst, const T &, T &>::type reference;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef TreeNode <T> node_type;
    typedef node_type *node_ptr;

 protected:
    node_ptr _ptr;

 public:
    TreeIterator() : _ptr(NULL) {}

    TreeIterator(const node_ptr other) : _ptr(other) {}

    template<bool B>
    TreeIterator(const TreeIterator<T, B> &other,
                 typename ft::enable_if<!B>::type * = 0) :
                 _ptr(other.getNode()) {}

    TreeIterator &operator=(TreeIterator const &other) {
        this->_ptr = other._ptr;
        return *this;
    }

    ~TreeIterator() {}

    reference operator*() const { return static_cast<reference>(_ptr->value); }

    pointer operator->() const { return &(_ptr->value); }

    TreeIterator &operator++() {
        _ptr = successor(_ptr);
        return *this;
    }

    TreeIterator &operator--() {
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

    node_ptr getNode() const {
        return _ptr;
    }

    template<typename T1, bool B1, bool C1>
    friend bool operator==(const TreeIterator<T1, B1> &left,
            const TreeIterator<T1, C1> &right);

 protected:
    /* find the predecessor of a given node */
    node_ptr predecessor(node_ptr x) const {
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
    node_ptr successor(node_ptr x) const {
        if (x->right)
            return (minNode(x->right));

        node_ptr prev = x;
        node_ptr tmp = x->parent;
        while (tmp && prev == tmp->right) {
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
        while (tmp->right)
            tmp = tmp->right;
        return tmp;
    }

    node_ptr minNode(node_ptr node) const {
        node_ptr tmp = node;
        if (!tmp)
            return NULL;
        while (tmp->left)
            tmp = tmp->left;
        return tmp;
    }
};  //  class  TreeIterator

/* Templates for TreeIterator */
template<typename T, bool B, bool C>
bool operator==(const TreeIterator<T, B> &left,
        const TreeIterator<T, C> &right) {
    return (left._ptr == right._ptr);
}

template<typename T, bool B, bool C>
bool operator!=(const TreeIterator<T, B> &left,
        const TreeIterator<T, C> &right) {
    return !(left == right);
}

}  // namespace ft

#endif  // INCLUDES_TREE_ITERATOR_HPP_
