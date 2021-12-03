#ifndef _STACK_HPP
#define _STACK_HPP

#include "vector.hpp"

namespace ft {

template<typename T, typename Container = ft::vector<T> >
class stack {
public:
    typedef Container   container_type;
    typedef typename Container::value_type  value_type;
    typedef typename Container::size_type   size_type;

protected:
    Container _cont;

public:
    stack() : _cont() {}

    explicit stack(const container_type &other) : _cont(other) {}

    ~stack() {}

    bool empty () const {
        return (_cont.empty());
    }

    size_type size() const {
        return (_cont.size());
    }

    value_type& top() {
        return (_cont.back());
    }
    const value_type& top() const {
        return(_cont.back());
    }

    void push(const value_type& other) {
        _cont.push_back(other);
    }

    void pop() {
        _cont.pop_back();
    }

    template <class T1, class Container1>
    friend bool operator== (const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs);

    template <class T1, class Container1>
    friend bool operator<  (const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs);

};  // class stack

    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs._cont == rhs._cont);
    }

    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return !(lhs == rhs);
    }

    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs._cont < rhs._cont);
    }

    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return ((lhs < rhs) || (lhs == rhs));
    }

    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return !(lhs <= rhs);
    }

    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return !(lhs < rhs);
    }


}  //  namespace ft

#endif  //  _STACK_HPP
