#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"

template<typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
class map {
public:
    typedef T      key_type;
    typedef T      value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
    typedef TreeNode<T>    node_type;
    typedef node_type*      node_pointer;

    typedef Alloc                               allocator_type;
    typedef T&                                  reference;
    typedef const T&                            const_reference;
    typedef T*                                  pointer;
    typedef const T*                            const_pointer;
    typedef ptrdiff_t                           difference_type;
    typedef size_t                              size_type;
    typedef ft::TreeIterator<T, false>         iterator;
    typedef ft::TreeIterator<T, true>          const_iterator;
    typedef ft::ReverseIterator<iterator>       reverse_iterator;
    typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

/*
+set::begin
set::clear
set::count
+set::empty
+set::end
set::equal_range
set::erase
set::find
+set::get_allocator
set::insert
+set::key_comp
set::lower_bound
+set::max_size
set::operator=

            operator[]  map

+set::rbegin
+set::rend
+set::size
set::swap
set::upper_bound
set::value_comp

 non-member overloads:
relational operators (set)
swap (set)


    */

};  // class map



#endif // MAP_HPP
