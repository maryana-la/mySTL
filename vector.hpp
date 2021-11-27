//
// Created by Ragwyle Chelsea on 11/9/21.
//

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include "iterator.hpp"
#include <iterator>

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

//        /* todo: change to my_iterator */
//        typedef std::random_access_iterator_tag

    private:
        pointer             _array; // указатель на выделенную память
        pointer             _endPoint; // указатель на конец
        size_type           _capacity; // выделенная память
        size_type           _numOfElem; // кол-во элементов
        allocator_type      _alloc; // некий механизм, с помощью которого будем выделять память

    public:
        // конструкторы vector
//        (1) empty container constructor (default constructor)
        explicit vector (const allocator_type& alloc_var = allocator_type()) :
            _array(NULL), _endPoint(NULL), _capacity(0), _numOfElem(0), _alloc(alloc_var) {}

//        (2) fill constructor: Constructs a container with n elements. Each element is a copy of val.
        vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc_var = allocator_type()) : _numOfElem(n), _capacity(n), _alloc(alloc_var) {
            _array = new value_type[n]();
            for (size_type i = 0; i < n; i++)
                _array[i] = val;
        };

//        (3) range constructor
//        template <class InputIterator> //todo write a function
//        vector (InputIterator first, InputIterator last, const allocator_type& alloc_var = allocator_type()) :
//        {
//            _array = NULL;
//            _endPoint = NULL;
//            _capacity = 0;
//            _numOfElem = 0;
//            _alloc = alloc_var;
//            assign(first, last);
//        };

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

        void assign( size_type count, const T& value );

        template< class InputIt >
        void assign( InputIt first, InputIt last );



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