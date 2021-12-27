#ifndef _VECTOR_HPP
#define _VECTOR_HPP

#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include <iterator>
#include <memory>
#include <iostream>

namespace ft {

    template<typename T, typename Allocator = std::allocator<T> >
    class vector {
    public:
        typedef Allocator                       allocator_type;
        typedef T                               value_type;
        typedef T&                              reference;
        typedef const T&                        const_reference;
        typedef T*                              pointer;
        typedef const T*                        const_pointer;
        typedef ptrdiff_t                       difference_type;
        typedef size_t                          size_type;
        typedef RandomAccessIterator<T, false>  iterator;
        typedef RandomAccessIterator<T, true>   const_iterator;
        typedef ReverseIterator<iterator>       reverse_iterator;
        typedef ReverseIterator<const_iterator> const_reverse_iterator;

    private:
        pointer             _array; // указатель на выделенную память
        size_type           _capacity; // выделенная память
        size_type           _numOfElem; // кол-во элементов
        allocator_type      _alloc; // некий механизм, с помощью которого будем выделять память

    public:
        /*
         *  Vector constructors
         */

        /* (1) empty container constructor (default constructor) */
        explicit vector (const allocator_type& alloc = allocator_type()) :
            _array(NULL), _capacity(0), _numOfElem(0), _alloc(alloc) {
        }

        /* (2) fill constructor: Constructs a container with n elements. Each element is a copy of val */
        explicit vector (size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()) :
                        _capacity(n), _numOfElem(n), _alloc(alloc) {
            _array = _alloc.allocate(_capacity);
            size_type i = 0;
            try {
                for (; i < n; i++)
                    _alloc.construct(_array + i, value);
            }
            catch (...) {
                for (size_type j = 0; j < i; j++)
                    _alloc.destroy(&_array[j]);
                _alloc.deallocate(_array, n);
                throw;
            }
        };

        /* (3) range constructor */
        template <typename InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0): _alloc(alloc), _array(NULL), _capacity(0), _numOfElem(0) {
            insert(begin(), first, last);
            _numOfElem = std::distance(first, last);
            _capacity = _numOfElem;
        }

        /* (4) copy constructor */
        vector (const vector& other) {
            _array = NULL;
            _capacity = 0;
            _numOfElem = 0;
            insert(begin(), other.begin(), other.end());
            this->_numOfElem = other.size();
            this->_capacity = other.capacity();
            this->_alloc = other.get_allocator();
        };

        ~vector() {
            if (!empty()) {
                for (size_type i = 0; i < _numOfElem; i++)
                    _alloc.destroy(&_array[i]);
                _alloc.deallocate(_array, _capacity);
            }
            else if (_capacity)
                _alloc.deallocate(_array, _capacity);
        }

        vector& operator= (const vector& other) {
            clear();
            insert(begin(),other.begin(), other.end());
            return *this;
        }


        /*
         *  Iterators
         */

        iterator begin() { return _array; }
        const_iterator begin() const { return (const_iterator(_array)); }

        iterator end() { return _array + _numOfElem; }
        const_iterator end() const { return (const_iterator(_array + _numOfElem)); }

