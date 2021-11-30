
#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include "iterator.hpp"
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
        typedef RandomAccessIterator<T>         iterator;
        typedef RandomAccessIterator<const T>   const_iterator;
        typedef ReverseIterator<iterator>       reverse_iterator;
        typedef ReverseIterator<const_iterator> const_reverse_iterator;

    private:
        pointer             _array; // указатель на выделенную память
        size_type           _capacity{}; // выделенная память
        size_type           _numOfElem{}; // кол-во элементов
        allocator_type      _alloc; // некий механизм, с помощью которого будем выделять память

    public:
        /* Vector constructors */

//        (1) empty container constructor (default constructor)
        explicit vector (const allocator_type& alloc = allocator_type()) :
            _array(NULL), _capacity(0), _numOfElem(0), _alloc(alloc) {}

//        (2) fill constructor: Constructs a container with n elements. Each element is a copy of val.
        explicit vector (size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()) :
                        _numOfElem(n), _capacity(n), _alloc(alloc) {
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

//        (3) range constructor
        template <typename InputIterator> //todo write functions below
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
               typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = 0): _alloc(alloc), _array(NULL) {
            _numOfElem = std::distance(first, last);
            _capacity= _numOfElem;
            insert(begin(), first, last);
//            _array = _alloc.allocate(_capacity);
//            for (size_t i = 0; first != last; first++) {
//                _alloc.construct(&_array[i], *first);
//                i++;
//            }
//            return ;
        }

//        (4) copy constructor
        vector (const vector& other) {
            this->_numOfElem = other.size();
            this->_capacity = other.capacity();
            this->_alloc = other.get_allocator();

            _alloc.allocate(_numOfElem);
            insert(begin(), other.begin(), other.end());
//            for (size_type i  = 0; i < length; ++i)
//            {
//                this->alloc.construct(this->endPoint, *(other.point + i));
//                ++this->endPoint;
//            }
//            this->countElem = length;
        };

        ~vector() {
            if (!empty()) {
                for (size_type i = 0; i < _numOfElem; i++)
                    _alloc.destroy(&_array[i]);
                _alloc.deallocate(_array);
            }
        }


        vector& operator= (const vector& other) {
            clear();
            insert(begin(),other.begin(), other.end());
            return *this;
        }


        /* Iterators */
        /*
            begin: Return iterator to beginning (public member function )
            end: Return iterator to end (public member function )
            rbegin: Return reverse iterator to reverse beginning (public member function )
            rend: Return reverse iterator to reverse end (public member function )
         */

        iterator begin() { return _array; }
        const_iterator begin() const { return (const_iterator(_array)); }

        iterator end() { return (_array + _numOfElem); }
        const_iterator end() const { return (const_iterator(_array + _numOfElem)); }

        reverse_iterator rbegin() { return (reverse_iterator(end())); }
        const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }

        reverse_iterator rend() { return (reverse_iterator(begin())); }
        const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }


        /* Capacity */
        /*
            size: Return size (public member function )
            max_size: Return maximum size (public member function )
            resize: Change size (public member function )
            capacity: Return size of allocated storage capacity (public member function )
            empty: Test whether vector is empty (public member function )
            reserve: Request a change in capacity (public member function )
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

        /* Element access */
        /*
            operator[]: Access element (public member function )
            at: Access element (public member function )
            front: Access first element (public member function )
            back: Access last element (public member function )
            data: Access data (public member function )
        */

        reference operator[] (size_type n) { return (_array[n]); }
        const_reference operator[] (size_type n) const { return (_array[n]); }

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


        /* Modifiers */
        /*
            assign: Assign vector content (public member function )
            push_back: Add element at the end (public member function )
            pop_back: Delete last element (public member function )
            insert: Insert elements (public member function )
            erase: Erase elements (public member function )
            swap: Swap content (public member function )
            clear: Clear content (public member function )
        */

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last,
                     typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = 0) {

            erase(begin(), end());
            insert(begin(), first, last);

            // my code:

//            size_type distance = std::distance(first, last);
//            if (distance > _numOfElem)
//                reserve(distance);
//            size_type i = 0;
//            for (; first != last; first++, i++)
//                _alloc.construct(&_array[i], *first);
//            for (; i < _numOfElem; i++) {
//                _alloc.destroy(&_array[i]);
//            }
//            _numOfElem = distance;
        }

        void assign (size_type n, const value_type& val) {
//            my code:
//            if (n > _capacity)
//                reserve(n);
//            erase(begin(), end());
//            insert(begin(), n, val);
//            _numOfElem = n;
//            for (size_type i = 0; i < _numOfElem; i++)
//                _alloc.construct(&_array[i], val);

            value_type& tmp = val;
            erase(begin(), end());
            insert(begin(), n, tmp);
        }

        void push_back (const value_type& val) {
            //todo should throw exception
            if (_numOfElem == 0)
                reserve(1);
            else if (_numOfElem + 1 > _capacity)
                reserve(_capacity * 2);
            _alloc.construct(&_array[_numOfElem], val);
            _numOfElem += 1;
        }

        void pop_back() {
//            if (_numOfElem == 0)
//                return ; //todo no need for this check
            _alloc.destroy(&_array[_numOfElem]);
            _numOfElem -= 1;
        }

        iterator insert(iterator position, const value_type& val) {
            this->insert(position, 1, val);
            return position;
        }

