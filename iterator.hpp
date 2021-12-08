#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

#include <cstddef>  //  defines size_t, ptrdiff_t, NULL
//#include <iterator>
#include <iostream>
#include "utils.hpp"

namespace ft {

    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

//    // template class iterator page 118 book
//    template <class C, class T, class D = ptrdiff_t, class Pt = T*, class Rt = T&>
//    struct iterator {
//        typedef C iterator_category;
//        typedef T value_type;
//        typedef D difference_type;
//        typedef Pt pointer;
//        typedef Rt reference;
//    };

    // template class iterator_traits
    template<typename It>
    struct iterator_traits {
        typedef typename It::iterator_category iterator_category;
        typedef typename It::value_type value_type;
        typedef typename It::difference_type difference_type;
        typedef typename It::pointer pointer;
        typedef typename It::reference reference;
    };

    template<typename T>
    struct iterator_traits <T *> {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T& reference;
    };

    template<typename T>
    struct iterator_traits <const T *> {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T& reference;
    };

/*  not sure if needed this part:
        template <typename InputIt>
        typename ft::iterator_traits<InputIt>::difference_type
        do_distance(InputIt first, InputIt last, std::input_iterator_tag)
        {
            typename ft::iterator_traits<InputIt>::difference_type distance = 0;
            for (InputIt it = first; it != last; it++)
                distance++;
            return distance;
        }

        template <typename InputIt>
        typename ft::iterator_traits<InputIt>::difference_type
        do_distance(InputIt first, InputIt last, std::random_access_iterator_tag)
        {
            return last - first;
        }

        template <typename InputIt>
        typename ft::iterator_traits<InputIt>::difference_type
        distance(InputIt first, InputIt last)
        {
            return ft::do_distance(first, last,
                                   typename ft::iterator_traits<InputIt>::iterator_category());
        }
*/

    /*
     *  vector iterator
     */

    template <typename T, bool IsConst = false>
    class RandomAccessIterator {
     public:
         typedef T           value_type;
         typedef std::ptrdiff_t   difference_type;
         typedef typename ft::conditional<IsConst, const T*, T*>::type         pointer;
         typedef typename ft::conditional<IsConst, const T&, T&>::type          reference;
         typedef std::random_access_iterator_tag    iterator_category;

     protected:
         pointer _ptr;

         pointer getPtr () const { return _ptr; }

     public:
         RandomAccessIterator() : _ptr(NULL) {}

    //     RandomAccessIterator(const RandomAccessIterator& other) : _ptr(other._ptr) {}
    //todo the same is next template?
         RandomAccessIterator(const RandomAccessIterator& other) : _ptr(const_cast<pointer>(other._ptr)) { }

         template <bool B>
         RandomAccessIterator(const RandomAccessIterator<T, B> &other,
                      typename ft::enable_if<!B>::type* = 0) : _ptr(other.getPtr()) {}

         RandomAccessIterator(const pointer other) : _ptr(other) {}

         RandomAccessIterator& operator=(const RandomAccessIterator& other) {
             this->_ptr = other._ptr;
             return *this;
         }

         virtual ~RandomAccessIterator() {}

         reference operator*() const { return static_cast<reference>(*this->_ptr);}
         pointer operator->() const { return this->_ptr; }

         RandomAccessIterator& operator++() { _ptr += 1; return *this; }
         RandomAccessIterator& operator--() { _ptr -= 1; return *this; }

         RandomAccessIterator operator++(int) { RandomAccessIterator tmp = *this; ++this->_ptr; return tmp; }
         RandomAccessIterator operator--(int) { RandomAccessIterator temp = *this; --this->_ptr; return temp; }

         RandomAccessIterator& operator+=(difference_type n) { _ptr += n; return *this; }
         RandomAccessIterator& operator-=(difference_type n) {_ptr -= n; return *this; }

         RandomAccessIterator operator+(difference_type n) const { return (RandomAccessIterator(_ptr + n)); }
         RandomAccessIterator operator-(difference_type n) const { return (RandomAccessIterator(_ptr - n)); }

         difference_type operator-(const reference other) const { return (_ptr - other._ptr); }

         reference operator[](difference_type n) { return *(_ptr + n); }


         //todo check if needed
         const reference operator[](difference_type n) const { return *(_ptr + n); }
        operator RandomAccessIterator<const value_type> () const { return RandomAccessIterator<const value_type>(_ptr) ; }


        /* friend for non-member overloads */

        template <typename T1, bool B1, bool C1>
        friend ptrdiff_t operator-(const RandomAccessIterator<T1, B1> &left, const RandomAccessIterator<T1, C1> &right);

        template <typename T1, bool B1, bool C1>
        friend bool operator==(const RandomAccessIterator<T1, B1> &left, const RandomAccessIterator<T1, C1> &right);

