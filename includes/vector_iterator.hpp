#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {

    template<typename T, bool IsConst = false>
    class RandomAccessIterator {
    public:
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef typename ft::conditional<IsConst, const T *, T *>::type pointer;
        typedef typename ft::conditional<IsConst, const T &, T &>::type reference;
        typedef std::random_access_iterator_tag iterator_category;

    protected:
        pointer _ptr;

    public:
        RandomAccessIterator() : _ptr(NULL) {}

        RandomAccessIterator(const RandomAccessIterator &other) : _ptr(const_cast<pointer>(other._ptr)) {}

        template<bool B>
        RandomAccessIterator(const RandomAccessIterator<T, B> &other,
                             typename ft::enable_if<!B>::type * = 0) : _ptr(other.getPtr()) {}

        RandomAccessIterator(const pointer other) : _ptr(other) {}

        RandomAccessIterator &operator=(const RandomAccessIterator &other) {
            this->_ptr = other._ptr;
            return *this;
        }

        virtual ~RandomAccessIterator() {}

        reference operator*() const { return static_cast<reference>(*this->_ptr); }

        pointer operator->() const { return this->_ptr; }

        RandomAccessIterator &operator++() {
            _ptr += 1;
            return *this;
        }

        RandomAccessIterator &operator--() {
            _ptr -= 1;
            return *this;
        }

        RandomAccessIterator operator++(int) {
            RandomAccessIterator tmp = *this;
            ++this->_ptr;
            return tmp;
        }

        RandomAccessIterator operator--(int) {
            RandomAccessIterator temp = *this;
            --this->_ptr;
            return temp;
        }

        RandomAccessIterator &operator+=(difference_type n) {
            _ptr += n;
            return *this;
        }

        RandomAccessIterator &operator-=(difference_type n) {
            _ptr -= n;
            return *this;
        }

        RandomAccessIterator operator+(difference_type n) const { return (RandomAccessIterator(_ptr + n)); }

        RandomAccessIterator operator-(difference_type n) const { return (RandomAccessIterator(_ptr - n)); }

        difference_type operator-(const reference other) const { return (_ptr - other._ptr); }

        reference operator[](difference_type n) { return *(_ptr + n); }

        const reference operator[](difference_type n) const { return *(_ptr + n); }
        pointer getPtr() const { return _ptr; }

        operator RandomAccessIterator<const value_type>() const { return RandomAccessIterator<const value_type>(_ptr); }

        /* friend for non-member overloads */

        template<typename T1, bool B1, bool C1>
        friend ptrdiff_t operator-(const RandomAccessIterator<T1, B1> &left, const RandomAccessIterator<T1, C1> &right);

        template<typename T1, bool B1, bool C1>
        friend bool operator==(const RandomAccessIterator<T1, B1> &left, const RandomAccessIterator<T1, C1> &right);

        template<typename T1, bool B1, bool C1>
        friend bool operator<(const RandomAccessIterator<T1, B1> &left, const RandomAccessIterator<T1, C1> &right);

    };  // RandomAccessIterator

    template<typename T>
    RandomAccessIterator<T> operator+(const RandomAccessIterator<T> &it, size_t num) {
        RandomAccessIterator<T> res = it;
        return res += num;
    }

    template<typename T>
    RandomAccessIterator<T> operator+(size_t num, const RandomAccessIterator<T> &it) {
        return it + num;
    }

    template<typename T>
    RandomAccessIterator<T> operator-(const RandomAccessIterator<T> &it, size_t num) {
        RandomAccessIterator<T> res = it;
        return res -= num;
    }

    template<typename T, bool B, bool C>
    ptrdiff_t operator-(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
        return left.getPtr() - right.getPtr();
    }

    template<typename T, bool B, bool C>
    bool operator==(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
        return (left.getPtr() == right.getPtr());
    }

    template<typename T, bool B, bool C>
    bool operator!=(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
        return !(left == right);
    }

    template<typename T, bool B, bool C>
    bool operator<(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
        return (left.getPtr() < right.getPtr());
    }

    template<typename T, bool B, bool C>
    bool operator<=(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
        return ((left < right) || (left == right));
    }

    template<typename T, bool B, bool C>
    bool operator>(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
        return !(left <= right);
    }

    template<typename T, bool B, bool C>
    bool operator>=(const RandomAccessIterator<T, B> &left, const RandomAccessIterator<T, C> &right) {
        return !(left < right);
    }
}  // namespace ft

#endif //VECTOR_ITERATOR_HPP