//todo not sure if works correctly, can be simplified; what if position > _numOfElem?
        void insert(iterator position, size_type n, const value_type& val) {
            if (n == 0)
                return ;
            else if (max_size() - size() < n)
                throw std::length_error("vector<T> too long");
            size_type new_size;
            if (_capacity < _numOfElem + n)
                new_size = (n > _numOfElem ? _numOfElem + n : _capacity * 2);

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
            else {// Insert near the end
                size_type InsertPos = std::distance(begin(), position);
                size_type i = 0;
                try {
                    for (; i < InsertPos; i++)
                        _alloc.construct(&tmp[i], _array[i]);
                    for (; i < InsertPos + n; i++)
                        _alloc.construct(&tmp[InsertPos + i], val);
                    for (; i > _numOfElem + n; i++)
                        _alloc.construct(&tmp[i], _array[i + n]);
                }
                catch (...) {
                    for (size_type j = 0; j < i; j++)
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
//            from the book
/*
            pointer tmp(new_size);
            pointer Q;
            if (position > begin()) {
                try {
                    Q = Ucopy(begin(), position, tmp);
                    Q = Ufill(Q, n, val);
                    Ucopy(position, end(), tmp;)
                }
                catch {
                    Destroy(tmp, Q);
                    _alloc.deallocate(tmp, new_size);
                    throw;
                }
                if (_array != 0) {
                    Destroy(_array, back());
                    _alloc.deallocate(_array, size())
                }
                _array = tmp;
            } */
        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last) {
//            from the book
            for (; first != last; ++first, ++position)
                position = insert(position, *first);
        }

//        the same, but different realization
        template <typename InputIterator >
        void insert (iterator position, InputIterator first, InputIterator last,
                     typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = 0) {
            size_type pos = position - begin();
            size_type s = last - first;
            if (_numOfElem + s > _capacity)
                reserve(_numOfElem + s);
            position = begin() + pos;
            for (InputIterator it = first; it != last; ++it) {
                position = insert(position, *it);
                position++;
            }
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

        /* Allocator */

        allocator_type get_allocator() const {
            return _alloc;
        }

/* from the book/ used for insert
    protected:
        void Destroy(pointer first, pointer last) {
            for (; first != last; ++first)
                _alloc.destroy(first);
        }

        template<typename It>
        pointer Ucopy(It first, It last, ponter array) {
            pointer arr = array;
            try {
                for (; first != last; ++array, ++first)
                    _alloc.construct(array, *first);
            }
            catch (...) {
                Destroy(arr, array);
                throw;
            }
            return array;
        }

        pointer Ufill(pointer array, size_type n, const_reference x) {
            pointer arr = array;
            try {
                for (; array < n; --n, ++array)
                    _alloc.construct(array, x)
            }
            catch (...) {
                Destroy(arr, array);
                throw;
            }
            return array;
        }
*/
    };



//    template <class T, class Alloc>
//    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
//
//    template <class T, class Alloc>
//    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
//
//    template <class T, class Alloc>
//    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
//
//    template <class T, class Alloc>
//    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
//
//    template <class T, class Alloc>
//    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
//
//    template <class T, class Alloc>
//    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
//

}


#endif  //  VECTOR_HPP_
