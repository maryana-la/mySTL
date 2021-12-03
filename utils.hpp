#ifndef UTILS_HPP_
#define UTILS_HPP_

namespace ft {

    /*
     *  type_traits
     */

    template<bool Cond, typename T = void>
    struct enable_if {};

    template<typename T>
    struct enable_if<true, T> { typedef T type; };

    /*try to implement like in source code
        template<typename T, T v>
        struct integral_constant {
            typedef T value_type;
            typedef ft::integral_constant<T, v> type;
            static const T value = v;
    //    const operator value_type() const {return value;}
        };

     The type used as a compile-time boolean with true value.
        using TrueType = ft::integral_constant<bool, true>;
    template<>
    struct integral_constant <bool, true> {
        typedef ft::integral_constant<bool, true> true_type;
    }

     The type used as a compile-time boolean with false value.
        using FalseType = ft::integral_constant<bool, false>;

    template<>
    struct integral_constant <bool, false> {
        typedef ft::integral_constant<bool, true> true_type;
    }


    template <>
    struct integral_constant<bool, true> { typedef ft::integral_constant<bool, true> true_type; };

    template <>
    struct integral_constant<bool, false> { typedef ft::integral_constant<bool, false> false_type; };

        template<typename T>
        struct is_integral : public FalseType {
        };

        template<>
    struct is_integral<bool> : public ft::integral_constant<true> {
        };
        template<>
        struct is_integral<char> : public  ft::integral_constant<true> {
        };
        template<>
        struct is_integral<char16_t> : public TrueType {
        };
        template<>
        struct is_integral<char32_t> : public TrueType {
        };
        template<>
        struct is_integral<signed char> : public TrueType {
        };
        template<>
        struct is_integral<wchar_t> : public TrueType {
        };
        template<>
        struct is_integral<short> : public TrueType {
        };
        template<>
        struct is_integral<int> : public TrueType {
        };
        template<>
        struct is_integral<long> : public TrueType {
        };
        template<>
        struct is_integral<long long int> : public TrueType {
        };
        template<>
        struct is_integral<unsigned char> : public TrueType {
        };
        template<>
        struct is_integral<unsigned short int> : public TrueType {
        };
        template<>
        struct is_integral<unsigned int> : public TrueType {
        };
        template<>
        struct is_integral<unsigned long int> : public TrueType {
        };
        template<>
        struct is_integral<unsigned long long int> : public TrueType {
        };
    */

    /* implementation is_integral */
    template <typename T>
    struct is_integral { static bool const value = false; };

    template <> struct is_integral<bool> { static bool const value = true; };
    template <> struct is_integral<char> { static bool const value = true; };
    template <> struct is_integral<char16_t> { static bool const value = true; };
    template <> struct is_integral<char32_t> { static bool const value = true; };
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


}  //  namespace ft

#endif  // UTILS_HPP_