        reverse_iterator rbegin() { return (reverse_iterator(end())); }
        const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }

        reverse_iterator rend() { return (reverse_iterator(begin())); }
        const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }


        /*
         *  Capacity
         */

        size_type size() const { return _numOfElem; }
        size_type max_size() const { return _alloc.max_size(); }

        void resize (size_type n, value_type val = value_type()) {
            if (n < _numOfElem) {
                for (size_type i = n + 1; i < _numOfElem; i++)
                    _alloc.destroy(_array + i);
            }
            if (n > _numOfElem) {
                if (n > _capacity)
                    reserve(n);
                if (n <= _capacity) {
                    for (size_type i = _numOfElem; i < n; i++)
                        _alloc.construct(_array + i, val);
                }
            }
            _numOfElem = n;
        }

        size_type capacity() const { return _capacity; }
        bool empty() const { return (_numOfElem == 0); }

        void reserve (size_type n) {
            if (max_size() < n)
                throw std::length_error("vector<T> too long");
            if (n > _capacity) {
                pointer tmp = _alloc.allocate(n);
                size_type i = 0;
                // catch exception if memory cannot be allocated
                try {
                    for (; i < _numOfElem; i++)
                        _alloc.construct(tmp + i, _array[i]);
                }
                catch (...) {
                    for (size_type j = 0; j < i; j++)
                        _alloc.destroy(&tmp[j]);
                    _alloc.deallocate(tmp, n);
                    throw;
                }
                i = 0;
                for (; i < _numOfElem; i++)
                    _alloc.destroy(&_array[i]);
                if (_capacity != 0)
                    _alloc.deallocate(_array, _capacity);
                _array = tmp;
                _capacity = n;
            }
        }

        /*
         *  Element access
         */

        reference operator[] (size_type n) { return *(_array + n); }

        const_reference operator[] (size_type n) const { return *(_array + n); }

        reference at (size_type n) {
            if (n > _numOfElem || n < 0)
                throw std::out_of_range("ft::vector::at error");
            return (_array[n]);
        }

        const_reference at (size_type n) const {
            if (n > _numOfElem || n < 0)
                throw std::out_of_range("ft::vector::at error");
            return (_array[n]);
        }

        reference front() { return _array[0]; }
        const_reference front() const  { return _array[0]; }

        reference back() { return _array[_numOfElem - 1]; }
        const_reference back() const { return _array[_numOfElem - 1]; }

        /*
         *  Modifiers
         */

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last,
                     typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
            erase(begin(), end());
            insert(begin(), first, last);
        }

        void assign (size_type n, const value_type& val) {
            const value_type& tmp = val;
            erase(begin(), end());
            insert(begin(), n, tmp);
        }

        void push_back (const value_type& val) {
            if (_numOfElem == 0)
                reserve(1);
            else if (_numOfElem + 1 > _capacity)
                reserve(_capacity * 2);
            _alloc.construct(&_array[_numOfElem], val);
            _numOfElem += 1;
        }

        void pop_back() {
            _alloc.destroy(&_array[_numOfElem - 1]);
            _numOfElem -= 1;
        }

        iterator insert(iterator position, const value_type& val) {
            int n = std::distance(begin(), position);
            insert(position, 1, val);
            return (iterator(&_array[n]));
        }

        void insert(iterator position, size_type n, const value_type& val) {
            if (n == 0)
                return ;
            else if (max_size() - size() < n)
                throw std::length_error("vector::insert unacceptable size");
            else if (position > end())
                throw std::out_of_range ("vector::insert iterator error");
            size_type new_size = _capacity;
            if (_capacity < _numOfElem + n) {
                if (n > _numOfElem)
                    new_size = _numOfElem + n;
                else
                    new_size = _capacity * 2;
            }
            pointer tmp = _alloc.allocate(new_size);
            if (_numOfElem == 0) {
                size_type i = 0;
                try {
                    for (; i < n; i++)
                        _alloc.construct(&tmp[i], val);
                }
                catch (...) {
                    for (size_type j = 0; j < i; j++)
                        _alloc.destroy(&tmp[j]);
                    _alloc.deallocate(tmp, new_size);
                    throw;
                }
            }
            else {
                iterator tmp1 = begin();
                long int InsertPos = std::distance(begin(), position);
                long int i = 0;
                try {
                    for (; i < InsertPos; i++)
                        _alloc.construct(&tmp[i], _array[i]);
                    for (; i < (long)(InsertPos + n); i++)
                        _alloc.construct(&tmp[i], val);
                    for (; i < (long)(_numOfElem + n); i++)
                        _alloc.construct(&tmp[i], _array[i - n]);
                }
                catch (...) {
                    for (long int j = 0; j < i; j++)
                        _alloc.destroy(&tmp[j]);
                    _alloc.deallocate(tmp, new_size);
                    throw;
                }
            }
            for (size_type i = 0; i < _numOfElem; i++)
                _alloc.destroy(&_array[i]);
            if (_capacity != 0)
                _alloc.deallocate(_array, _capacity);
            _array = tmp;
            _numOfElem += n;
            _capacity = new_size;
        }


        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last,
                     typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
            size_type n = std::distance(first, last);
            if (n == 0)
                return ;
            else if (max_size() - size() < n)
                throw std::length_error("vector::insert unacceptable size");
            else if (position > end())
                throw std::out_of_range ("vector::insert iterator error");

            size_type new_size = _capacity;
            if (_capacity < _numOfElem + n) {
                if (n > _numOfElem)
                    new_size = _numOfElem + n;
                else
                    new_size = _capacity * 2;
            }
            pointer tmp = _alloc.allocate(new_size);

            if (_numOfElem == 0) {
                size_type i = 0;
                try {
                    for (; first != last; first++, i++)
                        _alloc.construct(&tmp[i], *first);
                }
                catch (...) {
                    for (size_type j = 0; j < i; j++)
                        _alloc.destroy(&tmp[j]);
                    _alloc.deallocate(tmp, new_size);
                    throw;
                }
            }

            else {
                iterator it = begin();
                size_type i = 0;
                try {
                    for (; it != position; i++, it++)
                        _alloc.construct(tmp + i, _array[i]);

                    size_type j = 0;
                    for (; first != last; first++, j++, it++)
                        _alloc.construct(tmp + i + j, *first);

                    for (; i + j < new_size; i++, it++)
                        _alloc.construct(tmp + i + j, _array[i]);
                }
                catch (...) {
                    size_type j = 0;
                    for (; it != begin(); j++, it--)
                        _alloc.destroy(&tmp[j]);
                    _alloc.deallocate(tmp, new_size);
                    throw;
                }
            }
            if (_capacity != 0)
                _alloc.deallocate(_array, _capacity);
            _array = tmp;
            _numOfElem += n;
            _capacity = new_size;
        }

        iterator erase (iterator position) {
            if (position == this->end())
                return position;
            size_type i = position - begin();
            _alloc.destroy(_array + i);
            for (iterator it = position; it != this->end() - 1; i++, it++) {
                _alloc.construct(&_array[i], _array[i + 1]);
                _alloc.destroy(&_array[i + 1]);
            }
            _numOfElem--;
            return position;
        }

        iterator erase (iterator first, iterator last) {
            if (first >= last)
                return first;
            size_type EraseDist = last - first;
            size_type EraseBegin = first - begin();
            for (size_type i = 0; i < EraseDist; i++)
                _alloc.destroy(_array + EraseBegin + i);
            for (size_type i = EraseBegin + EraseDist; i < _numOfElem; i++) {
                _alloc.construct(&_array[i - EraseDist], _array[i]);
                _alloc.destroy(&_array[i]);
            }
            _numOfElem -= EraseDist;
            return first;
        }

        void swap (vector& x) {
            std::swap(_array, x._array);
            std::swap(_alloc, x._alloc);
            std::swap(_numOfElem, x._numOfElem);
            std::swap(_capacity, x._capacity);
        }


        void clear() {
            erase(begin(), end());
        }

        /*
         *  Allocator
         */

        allocator_type get_allocator() const {
            return _alloc;
        }
    };  // class vector

    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (lhs < rhs || lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs <= rhs);
    }

    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
        x.swap(y);
    }
}  // namespace ft

#endif  //  VECTOR_HPP_