        template <typename T1, bool B1, bool C1>
        friend bool operator<(const RandomAccessIterator<T1, B1> &left, const RandomAccessIterator<T1, C1> &right);

    };  // RandomAccessIterator

        template <typename T>
        RandomAccessIterator<T> operator+(const RandomAccessIterator<T> &it, size_t num) {
            RandomAccessIterator<T> res = it;
            return res += num;
        }

        template <typename T>
        RandomAccessIterator<T> operator+(size_t num, const RandomAccessIterator<T> &it) {
            return it + num;
        }

        template <typename T>
        RandomAccessIterator<T> operator-(const RandomAccessIterator<T> &it, size_t num) {
            RandomAccessIterator<T> res = it;
            return res -= num;
        }

        template <typename T, bool B, bool C>
        ptrdiff_t operator-(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
            return left.getPtr() - right.getPtr();
        }

        template <typename T, bool B, bool C>
        bool operator==(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
            return (left.getPtr() == right.getPtr());
        }

        template <typename T, bool B, bool C>
        bool operator!=(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
            return !(left == right);
        }

        template <typename T, bool B, bool C>
        bool operator<(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
            return (left.getPtr() < right.getPtr());
        }

        template <typename T, bool B, bool C>
        bool operator<=(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
            return ((left < right) || (left == right));
        }

        template <typename T, bool B, bool C>
        bool operator>(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
            return !(left <= right);
        }

        template <typename T, bool B, bool C>
        bool operator>=(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
            return !(left < right);
        }

    template <typename Iter>
    class ReverseIterator {
     public:
        typedef typename iterator_traits<Iter>::value_type value_type;
         typedef typename iterator_traits<Iter>::pointer pointer;
         typedef typename iterator_traits<Iter>::reference reference;
         typedef typename iterator_traits<Iter>::difference_type difference_type;
         typedef Iter   iterator_type;
         typedef ReverseIterator<Iter> RevIt;

     protected:
         Iter _current;

     public:
         ReverseIterator() : _current(iterator_type()) {}
         ReverseIterator(Iter other) : _current(other) {}

         template <typename U>
         ReverseIterator(const ReverseIterator<U>& other) : _current(other.base()) {}

    //     RevIt& operator=(const ReverseIterator& other) {
    //         this->_current = other.base();
    //         return *this;
    //    }

         ~ReverseIterator() {}

         Iter base () const { return (_current); }

         reference operator*() const { Iter tmp = this->base(); ; return (*--tmp); }
         pointer operator->() const { return &(operator*()); }  // - с сайте cplusplus

         RevIt& operator++() { --_current; return (*this); }
         RevIt operator++(int) { RevIt tmp(*this); --_current; return tmp; }

         RevIt& operator-- () { ++_current; return (*this); }
         RevIt operator--(int) { RevIt tmp(*this); ++_current; return tmp; }

         RevIt& operator+= (difference_type num) { _current -= num; return (*this); }
         RevIt& operator-= (difference_type num) { _current += num; return (*this); }

         RevIt operator+(difference_type num) const { return (RevIt(_current - num)); }
         RevIt operator-(difference_type num) const { return (RevIt(_current + num)); }

         reference operator[](difference_type num) const { return (*(_current + num)); }
    //     const reference operator[](difference_type num) const { return (*(this + num)); }
    };  // ReverseIterator

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

    template <typename Iter1, typename Iter2>
    bool operator== (const ReverseIterator<Iter1>& left, const ReverseIterator<Iter2>& right) {
        return (left.base() == right.base());
    }

    template <typename Iter1, typename Iter2>
    bool operator!= (const ReverseIterator<Iter1>& left, const ReverseIterator<Iter2>& right) {
        return (left.base() != right.base());
    }

    template <typename Iter1, typename Iter2>
    bool operator< (const ReverseIterator<Iter1>& left, const ReverseIterator<Iter2>& right) {
        return (left.base() > right.base());
    }

    template <typename Iter1, typename Iter2>
    bool operator<= (const ReverseIterator<Iter1>& left, const ReverseIterator<Iter2>& right) {
        return (left.base() >= right.base());
    }

    template <typename Iter1, typename Iter2>
    bool operator> (const ReverseIterator<Iter1>& left, const ReverseIterator<Iter2>& right) {
        return (left.base() <= right.base());
    }

    template <typename Iter1, typename Iter2>
    bool operator>= (const ReverseIterator<Iter1>& left, const ReverseIterator<Iter2>& right) {
        return (left.base() <= right.base());
    }




    /*  from video, extra functions, not sure if needed
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
     */

}  //  namespace ft

#endif  //  ITERATOR_HPP_
