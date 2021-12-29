/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:54:00 by                   #+#    #+#             */
/*   Updated: 2021/12/29 14:59:10 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_STACK_HPP_
#define INCLUDES_STACK_HPP_

#include "vector.hpp"

namespace ft {

template<typename T, typename Container = ft::vector<T> >
class stack {
 public:
    typedef Container   container_type;
    typedef typename Container::value_type  value_type;
    typedef typename Container::size_type   size_type;

 protected:
    Container c;

 public:
    stack() : c() {}

    explicit stack(const container_type &other) : c(other) {}

    ~stack() {}

    bool empty() const {
        return (c.empty());
    }

    size_type size() const {
        return (c.size());
    }

    value_type& top() {
        return (c.back());
    }
    const value_type& top() const {
        return(c.back());
    }

    void push(const value_type& other) {
        c.push_back(other);
    }

    void pop() {
        c.pop_back();
    }

    template <typename T1, typename Container1>
    friend bool operator==(const stack<T1, Container1>& lhs,
            const stack<T1, Container1>& rhs);

    template <typename T1, typename Container1>
    friend bool operator<(const stack<T1, Container1>& lhs,
            const stack<T1, Container1>& rhs);
};  // class stack

template <typename T, typename Container>
bool operator==(const stack<T, Container>& lhs,
        const stack<T, Container>& rhs) {
    return (lhs.c == rhs.c);
}

template <typename T, typename Container>
bool operator!=(const stack<T, Container>& lhs,
        const stack<T, Container>& rhs) {
    return !(lhs == rhs);
}

template <typename T, typename Container>
bool operator<(const stack<T, Container>& lhs,
        const stack<T, Container>& rhs) {
    return (lhs.c < rhs.c);
}

template <typename T, typename Container>
bool operator<=(const stack<T, Container>& lhs,
        const stack<T, Container>& rhs) {
    return ((lhs < rhs) || (lhs == rhs));
}

template <typename T, typename Container>
bool operator>(const stack<T, Container>& lhs,
        const stack<T, Container>& rhs) {
    return !(lhs <= rhs);
}

template <typename T, typename Container>
bool operator>=(const stack<T, Container>& lhs,
        const stack<T, Container>& rhs) {
    return !(lhs < rhs);
}

}  //  namespace ft

#endif  // INCLUDES_STACK_HPP_
