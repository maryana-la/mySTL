#ifndef UTILS_HPP_
#define UTILS_HPP_

namespace ft {

    /*
     *  type_traits
     */

    /* implementation enable_if */

    template<bool Cond, typename T = void>
    struct enable_if {};

    template<typename T>
    struct enable_if<true, T> { typedef T type; };

    /* implementation is_integral */

    template <typename T>
    struct is_integral { static bool const value = false; };

    template <> struct is_integral<bool> { static bool const value = true; };
    template <> struct is_integral<char> { static bool const value = true; };
//    template <> struct is_integral<char16_t> { static bool const value = true; }; not a 98 std
//    template <> struct is_integral<char32_t> { static bool const value = true; };
    template <> struct is_integral<signed char> { static bool const value = true; };
    template <> struct is_integral<wchar_t> { static bool const value = true; };
    template <> struct is_integral<short> { static bool const value = true; };
    template <> struct is_integral<int> { static bool const value = true; };
    template <> struct is_integral<long> { static bool const value = true; };
    template <> struct is_integral<long long int> { static bool const value = true; };
    template <> struct is_integral<unsigned char> { static bool const value = true; };
    template <> struct is_integral<unsigned short int> { static bool const value = true; };
    template <> struct is_integral<unsigned int> { static bool const value = true; };
    template <> struct is_integral<unsigned long int> { static bool const value = true; };
    template <> struct is_integral<unsigned long long int> { static bool const value = true; };

    template <bool Cond, typename T, typename F>
    struct conditional { typedef T type; };

    template <typename T, typename F>
    struct conditional<false, T, F> {typedef F type;};


    /*
     *  algorithm
     */


    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
            for (; first1 != last1; ++first1, ++first2) {
                if (*first1 != *first2)
                    return false;
            }
            return true;
    }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
        for (; first1 != last1; ++first1, ++first2) {
            if (!pred(*first1,*first2))
                return false;
        }
        return true;
    }

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                  InputIterator2 first2, InputIterator2 last2) {


        for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
            if (*first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
        }
        return ((first1 == last1) && (first2 != last2));
    }

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                  InputIterator2 first2, InputIterator2 last2, Compare comp) {
        for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
            if (comp(*first2, *first1))
                return false;
            else if (comp(*first1, *first2))
                return true;
        }
        return ((first1 == last1) && (first2 != last2));
    }


    // todo add std::distance and replace in vector.hpp

}  //  namespace ft

#endif  // UTILS_HPP_
