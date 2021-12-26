#ifndef SET_HPP
#define SET_HPP


#include "tree.hpp"

namespace ft {

    template<typename Key, typename Compare = std::less<Key>,
            typename Alloc = std::allocator<Key> >
    class set : public tree<Key, Key, Key, Compare, Alloc> {
    public:
        typedef ft::tree<Key, Key, Key, Compare, Alloc> MyBase; //base

        typedef typename MyBase::key_type key_type;
        typedef typename MyBase::value_type value_type;

        typedef typename MyBase::key_compare key_compare;
        typedef typename MyBase::allocator_type allocator_type;

        typedef typename MyBase::reference reference;
        typedef typename MyBase::const_reference const_reference;
        typedef typename MyBase::pointer pointer;
        typedef typename MyBase::const_pointer const_pointer;


        typedef typename MyBase::iterator iterator;
        typedef typename MyBase::const_iterator const_iterator;
        typedef typename MyBase::reverse_iterator reverse_iterator;
        typedef typename MyBase::const_reverse_iterator const_reverse_iterator;

        typedef typename MyBase::size_type size_type;
        typedef typename MyBase::difference_type difference_type;

        typedef ft::TreeNode<Key> node_type;
        typedef node_type *node_pointer;

        // http://www.cplusplus.com/reference/map/map/value_comp/
        class value_compare { // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
            friend class set;
        protected:
            Compare comp;
            explicit value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object
        public:
            bool operator()(const value_type &x, const value_type &y) const {
                return comp(x, y);
            }
        };  // class value_compare

        /*
         *  Constructors
         */

        explicit set (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type()) : MyBase(comp, alloc) {}

        template<class InputIterator>
        set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) : MyBase(comp, alloc) {
            insert(first, last);
        }

        set(const set &x) : MyBase() {
            insert(x.begin(), x.end());
        }

        virtual ~set() { }

        set& operator=(const set& x) {
            if (*this == x)
                return *this;
            this->_alloc = x._alloc;
            this->_cmp = x._cmp;
            this->clear();
            insert(x.begin(), x.end());
            return *this;
        }

        /*
         *  Modifiers
         */

        ft::pair<iterator, bool> insert(const value_type& val) {
            if (this->_size == 0)
                return (ft::make_pair(iterator(MyBase::insertNode(val)), true));
            node_pointer it = this->_root;
            while (it) {
                if (val < it->value) {
                    if (it->left)
                        it = it->left;
                    else return ft::make_pair(iterator(MyBase::insertNode(val)), true);
                }
                else if (val > it->value) {
                    if (it->right)
                        it = it->right;
                    else return ft::make_pair(iterator(MyBase::insertNode(val)), true);
                }
                else
                    break ;
            }
            return ft::make_pair(iterator(it), false);
        }


        iterator insert(iterator position, const value_type &val) {
            (void) position;
            return insert(val).first;
        }

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
            InputIterator it = first;
            try
            {
                for (; it != last; it++)
                    insert(*it);
            }
            catch(...) {
                InputIterator it1 = first;
                for (; it1 != it; it++)
                    this->erase(it1.getNode());
                throw;
            }
        }

        value_compare value_comp() const { return value_compare(this->_cmp); }

    };  // class set

    template<class Key, class Compare, class Alloc>
    bool operator==(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs) {
        return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template<class Key,  class Compare, class Alloc>
    bool operator!=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs) {
        return !(lhs == rhs);
    }

    template<class Key, class Compare, class Alloc>
    bool operator<(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template<class Key, class Compare, class Alloc>
    bool operator<=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs) {
        return (lhs < rhs || lhs == rhs);
    }

    template<class Key, class Compare, class Alloc>
    bool operator>(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs) {
        return !(lhs <= rhs);
    }

    template<class Key, class Compare, class Alloc>
    bool operator>=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs) {
        return !(lhs < rhs);
    }

    template <class T, class Compare, class Alloc>
    void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y) {
        x.swap(y);
    }

}  //  namespace ft

#endif  //  SET_HPP
