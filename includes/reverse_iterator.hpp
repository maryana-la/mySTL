/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:39:03 by                   #+#    #+#             */
/*   Updated: 2021/12/29 14:42:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  INCLUDES_REVERSE_ITERATOR_HPP_
#define  INCLUDES_REVERSE_ITERATOR_HPP_

#include "iterator.hpp"

namespace ft {

template<typename Iter>
class ReverseIterator {
 public:
    typedef typename iterator_traits<Iter>::value_type value_type;
    typedef typename iterator_traits<Iter>::pointer pointer;
    typedef typename iterator_traits<Iter>::reference reference;
    typedef typename iterator_traits<Iter>::difference_type difference_type;
    typedef Iter iterator_type;
    typedef ReverseIterator<Iter> RevIt;

 protected:
    Iter _current;

 public:
    ReverseIterator() : _current(iterator_type()) {}

    explicit ReverseIterator(Iter other) : _current(other) {}

    template<typename U>
    ReverseIterator(const ReverseIterator<U> &other) : _current(other.base()) {}

    ~ReverseIterator() {}

    Iter base() const { return (_current); }

    reference operator*() const {
        Iter tmp = this->base();;
        return (*--tmp);
    }

    pointer operator->() const { return &(operator*()); }

    RevIt &operator++() {
        --_current;
        return (*this);
    }

    RevIt operator++(int) {
        RevIt tmp(*this);
        --_current;
        return tmp;
    }

    RevIt &operator--() {
        ++_current;
        return (*this);
    }

    RevIt operator--(int) {
        RevIt tmp(*this);
        ++_current;
        return tmp;
    }

    RevIt &operator+=(difference_type num) {
        _current -= num;
        return (*this);
    }

    RevIt &operator-=(difference_type num) {
        _current += num;
        return (*this);
    }

    RevIt operator+(difference_type num) const {
        return (RevIt(_current - num)); }

    RevIt operator-(difference_type num) const {
        return (RevIt(_current + num)); }

    reference operator[](difference_type num) const {
        return (*(_current + num)); }
};  // ReverseIterator

// ReverseIterator templates
template<typename Iter, typename D>
ReverseIterator<Iter> operator*(D num, const ReverseIterator<Iter> &other) {
    return (other + num);
}

template<typename Iter>
ReverseIterator<Iter> operator-(const ReverseIterator<Iter> &other,
        typename ReverseIterator<Iter>::difference_type num) {
    ReverseIterator<Iter> tmp(other.base() + num);
    return tmp;
}

template<typename Iter>
ReverseIterator<Iter> operator+(const ReverseIterator<Iter> &other,
        typename ReverseIterator<Iter>::difference_type num) {
    ReverseIterator<Iter> tmp(other.base() - num);
    return tmp;
}

template<typename Iter1, typename Iter2>
bool operator==(const ReverseIterator<Iter1> &left,
        const ReverseIterator<Iter2> &right) {
    return (left.base() == right.base());
}

template<typename Iter1, typename Iter2>
bool operator!=(const ReverseIterator<Iter1> &left,
        const ReverseIterator<Iter2> &right) {
    return (left.base() != right.base());
}

template<typename Iter1, typename Iter2>
bool operator<(const ReverseIterator<Iter1> &left,
        const ReverseIterator<Iter2> &right) {
    return (left.base() > right.base());
}

template<typename Iter1, typename Iter2>
bool operator<=(const ReverseIterator<Iter1> &left,
        const ReverseIterator<Iter2> &right) {
    return (left.base() >= right.base());
}

template<typename Iter1, typename Iter2>
bool operator>(const ReverseIterator<Iter1> &left,
               const ReverseIterator<Iter2> &right) {
    return (left.base() <= right.base());
}

template<typename Iter1, typename Iter2>
bool operator>=(const ReverseIterator<Iter1> &left,
        const ReverseIterator<Iter2> &right) {
    return (left.base() <= right.base());
}
}  // namespace ft

#endif  // INCLUDES_REVERSE_ITERATOR_HPP_
