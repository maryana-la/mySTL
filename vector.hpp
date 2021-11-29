//
// Created by Ragwyle Chelsea on 11/9/21.
//

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include "iterator.hpp"
#include <iterator>
#include <memory>
#include <iostream>

namespace ft {

    template<typename T, typename Allocator = std::allocator<T> >
    class Vector {
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
        pointer             _endPoint; // указатель на конец
        size_type           _capacity; // выделенная память
        size_type           _numOfElem; // кол-во элементов
        allocator_type      _alloc; // некий механизм, с помощью которого будем выделять память

    public:
        /* Vector constructors */

//        (1) empty container constructor (default constructor)
        explicit vector (const allocator_type& alloc_var = allocator_type()) :
            _array(NULL), _endPoint(NULL), _capacity(0), _numOfElem(0), _alloc(alloc_var) {}

//        (2) fill constructor: Constructs a container with n elements. Each element is a copy of val.
        explicit vector (size_type n, const value_type& value = value_type(), const allocator_type& alloc_var = allocator_type()) : _numOfElem(n), _capacity(n), _alloc(alloc_var) {
            _array = _alloc.allocate(_capacity);
            for (size_type i = 0; i < n; i++)
                _alloc.construct(_array + i, value);
        };

//        (3) range constructor
//        template <typename InputIterator> //todo write functions below
//        Vector(InputIterator first, InputIterator last, const allocator_type& alloc_var = allocator_type(), typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()): _alloc(alloc) {
//            _numOfElem = std::distance(first, last);
//            _capacity= _numOfElem;
//            _array = _alloc.allocate(_size);
//            for (size_t i = 0; first != last; first++) {
//                _alloc.construct(&_array[i], *first);
//                i++;
//            }
//            return ;
//        }



//        (4) copy constructor
        vector (const vector& other) :
        {
//            this->_capacity = other.size();
//            this->countElem = 0;
//            this->alloc = other.alloc;
//            this->point = NULL;
//            this->endPoint = NULL;
//            size_type	length = other.size();
//
//            this->point = this->alloc.allocate(length);
//            this->endPoint = this->point;
//            for (size_type i  = 0; i < length; ++i)
//            {
//                this->alloc.construct(this->endPoint, *(other.point + i));
//                ++this->endPoint;
//            }
//            this->countElem = length;
        };

//        ~vector() {}
//        vector& operator= (const vector& x) {}


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

