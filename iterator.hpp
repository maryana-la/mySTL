#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

#include <cstddef>

namespace ft {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};


// template class iterator page 118 book
template <class C, class T, class D = ptrdiff_t, class Pt = T*, class Rt = T&>
struct iterator {
    typedef C iterator_category;
    typedef T value_type;
    typedef D difference_type;
    typedef Pt pointer;
    typedef Rt reference;
};

// template class iterator_traits
template<class It>
struct iterator_traits {
    typedef typename It::iterator_category iterator_category;
    typedef typename It::value_type value_type;
    typedef typename It::distance_type distance_type;
    typedef typename It::pointer pointer;
    typedef typename It::reference reference;
};

template<class T>
struct iterator_traits <T *> {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t distance_type;
    typedef T *pointer;
    typedef T& reference;
};

template<class T>
struct iterator_traits <const T *> {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t distance_type;
    typedef const T *pointer;
    typedef const T& reference;
};


/*
 *  vector iterator
 */

template <class T, class Category = ft::random_access_iterator_tag>
class RandomAccessIterator {
 public:
     typedef T           value_type;
     typedef ptrdiff_t   difference_type;
     typedef T*          pointer;
     typedef T&          reference;
     typedef Category    iterator_category;

     typedef RandomAccessIterator<T, Category> RAIt;

 private:
     pointer _ptr;

 public:
     RandomAccessIterator() : _ptr(NULL) {}
     explicit RandomAccessIterator(const pointer other) : _ptr(other) {}
     explicit RandomAccessIterator(const RandomAccessIterator& other) :
         _ptr(other._ptr) {}

     RandomAccessIterator& operator=(const RandomAccessIterator& other) {
         this->_ptr = other._ptr;
         return *this;
     }

     virtual ~RandomAccessIterator() {}

     reference operator*() const { return *this->_ptr; }
     pointer operator->() const { return this->_ptr; }

     RAIt& operator++() { ++_ptr; return *this; }
     RAIt& operator--() { --_ptr; return *this; }

     RAIt operator++(int) { RAIt tmp = *this; ++this->_ptr; return tmp; }
     RAIt operator--(int) { RAIt temp = *this; --this->_ptr; return temp; }

     RAIt& operator+=(difference_type n) { _ptr += n; return *this; }
     RAIt& operator-=(difference_type n) {_ptr -= n; return *this; }

     RAIt operator+(difference_type n) const { return (RAIt(_ptr + n)); }
     RAIt operator-(difference_type n) const { return (RAIt(_ptr - n)); }

     difference_type operator-(const RAIt& other) const { return (_ptr - other._ptr); }

     reference operator[](difference_type n) { return (*(*this + n)); }

     bool operator==(const RAIt& other) const {return (_ptr == other._ptr); }
     bool operator!=(const RAIt& other) const { return (_ptr != other._ptr); }

     bool operator>(const RAIt& other) const { return (_ptr > other._ptr); }
     bool operator>=(const RAIt& other) const { return (_ptr >= other._ptr); }
     bool operator<(const RAIt& other) const { return (_ptr < other._ptr); }
     bool operator<=(const RAIt& other) const { return (_ptr <= other._ptr); }
};

    /*
    template <typename T>
    RandomAccessIterator<T> operator+(const RandomAccessIterator<T> &ite, size_t offset)
    {
        RandomAccessIterator<T> res = ite;
        return res += offset;
    }

    template <typename T>
    RandomAccessIterator<T> operator+(size_t offset, const RandomAccessIterator<T> &ite)
    {
        return ite + offset;
    }

    template <typename T>
    RandomAccessIterator<T> operator-(const RandomAccessIterator<T> &ite, size_t offset)
    {
        RandomAccessIterator<T> res = ite;
        return res -= offset;
    }

    template <typename T>
    ptrdiff_t operator-(const RandomAccessIterator<T> &lhs, const RandomAccessIterator<T> &rhs)
    {
        return lhs._e - rhs._e;
    }

    template <typename T>
    ptrdiff_t operator-(const RandomAccessIterator<T, Category> &left, const RandomAccessIterator<T, Category> &right) {
        return left._ptr - right._ptr;
    }
*/


