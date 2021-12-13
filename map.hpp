#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"

namespace ft {

    template<typename Key, typename Value, typename Compare = std::less<Key>,
            typename Alloc = std::allocator<ft::pair<const Key, Value> > >
    class map {
    public:
        typedef Key key_type;
        typedef Value mapped_type;
        typedef ft::pair<const Key, Value> value_type;
        typedef Compare key_compare;
        typedef ft::TreeNode<ft::pair<const Key, Value> > node_type;
        typedef node_type *node_pointer;

        typedef Alloc allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef ft::TreeIterator<value_type, false> iterator;
        typedef ft::TreeIterator<value_type, true> const_iterator;
        typedef ft::ReverseIterator<iterator> reverse_iterator;
        typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

        class value_compare {
            friend class map;

        protected:
            Compare comp;

            value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object
        public:
            bool operator()(const value_type &x, const value_type &y) const {
                return comp(x.first, y.first);
            }
        };

    private:
        typedef ft::tree<key_type, mapped_type, value_type> tree_type;
        tree_type _tree;
        key_compare _comp;

    public:

        /*
         *  Constructors
         */

        map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
                _tree(), _comp(comp) {}

        template<class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) {
            insert(first, last);
        }

        map(const map &x) : _comp(x._comp) {
            _tree = x._tree;
        }

        ~map() {
            _tree.~tree();
        }

        map &operator=(const map &x) {
            _comp = x._comp;
            _tree = x._tree;
            return *this;
        }

        /*
         *  Iterators
         */

        iterator begin() { return _tree.begin(); }

        const_iterator begin() const { return const_iterator(_tree.begin()); }

        iterator end() { return iterator(_tree.end()); }

        const_iterator end() const { return const_iterator(_tree.end()); }

        reverse_iterator rbegin() { return reverse_iterator(_tree.rbegin()); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(_tree.rbegin()); }

        reverse_iterator rend() { return reverse_iterator(_tree.rend()); }

        const_reverse_iterator rend() const { return const_reverse_iterator(_tree.rend()); }

        /*
         *  Capacity
         */

        size_type size() const { return _tree.size(); }

        size_type max_size() const { return _tree.max_size(); /* _node_alloc.max_size();*/ } //todo or node_alloc
        bool empty() const { return _tree.empty(); }

        /*
         *  Element access
         */

        mapped_type &operator[](const key_type &k) {
            return insert(ft::make_pair(k, mapped_type())).first->second;
        }

        /*
         *  Modifiers
         */

        ft::pair<iterator, bool> insert(const value_type &val) {
            _tree.insertNode(val);
        }

        //todo do smth with iterator
        iterator insert(iterator position, const value_type &val) {
            _tree.insertNode(val);
        }


        template<class InputIterator>
        void insert(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
            _tree.insertIter(first, last);
        }


        void erase(iterator position) {
            _tree.deleteNode(*position);
        }

        size_type erase(const key_type &k) {
            _tree.deleteNode(k);
        }

        void erase(iterator first, iterator last) {
            _tree.deleteIter(first, last);
        }

        void swap(map &x) {
            _tree.swap(x._tree);
            std::swap(_comp, x._comp);
        }

        void clear() {
            _tree.clear();
        }

        /*
         *  Observers
         */

        key_compare key_comp() const { return _comp; }

        value_compare value_comp() const { return value_compare(_comp); }

        /*
         *  Operations
         */

        iterator find(const key_type &k) {
            return (_tree.find(k));
        }

        const_iterator find(const key_type &k) const {
            return (const_iterator(_tree.find(k)));
        }

        size_type count(const key_type &k) const {
            return (_tree.count(k));
        }

        iterator lower_bound(const key_type &k) {
            iterator it = begin();
            iterator ite = end();

            for (; it != ite; it++) {
                if (!key_comp()(*it, k))
                    break;
            }
            return it;
        }

        const_iterator lower_bound(const key_type &k) const {
            const_iterator it = begin();
            const_iterator ite = end();

            for (; it != ite; it++) {
                if (!key_comp()(*it, k))
                    break;
            }
            return it;
        }

        iterator upper_bound(const key_type &k) {
            iterator it = begin();
            iterator ite = end();

            for (; it != ite; it++) {
                if (key_comp()(*it, k))
                    break;
            }
            return it;
        }

        const_iterator upper_bound(const key_type &k) const {
            const_iterator it = begin();
            const_iterator ite = end();

            for (; it != ite; it++) {
                if (key_comp()(*it, k))
                    break;
            }
            return it;
        }

        ft::pair<iterator, iterator> equal_range(const key_type &k) {
            return (ft::make_pair(iterator(lower_bound(k)), iterator(upper_bound(k))));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
            return (ft::make_pair(const_iterator(lower_bound(k)), const_iterator(upper_bound(k))));
        }

        /*
         *  Allocator
         */

        allocator_type get_allocator() const { return _tree.get_allocator(); }

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
        return (rhs < lhs);
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return (lhs <= rhs);
    }

    template<class Key, class T, class Compare, class Alloc>
    bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return !(lhs < rhs);
    }

}  //  namespace ft


#endif // MAP_HPP
