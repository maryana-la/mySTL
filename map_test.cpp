#include "map.hpp"
#include <map>
#include "color.hpp"

#ifndef NS
# define NS ft
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

void test_insert () {
    {
        std::cout << RED_COL << "***** INSERT TESTS ****" << RESET << std::endl;
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
//    {
//        /* from cplusplus */
//        NS::map<char, int> mymap;
//
//        // first insert function version (single parameter):
//        mymap.insert(NS::pair<char, int>('a', 100));
//        mymap.insert(NS::pair<char, int>('z', 200));
//
//        NS::pair<NS::map<char, int>::iterator, bool> ret;
//        ret = mymap.insert(NS::pair<char, int>('z', 500));
//        if (!ret.second) {
//            std::cout << "element 'z' already existed";
//            std::cout << " with a value of " << ret.first->second << '\n';
//        }
//
//        // second insert function version (with hint position):
//        NS::map<char, int>::iterator it = mymap.begin();
//        mymap.insert(it, NS::pair<char, int>('b', 300));  // max efficiency inserting
//        mymap.insert(it, NS::pair<char, int>('c', 400));  // no max efficiency inserting
//
//        // third insert function version (range insertion):
//        NS::map<char, int> anothermap;
//        anothermap.insert(mymap.begin(), mymap.find('c'));
//
//        // showing contents:
//        std::cout << "mymap contains:\n";
//        for (it = mymap.begin(); it != mymap.end(); ++it)
//            std::cout << it->first << " => " << it->second << '\n';
//
//        std::cout << "anothermap contains:\n";
//        for (it = anothermap.begin(); it != anothermap.end(); ++it)
//            std::cout << it->first << " => " << it->second << '\n';
//    }
}

void test_erase() {
    std::cout << RED_COL << "\n***** ERASE TESTS ****" << RESET << std::endl;
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

/*
    std::cout << std::endl;
    NS::map<int, int> myt1;
    NS::pair<NS::map<int, int>::iterator, bool> ret2;
    for (int i = 0; i < 15 ; i++) {
        ret2 = myt1.insert(NS::make_pair(i, i * i));
        if (!ret2.second)
            std::cout << i << " already exists" << std::endl;
    }
    myt1.inOrderPrint();
    std::cout << std::endl;
    myt1.erase(myt1.find(2), myt1.find(13));
    myt1.inOrderPrint(); */
}

void test_swap() {
    std::cout << RED_COL << "\n***** SWAP TESTS ****" << RESET << std::endl;
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

void test_clear() {
    std::cout << RED_COL << "\n***** CLEAR TESTS ****" << RESET << std::endl;

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

void test_capacity() {
    std::cout << RED_COL << "\n***** CAPACITY TESTS ****" << RESET << std::endl;
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

void test_elem_access() {
    std::cout << RED_COL << "\n***** ELEMENT ACCESS TESTS ****" << RESET << std::endl;
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
}



int main () {
    test_insert();
    test_erase();
    test_swap();
    test_clear();
    test_capacity();
    test_elem_access();

    return 0;

}


/*
Member functions
(constructor)
(destructor)
operator=

Iterators:
begin
end
rbegin
rend

Capacity: - done
empty
size
max_size

Element access: - done
operator[]
at

Modifiers: - done
insert
erase
swap
clear

Observers:
key_comp
value_comp

Operations:
find
count
lower_bound
upper_bound
equal_range

Allocator:
get_allocator
 */