/*
Two iterators that compare equal, keep comparing equal after being both increased.
*a++
Can be decremented (if a dereferenceable iterator value precedes it).
*a--
Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another.
n + a
a - b - to friend
For mutable iterators (non-constant iterators):
Can be dereferenced as an lvalue (if in a dereferenceable state).	*a = t

 */

template <typename Iter>
class ReverseIterator : public iterator<
                    typename fiterator_traits<_Iter>::iterator_category,
                    typename iterator_traits<_Iter>::value_type,
                    typename iterator_traits<_Iter>::difference_type,
                    typename iterator_traits<_Iter>::pointer,
                    typename iterator_traits<_Iter>::reference> {
 public:
     typedef typename iterator_traits<Iter>::pointer Ptr;
     typedef typename iterator_traits<Iter>::reference Ref;
     typedef typename iterator_traits<Iter>::distance_type Dist;
     typedef Iter iterator_type;
     typedef ReverseIterator<Iter> RevIt;

 protected:
     Iter _current;

 public:
     ReverseIterator() {}
     explicit ReverseIterator(Iter x) : _current(x) {}

     template<typename U>
     ReverseIterator(const ReverseIterator<U>& other) : _current(other.base()) {}

     ~ReverseIterator() {}

     Iter base () const { return (_current); }

     Ref operator*() const { Iter tmp(*this); return (*--tmp); }
     Ptr operator->() const { return &(operator*()); }  // - с сайте cplusplus

     RevIt& operator++() { --_current; return (*this); }
     RevIt operator++(int) { RevIt tmp(*this); --_current; return tmp; }

     RevIt& operator-- () { ++_current; return (*this); }
     RevIt operator--(int) { RevIt tmp(*this); ++_current; return tmp; }

     RevIt& operator+= (Dist num) { _current -= num; return (*this); }
     RevIt& operator-= (Dist num) { _current += num; return (*this); }

     RevIt operator+(Dist num) const { return (RevIt(_current - num)); }
     RevIt operator-(Dist num) const { return (RevIt(_current + num)); }

     Ref operator[](Dist num) const { return (*(this + num)); }
};

//  ReverseIterator templates
template<typename Iter, typename D>
ReverseIterator<Iter> operator* (D num, const ReverseIterator<Iter>& other) {
    return (other + num);
}

template <typename Iter>
ReverseIterator<Iter> operator-(const ReverseIterator<Iter> &other,
        typename ReverseIterator<Iter>::difference_type num) {
    ReverseIterator<Iter> tmp(other.base() + num);
    return tmp;
}

template <typename Iter>
ReverseIterator<Iter> operator+(const ReverseIterator<Iter> &other,
        typename ReverseIterator<Iter>::difference_type num) {
    ReverseIterator<Iter> tmp(other.base() - num);
    return tmp;
}

template <typename Iter>
bool operator== (const ReverseIterator<Iter>& left, const ReverseIterator<Iter>& right) {
    return (left.base() == right.base());
}

template <typename Iter>
bool operator!= (const ReverseIterator<Iter>& left, const ReverseIterator<Iter>& right) {
    return (left.base() != right.base());
}

template <typename Iter>
bool operator< (const ReverseIterator<Iter>& left, const ReverseIterator<Iter>& right) {
    return (left.base() > right.base());
}

template <typename Iter>
bool operator<= (const ReverseIterator<Iter>& left, const ReverseIterator<Iter>& right) {
    return (left.base() >= right.base());
}

template <typename Iter>
bool operator> (const ReverseIterator<Iter>& left, const ReverseIterator<Iter>& right) {
    return (left.base() <= right.base());
}

template <typename Iter>
bool operator>= (const ReverseIterator<Iter>& left, const ReverseIterator<Iter>& right) {
    return (left.base() <= right.base());
}

/*  from video, extra functions  */
//  todo check if distance <0
template <typename Iterator, typename Distance>
void advance_template(Iterator& iter, Distance dist, input_iterator_tag) {
    for (ptrdiff_t i = 0; i < dist; ++i)
        ++iter;
}

template <typename Iterator, typename Distance>
void advance_template(Iterator& iter, Distance dist, random_access_iterator_tag) {
    iter += dist;
}

template <class InputIterator, class Distance>
void advance(InputIterator& it, Distance dist) {
    advance_template(it, dist, typename iterator_traits<InputIterator>::iterator_category());
}

}  //  namespace ft

#endif  //  ITERATOR_HPP_
