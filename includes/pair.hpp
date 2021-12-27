#ifndef _PAIR_HPP
#define _PAIR_HPP

namespace ft {

    template<typename T1, typename T2>
    struct pair {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        /* constructors */
        pair() : first(), second() {}

        pair(const T1 &a, const T2 &b) : first(a), second(b) {}

        template<typename U, typename V>
        pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

        pair &operator=(const pair &other) {
            if (*this == other)
                return *this;
            this->first = other.first;
            this->second = other.second;
            return *this;
        }
    };  //  struct pair

    template<class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template<class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(lhs == rhs);
    }

    template<class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
    }

    template<class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (!(rhs < lhs));
    }

    template<class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (rhs < lhs);
    }

    template<class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (!(lhs < rhs));
    }

    template<class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y) {
        return (pair<T1, T2>(x, y));
    }

//    template<class T1, class T2>
//    std::ostream &operator<<(std::ostream &out, const pair<T1, T2> toPrint) {
//        out << toPrint.first << " " << toPrint.second;
//        return out;
//    }

}  //  namespace ft

#endif //_PAIR_HPP
