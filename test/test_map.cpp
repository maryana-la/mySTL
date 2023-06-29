#include <iostream>
#include <cmath>
#include "../includes/color.hpp"

#ifdef FT
# define NS ft
# include "../includes/map.hpp"
#else
# define NS std
#include <map>
#endif

template <typename Key, typename T>
void print_tree(NS::map<Key, T> &tree) {
    typename NS::map<Key, T>::iterator it = tree.begin();
    typename NS::map<Key, T>::iterator ite = tree.end();

    int flag = 1;
    for (;it != ite; it++, flag++) {
        std::cout << CYAN << it->first << RESET << " => " << it->second << " | ";
        if (!(flag % 10))
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

static void test_insert() {
    {
        std::cout << MAGENTA << "***** INSERT TESTS ****" << RESET << std::endl;
        std::cout << "---- insert single element ----" << std::endl;
        NS::map<int, int> mytree;
        mytree.insert(NS::make_pair(10, 3));
        mytree.insert(NS::make_pair(110, 2));
        mytree.insert(NS::make_pair(15, 3));
        mytree.insert(NS::make_pair(7, 5));
        mytree.insert(NS::make_pair(35, 5));
        mytree.insert(NS::make_pair(2, 3));
        mytree.insert(NS::make_pair(0, 3));
        mytree.insert(NS::make_pair(110, 3));
        mytree.insert(NS::make_pair(110, 4));
        mytree.insert(NS::make_pair(110, 5));
        mytree.insert(NS::make_pair(110, 5));
        std::cout << "trying to insert keys: 10, 110, 15, 7, 35, 2, 0, 110, 110, 110, 110" << std::endl;

        print_tree(mytree);
//    mytree.inOrderPrint();
        std::cout << std::endl;

        std::cout << "---- insert with hint ----" << std::endl;
        NS::map<int, int>::iterator it = mytree.begin();
        it++;
        std::cout << "trying to insert key -1 at position begin()++" << std::endl;
        mytree.insert(it, NS::make_pair(-1, 15));
        print_tree(mytree);
//    mytree.inOrderPrint();
        std::cout << std::endl;

        std::cout << "---- insert range ----" << std::endl;
        NS::map<int, int> map1;
        NS::map<int, int>::iterator ite = mytree.end();
        it = mytree.begin();
        it++;
        ite--;
        std::cout << "trying to insert keys from begin()++ till end()--" << std::endl;
        map1.insert(it, ite);
        print_tree(map1);
//    map1.inOrderPrint();
        std::cout << std::endl;

        std::cout << "---- insert check return value ----" << std::endl;
        NS::map<char, int> tree1;
        NS::pair<NS::map<char, int>::iterator, bool> ret1;
        for (int i = 'a'; i <= 'z'; i++) {
            ret1 = tree1.insert(NS::make_pair((char)i, i));
            if (!ret1.second)
                std::cout << i << " already exists" << std::endl;
        }
        print_tree(tree1);
        for (int i = 'a'; i <= 'z'; i++) {
            ret1 = tree1.insert(NS::make_pair((char)i, i));
            if (!ret1.second)
                std::cout << (char)i << " already exists" << std::endl;
        }
    }
}

static void test_erase() {
    std::cout << MAGENTA << "\n***** ERASE TESTS ****" << RESET << std::endl;
    NS::map<int, int> myt;
    NS::pair<NS::map<int, int>::iterator, bool> ret1;
    for (int i = 0; i < 100 ; i++) {
        ret1 = myt.insert(NS::make_pair(i, i * i));
        if (!ret1.second)
            std::cout << i << " already exists" << std::endl;
    }
    std::cout << "My map contains:\n";
    print_tree(myt);

    std::cout << "---- erase position ----" << std::endl;
    NS::map<int, int>::iterator it;
    it = myt.find(20);
    myt.erase(it);
    std::cout << "Find node with key 20, delete it via iterator\n";
    print_tree(myt);
    std::cout << std::endl;

    std::cout << "---- erase single element ----" << std::endl;
    size_t ret;
    ret = myt.erase(5);
    std::cout << "Delete node with key 5, check return value\n";
    std::cout << "Return value: " << ret << std::endl;
    print_tree(myt);
    ret = myt.erase(150);
    std::cout << "Delete node with key 150, check return value\n";
    std::cout << "Return value: " << ret << std::endl;
    std::cout << std::endl;

    std::cout << "---- erase range ----" << std::endl;
    myt.erase(myt.find(17), myt.find(40));
    std::cout << "Delete range from 17 till 40\n";
    print_tree(myt);
}

static void test_swap() {
    std::cout << MAGENTA << "\n***** SWAP TESTS ****" << RESET << std::endl;
    NS::map<char,int> map1,map2;

    map1['x']=100;
    map1['y']=200;

    map2['a']=11;
    map2['b']=22;
    map2['c']=33;

    std::cout << "map1 contains: ";
    std::cout << "size " << map1.size() << ": ";
    print_tree(map1);
    std::cout << "map2 contains: ";
    std::cout << "size " << map2.size() << ": ";
    print_tree(map2);

    map1.swap(map2);

    std::cout << "After SWAP\nmap1 contains: ";
    std::cout << "size " << map1.size() << ": ";
    print_tree(map1);
    std::cout << "map2 contains: ";
    std::cout << "size " << map2.size() << ": ";
    print_tree(map2);
}

static void test_clear() {
    std::cout << MAGENTA << "\n***** CLEAR TESTS ****" << RESET << std::endl;

    NS::map<char,int> mymap;

    mymap['x']=100;
    mymap['y']=200;
    mymap['z']=300;
    std::cout << "my_map contains: size " << mymap.size() << ": ";
    print_tree(mymap);

    mymap.clear();
    std::cout << "Is empty? " << mymap.empty() << std::endl;
    mymap['a']=1101;
    mymap['b']=2202;
    std::cout << "my_map contains: size " << mymap.size() << ": ";
    print_tree(mymap);
}

static void test_capacity() {
    std::cout << MAGENTA << "\n***** CAPACITY TESTS ****" << RESET << std::endl;
    NS::map<int, char> mymap;

    mymap[0]='h';
    mymap[1]='e';
    mymap[5]='l';
    for (int i = 7; i <= 20; i += 2) {
        mymap.insert(NS::make_pair(i, (char)(i + 90)));
    }
    std::cout << "my_map contains: ";
    print_tree(mymap);
    std::cout << "is empty: " << mymap.empty() << std::endl;
    std::cout << "size: " << mymap.size() << std::endl;
    std::cout << "max_size: " << mymap.max_size() << std::endl;

    mymap[10] = 'w';
    std::cout << "AFTER ADDING [10] = w\nmy_map contains: ";
    print_tree(mymap);
    std::cout << "is empty: " << mymap.empty() << std::endl;
    std::cout << "size: " << mymap.size() << std::endl;
    std::cout << "max_size: " << mymap.max_size() << std::endl;

    mymap.clear();
    std::cout << "AFTER clear()\nmy_map contains: ";
    print_tree(mymap);
    std::cout << "is empty: " << mymap.empty() << std::endl;
    std::cout << "size: " << mymap.size() << std::endl;
    std::cout << "max_size: " << mymap.max_size() << std::endl;
}

static void test_elem_access() {
    std::cout << MAGENTA << "\n***** ELEMENT ACCESS TESTS ****" << RESET << std::endl;
    NS::map<int, char> mymap;

    mymap[0]='h';
    mymap[1]='e';
    mymap[5]='l';
    for (int i = 7; i <= 20; i += 2) {
        mymap.insert(NS::make_pair(i, (char)(i + 90)));
    }
    std::cout << "my_map contains: ";
    print_tree(mymap);

    std::cout << "element with key 7 => " << mymap[7] << std::endl;
    std::cout << "element with key 105 => " << mymap[105] << std::endl;
    print_tree(mymap);
    mymap[105] = 'e';
    std::cout << "element with key 105 => " << mymap[105] << std::endl;
    mymap[105] = 'w';
    std::cout << "element with key 105 => " << mymap[105] << std::endl;
    mymap[105] = 'g';
    std::cout << "element with key 105 => " << mymap[105] << std::endl;
    print_tree(mymap);
}

static void test_iterators() {
    std::cout << MAGENTA << "\n***** ITERATOR TESTS ****" << RESET << std::endl;
    NS::map<int, char> mymap;

    mymap[2]='h';
    mymap[4]='e';
    mymap[5]='l';
    for (int i = 7; i <= 20; i += 2) {
        mymap.insert(NS::make_pair(i, (char)(i + 90)));
    }

    std::cout << "my_map print via direct iterators: ";
    print_tree(mymap);

    NS::map<int, char>::iterator it;
    it = mymap.find(11);
    std::cout << it->first << " " << it->second << std::endl;
    mymap.erase(mymap.find(9), mymap.find(21));
    std::cout << it->first << " " << it->second << std::endl;


    NS::map<int, char>::reverse_iterator rit = mymap.rbegin();
    NS::map<int, char>::reverse_iterator rite = mymap.rend();
    std::cout << "my_map print via reverse iterators: ";
    int flag = 1;
    for (; rit != rite; rit++, flag++){
        std::cout << CYAN << rit->first << RESET << " => " << rit->second << " | ";
        if (!(flag % 10))
            std::cout << std::endl;
    }
}

static void test_observers() {
    std::cout << MAGENTA << "\n***** OBSERVERS TESTS ****" << RESET << std::endl;
    {
        NS::map<int, char> mymap;
        mymap[2] = 'h';
        mymap[4] = 'e';
        mymap[5] = 'l';
        for (int i = 7; i <= 20; i += 2)
            mymap.insert(NS::make_pair(i, (char) (i + 90)));

        NS::map<int, char>::key_compare mycomp = mymap.key_comp();

        std::cout << "mymap contains:\n";
        print_tree(mymap);

        int highest = 13;
        std::cout << "Print values less than 12 (key_compare):\n";
        NS::map<int, char>::iterator it = mymap.begin();
        for (; mycomp((*it).first, highest); it++) {
            std::cout << it->first << " => " << it->second << " | ";
        }
        std::cout << std::endl;
    }
    {
        NS::map<int, char> mymap;
        mymap[2]='h';
        mymap[4]='e';
        mymap[5]='l';
        for (int i = 7; i <= 20; i += 2)
            mymap.insert(NS::make_pair(i, (char)(i + 90)));

        NS::pair<int, char> highest = NS::make_pair(10, 'g');          // last element

        std::cout << "Print values less than <10, 'g'> (value_compare):\n";
        NS::map<int, char>::iterator it1 = mymap.begin();
        for(; mymap.value_comp()(*it1, highest); it1++)
            std::cout << it1->first << " => " << it1->second << " | ";
        std::cout << std::endl;
    }
}

static void test_find() {
    std::cout << MAGENTA << "\n***** FIND TESTS ****" << RESET << std::endl;
    NS::map<int, char> mymap;
    for (int i = 1; i <= 26; i++)
        mymap.insert(NS::make_pair(i, (char) (i + 96)));
    std::cout << "mymap contains:\n";
    print_tree(mymap);

    NS::map<int, char>::iterator it;
    it = mymap.find(22);
    std::cout << "Find key 22: " << it->first << " => " << it->second << std::endl;
    mymap.erase(mymap.begin(), it);
    std::cout << "Erase from begin() till find(22). Now mymap contains:\n";
    print_tree(mymap);
}

static void test_count() {
    std::cout << MAGENTA << "\n***** COUNT TESTS ****" << RESET << std::endl;
    NS::map<char, int> mymap;
    for (int i = 1; i <= 10; i++)
        mymap.insert(NS::make_pair((char) (i + 96), i));
    std::cout << "mymap contains:\n";
    print_tree(mymap);
    std::cout << std::endl;
    char c;

    for (c = 'a'; c <= 'z'; c++)
    {
        std::cout << c;
        if (mymap.count(c) > 0)
            std::cout << " is an element of mymap.\n";
        else
            std::cout << " is not an element of mymap.\n";
    }

}

static void test_lower_bound() {
    std::cout << MAGENTA << "\n***** LOWER/UPPER_BOUND TESTS ****" << RESET << std::endl;
    NS::map<int, char> mymap;
    for (int i = 1; i <= 26; i++)
        mymap.insert(NS::make_pair(i, (char) (i + 96)));
    std::cout << "mymap contains:\n";
    print_tree(mymap);

    NS::map<int, char>::iterator itlow,itup;

    itlow = mymap.lower_bound (5);  // itlow points to b
    std::cout << "lower_bound: " << itlow->first << " => " << itlow->second << '\n';
    itup = mymap.upper_bound (12);   // itup points to e (not d!)
    std::cout << "upper_bound: " << itup->first << " => " << itup->second << '\n';

    mymap.erase(itlow,itup);        // erases [itlow,itup)

    std::cout << "Erase from lower_bound till upper_bound:\n";
    print_tree(mymap);
}

static void test_equal_range() {
    std::cout << MAGENTA << "\n***** EQUAL_RANGE TESTS ****" << RESET << std::endl;

    NS::map<char, int> mymap;
    for (int i = 1; i <= 10; i++)
        mymap.insert(NS::make_pair((char) (i + 96), i));
    std::cout << "mymap contains:\n";
    print_tree(mymap);

    NS::pair<NS::map<char,int>::iterator,NS::map<char,int>::iterator> ret;
    ret = mymap.equal_range('b');

    std::cout << "equal_range for 'b':\nlower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << '\n';

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

static void test_allocator() {
    std::cout << MAGENTA << "\n***** ALLOCATOR TESTS ****" << RESET << std::endl;
    int psize;
    NS::pair<const char,int>* p;
    NS::map<char, int> mymap;

    std::cout << "Allocate an array of 5 elements using mymap's allocator:\n";
    p=mymap.get_allocator().allocate(5);

    psize = sizeof(NS::map<char,int>::value_type) * 5;

    std::cout << "The allocated array has a size of " << psize << " bytes.\n";

    mymap.get_allocator().deallocate(p,5);
}

static void test_relational_operators() {
    std::cout << MAGENTA << "\n***** RELATIONAL_OPERATORS TESTS ****" << RESET << std::endl;

    NS::map<char,int> foo,bar;
    foo['a']=10;
    foo['b']=200;
    bar['a']=100;
    bar['t']=1000;
    std::cout << "foo tree: ";
    print_tree(foo);
    std::cout << "bar tree: ";
    print_tree(bar);

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
    std::cout << std::endl;
    foo.clear();
    foo['a']=100;
    foo['z']=200;
    bar['a']=100;
    bar['t']=1000;
    std::cout << "foo tree: ";
    print_tree(foo);
    std::cout << "bar tree: ";
    print_tree(bar);

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

static void test_swap_non_mem() {
    std::cout << MAGENTA << "\n***** SWAP_NON-MEMBER TESTS ****" << RESET << std::endl;

    NS::map<char,int> foo,bar;

    foo['x']=100;
    foo['y']=200;

    bar['a']=11;
    bar['b']=22;
    bar['c']=33;
    std::cout << "foo contains:\n";
    print_tree(foo);

    std::cout << "bar contains:\n";
    print_tree(bar);

    NS::swap(foo,bar);

    std::cout << "\nAfter swap\nfoo contains:\n";
    print_tree(foo);

    std::cout << "bar contains:\n";
    print_tree(bar);
}

static void test_big_tree() {
    std::cout << MAGENTA << "\n***** BIG TREE TESTS ****" << RESET << std::endl;
    NS::map<int, float> mymap;
    std::cout << "Create tree: for i from 0 till 10000: <i, sqrt(i)>\n";
    for (int i = 0; i < 10000; i++)
        mymap.insert(NS::make_pair(i, sqrt(i)));
    NS::map<int, float>::iterator first, last;
    first = mymap.find(3567);
    last = mymap.find(9999);
    std::cout << "Erase from 3567 till 9999\n";
    mymap.erase(first, last);
    last = mymap.find(3500);
    std::cout << "Erase from begin till 3500\n";
    mymap.erase(mymap.begin(), last);
    std::cout << "mymap contains:\n";
    print_tree(mymap);
}

void test_map() {
    std::cout << std::endl;
    std::cout << RED_COL << "-------------------------------------" << std::endl;
    std::cout << RED_COL << "---------------- MAP ----------------" << std::endl;
    std::cout << RED_COL << "-------------------------------------" << std::endl;
    test_insert();
    test_erase();
    test_swap();
    test_clear();
    test_capacity();
    test_elem_access();
    test_iterators();
    test_observers();
    test_find();
    test_count();
    test_lower_bound();
    test_equal_range();
    test_allocator();
    test_relational_operators();
    test_swap_non_mem();
    test_big_tree();
}
