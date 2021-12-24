#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"

namespace ft {

    template<typename Key, typename Value, typename Compare = std::less<Key>,
            typename Alloc = std::allocator<ft::pair<const Key, Value> > >
    class map : public tree<const Key, Value, ft::pair<const Key, Value>, Compare, Alloc> {
    public:
        typedef ft::tree<const Key, Value, ft::pair<const Key, Value>, Compare, Alloc> MyBase; //base

        typedef Value mapped_type;
        typedef Compare key_compare;

        typedef typename MyBase::value_type value_type;
        typedef typename MyBase::key_type key_type;
//        typedef typename MyBase::value_compare value_compare;
        typedef typename MyBase::allocator_type allocator_type;
        typedef typename MyBase::size_type size_type;
        typedef typename MyBase::difference_type difference_type;

        typedef typename MyBase::pointer pointer;
        typedef typename MyBase::const_pointer const_pointer;
        typedef typename MyBase::reference reference;
        typedef typename MyBase::const_reference const_reference;
        typedef typename MyBase::iterator iterator;
        typedef typename MyBase::const_iterator const_iterator;
        typedef typename MyBase::reverse_iterator reverse_iterator;
        typedef typename MyBase::const_reverse_iterator const_reverse_iterator;

        typedef ft::TreeNode<ft::pair<const Key, Value> > node_type;
        typedef node_type *node_pointer;

        // http://www.cplusplus.com/reference/map/map/value_comp/
        class value_compare { // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
            friend class map;
        protected:
            Compare comp;
            explicit value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object
        public:
            bool operator()(const value_type &x, const value_type &y) const {
                return comp(x.first, y.first);
            }
        };  // class value_compare

        /*
         *  Constructors
         */

        explicit map (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type()) : MyBase(comp, alloc) {}

        template<class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) : MyBase(comp, alloc) {
            insert(first, last);
        }

        map(const map &x) : MyBase() {
            insert(x.begin(), x.end());
        }

        virtual ~map() { }

        map& operator=(const map& x) {
            if (*this == x)
                return *this;
            this->_alloc = x._alloc;
            this->_cmp = x._cmp;
            this->clear();
            insert(x.begin(), x.end());
            return *this;
        }

        /*
         *  Element access
         */

        mapped_type &operator[](const key_type &k) {
            return insert(ft::make_pair(k, mapped_type())).first->second;
        }

        /*
         *  Modifiers
         */

        ft::pair<iterator, bool> insert(const value_type& val) {
            if (this->_size == 0)
                return (ft::make_pair(iterator(MyBase::insertNode(val)), true));
            node_pointer it = this->_root;
            while (it) {
                if (val.first < it->value.first) {
                    if (it->left)
                        it = it->left;
                    else return ft::make_pair(iterator(MyBase::insertNode(val)), true);
                }
                else if (val.first > it->value.first) {
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
        

    };  // class map

    template<class Key, class T, class Compare, class Alloc>
    bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return !(lhs == rhs);
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return (lhs < rhs || lhs == rhs);
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return !(lhs <= rhs);
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return !(lhs < rhs);
    }

}  //  namespace ft


#endif // MAP_HPP