        //            Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
//        template <class InputIterator>
//        void assign (InputIterator first, InputIterator last) {
//            size_type distance = std::distance(first, last);
//            size_type position = 0;
//            if (distance > _numOfElem)
//                reserve(distance);
//            for (position = 0; first != last; first++ ) {
//                _alloc.construct(&_container[position++], *first);
//            }
//            for (; position < _size; position++) {
//                _alloc.destroy(&_container[position]);
//            }
//            _size = distance;
//
//        }

//todo check is needs to assign from the beginning and if destroyed previous info
        void assign (size_type n, const value_type& val) {
            if (n > _capacity)
                reserve(n);
            erase(begin(), end()); //todo write erase function
            _numOfElem = n;
            for (size_type i = 0; i < _numOfElem; i++) {
                _alloc.construct(&_array[i], val);
            }
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

        template <typename InputIterator >
        void insert (iterator position, InputIterator first, InputIterator last) {
                     typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = 0) {
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





        void clear() {

        }


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

    };
}


#endif  //  VECTOR_HPP_



//template <class T, class A = std::allocator<T> >
//        class X {
//        public:
//            typedef A allocator_type;
//            typedef typename A::value_type value_type;
//            typedef typename A::reference reference;
//            typedef typename A::const_reference const_reference;
//            typedef typename A::difference_type difference_type;
//            typedef typename A::size_type size_type;
//
//            class iterator {
//            public:
//                typedef typename A::difference_type difference_type;
//                typedef typename A::value_type value_type;
//                typedef typename A::reference reference;
//                typedef typename A::pointer pointer;
//                typedef std::random_access_iterator_tag iterator_category; //or another tag
//
//                iterator();
//                iterator(const iterator&);
//                ~iterator();
//
//                iterator& operator=(const iterator&);
//                bool operator==(const iterator&) const;
//                bool operator!=(const iterator&) const;
//                bool operator<(const iterator&) const; //optional
//                bool operator>(const iterator&) const; //optional
//                bool operator<=(const iterator&) const; //optional
//                bool operator>=(const iterator&) const; //optional
//
//                iterator& operator++();
//                iterator operator++(int); //optional
//                iterator& operator--(); //optional
//                iterator operator--(int); //optional
//                iterator& operator+=(size_type); //optional
//                iterator operator+(size_type) const; //optional
//                friend iterator operator+(size_type, const iterator&); //optional
//                iterator& operator-=(size_type); //optional
//                iterator operator-(size_type) const; //optional
//                difference_type operator-(iterator) const; //optional
//
//                reference operator*() const;
//                pointer operator->() const;
//                reference operator[](size_type) const; //optional
//            };

//            class const_iterator {
//            public:
//                typedef typename A::difference_type difference_type;
//                typedef typename A::value_type value_type;
//                typedef typename const A::reference reference;
//                typedef typename const A::pointer pointer;
//                typedef std::random_access_iterator_tag iterator_category; //or another tag
//
//                const_iterator ();
//                const_iterator (const const_iterator&);
//                const_iterator (const iterator&);
//                ~const_iterator();
//
//                const_iterator& operator=(const const_iterator&);
//                bool operator==(const const_iterator&) const;
//                bool operator!=(const const_iterator&) const;
//                bool operator<(const const_iterator&) const; //optional
//                bool operator>(const const_iterator&) const; //optional
//                bool operator<=(const const_iterator&) const; //optional
//                bool operator>=(const const_iterator&) const; //optional
//
//                const_iterator& operator++();
//                const_iterator operator++(int); //optional
//                const_iterator& operator--(); //optional
//                const_iterator operator--(int); //optional
//                const_iterator& operator+=(size_type); //optional
//                const_iterator operator+(size_type) const; //optional
//                friend const_iterator operator+(size_type, const const_iterator&); //optional
//                const_iterator& operator-=(size_type); //optional
//                const_iterator operator-(size_type) const; //optional
//                difference_type operator-(const_iterator) const; //optional
//
//                reference operator*() const;
//                pointer operator->() const;
//                reference operator[](size_type) const; //optional
//            };
//
//            typedef std::reverse_iterator<iterator> reverse_iterator; //optional
//            typedef std::reverse_iterator<const_iterator> const_reverse_iterator; //optional
//
//            X();
//            X(const X&);
//            ~X();
//
//            X& operator=(const X&);
//            bool operator==(const X&) const;
//            bool operator!=(const X&) const;
//            bool operator<(const X&) const; //optional
//            bool operator>(const X&) const; //optional
//            bool operator<=(const X&) const; //optional
//            bool operator>=(const X&) const; //optional
//
//            iterator begin();
//            const_iterator begin() const;
//            const_iterator cbegin() const;
//            iterator end();
//            const_iterator end() const;
//            const_iterator cend() const;
//            reverse_iterator rbegin(); //optional
//            const_reverse_iterator rbegin() const; //optional
//            const_reverse_iterator crbegin() const; //optional
//            reverse_iterator rend(); //optional
//            const_reverse_iterator rend() const; //optional
//            const_reverse_iterator crend() const; //optional
//
//            reference front(); //optional
//            const_reference front() const; //optional
//            reference back(); //optional
//            const_reference back() const; //optional
//            template<class ...Args>
//            void emplace_front(Args&&...); //optional
//            template<class ...Args>
//            void emplace_back(Args&&...); //optional
//            void push_front(const T&); //optional
//            void push_front(T&&); //optional
//            void push_back(const T&); //optional
//            void push_back(T&&); //optional
//            void pop_front(); //optional
//            void pop_back(); //optional
//            reference operator[](size_type); //optional
//            const_reference operator[](size_type) const; //optional
//            reference at(size_type); //optional
//            const_reference at(size_type) const; //optional
//
//            template<class ...Args>
//            iterator emplace(const_iterator, Args&&...); //optional
//            iterator insert(const_iterator, const T&); //optional
//            iterator insert(const_iterator, T&&); //optional
//            iterator insert(const_iterator, size_type, T&); //optional
//            template<class iter>
//            iterator insert(const_iterator, iter, iter); //optional
//            iterator insert(const_iterator, std::initializer_list<T>); //optional
//            iterator erase(const_iterator); //optional
//            iterator erase(const_iterator, const_iterator); //optional
//            void clear(); //optional
//            template<class iter>
//            void assign(iter, iter); //optional
//            void assign(std::initializer_list<T>); //optional
//            void assign(size_type, const T&); //optional
//
//            void swap(X&);
//            size_type size() const;
//            size_type max_size() const;
//            bool empty() const;
//
//            A get_allocator() const; //optional
//        };
//template <class T, class A = std::allocator<T> >
//        void swap(X<T,A>&, X<T,A>&); //optional