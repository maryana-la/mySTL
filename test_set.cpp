#include "set.hpp"
#include <ctime>
#include <sys/time.h>
#include <set>
#include "color.hpp"
#include <cmath>

#ifndef NS
# define NS ft
#endif

template <typename Key>
void print_tree(NS::set<Key> &tree) {
    typename NS::set<Key>::iterator it = tree.begin();
    typename NS::set<Key>::iterator ite = tree.end();

    int flag = 1;
    for (;it != ite; it++, flag++) {
        std::cout << *it << " ";
        if (!(flag % 30))
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

long int	get_time(void)
{
    long int		current;
    struct timeval	now;

    gettimeofday(&now, NULL);
    current = (now.tv_sec * 1000000) + now.tv_usec;
    return (current);
}

void speed_calculating(long int start) {
    std::cout << RED_COL << "\n***** SPEED TEST ****" << RESET << std::endl;
    printf("Time in microseconds %lu\n", get_time() - start);
}

void test_insert () {
    {
        std::cout << RED_COL << "***** INSERT TESTS ****" << RESET << std::endl;
        std::cout << "---- insert single element ----" << std::endl;
        NS::set<int> mytree;
        mytree.insert(10);
        mytree.insert(110);
        mytree.insert(15);
        mytree.insert(7);
        mytree.insert(35);
        mytree.insert(2);
        mytree.insert(0);
        mytree.insert(110);
        mytree.insert(110);
        mytree.insert(110);
        mytree.insert(110);
        std::cout << "trying to insert keys: 10, 110, 15, 7, 35, 2, 0, 110, 110, 110, 110" << std::endl;

        print_tree(mytree);
//    mytree.inOrderPrint();
        std::cout << std::endl;

        std::cout << "---- insert with hint ----" << std::endl;
        NS::set<int, int>::iterator it = mytree.begin();
        it++;
        std::cout << "trying to insert key -1 at position begin()++" << std::endl;
        mytree.insert(it, -1);
        print_tree(mytree);
//    mytree.inOrderPrint();
        std::cout << std::endl;

        std::cout << "---- insert range ----" << std::endl;
        NS::set<int> set1;
        NS::set<int>::iterator ite = mytree.end();
        it = mytree.begin();
        it++;
        ite--;
        std::cout << "trying to insert keys from begin()++ till end()--" << std::endl;
        set1.insert(it, ite);
        print_tree(set1);
//    set1.inOrderPrint();
        std::cout << std::endl;

        std::cout << "---- insert check return value ----" << std::endl;
        NS::set<char> tree1;
        NS::pair<NS::set<char>::iterator, bool> ret1;
        for (int i = 'a'; i <= 'k'; i++) {
            ret1 = tree1.insert((char)i);
            if (!ret1.second)
                std::cout << i << " already exists" << std::endl;
        }
        print_tree(tree1);
        for (int i = 'a'; i <= 'z'; i++) {
            ret1 = tree1.insert((char)i);
            if (!ret1.second)
                std::cout << (char)i << " already exists" << std::endl;
        }
    }
}

void test_erase() {
    std::cout << RED_COL << "\n***** ERASE TESTS ****" << RESET << std::endl;
    NS::set<int> myt;
    NS::pair<NS::set<int>::iterator, bool> ret1;
    for (int i = 0; i < 30 ; i++) {
        ret1 = myt.insert(i * 10);
        if (!ret1.second)
            std::cout << i << " already exists" << std::endl;
    }
    std::cout << "My set contains:\n";
    print_tree(myt);

    std::cout << "---- erase position ----" << std::endl;
    NS::set<int>::iterator it;
    it = myt.find(20);
    myt.erase(it);
    std::cout << "Find node with key 20, delete it via iterator\n";
    print_tree(myt);
    std::cout << std::endl;

    std::cout << "---- erase single element ----" << std::endl;
    size_t ret;
    ret = myt.erase(30);
    std::cout << "Delete node with key 30, check return value\n";
    std::cout << "Return value: " << ret << std::endl;
    print_tree(myt);

    ret = myt.erase(15);
    std::cout << "Delete node with key 15, check return value\n";
    std::cout << "Return value: " << ret << std::endl;
    print_tree(myt);
    std::cout << std::endl;

    std::cout << "---- erase range ----" << std::endl;
    myt.erase(myt.find(170), myt.find(280));
    std::cout << "Delete range from 170 till 280\n";
    print_tree(myt);
}

void test_swap() {
    std::cout << RED_COL << "\n***** SWAP TESTS ****" << RESET << std::endl;
    NS::set<char> set1, set2;

    for (int i = 'a'; i <= 'o' ; i++)
        set1.insert((char)i);

    for (int i = 'Z'; i >= 'O' ; i--)
        set2.insert((char)i);

    std::cout << "set1 contains: ";
    std::cout << "size " << set1.size() << ": ";
    print_tree(set1);
    std::cout << "set2 contains: ";
    std::cout << "size " << set2.size() << ": ";
    print_tree(set2);

    set1.swap(set2);

    std::cout << "After SWAP\nset1 contains: ";
    std::cout << "size " << set1.size() << ": ";
    print_tree(set1);
    std::cout << "set2 contains: ";
    std::cout << "size " << set2.size() << ": ";
    print_tree(set2);
}

void test_clear() {
    std::cout << RED_COL << "\n***** CLEAR TESTS ****" << RESET << std::endl;

    NS::set<char> myset;

    for (int i = 'a'; i < 'z' ; i++)
        myset.insert((char)i);
    std::cout << "my_set contains: size " << myset.size() << ": ";
    print_tree(myset);

    myset.clear();
    std::cout << "After clear: Is empty? " << myset.empty() << std::endl;
    for (int i = 'A'; i < 'F' ; i++)
        myset.insert((char)i);
    std::cout << "my_set contains: size " << myset.size() << ": ";
    print_tree(myset);
}

void test_capacity() {
    std::cout << RED_COL << "\n***** CAPACITY TESTS ****" << RESET << std::endl;
    NS::set<float> myset;

    for (int i = 7; i <= 50; i += 2)
        myset.insert(float(i * log(i)));
    std::cout << "my_set contains: ";
    print_tree(myset);
    std::cout << "is empty: " << myset.empty() << std::endl;
    std::cout << "size: " << myset.size() << std::endl;
    std::cout << "max_size: " << myset.max_size() << std::endl;

    myset.insert(45.7);
    std::cout << "AFTER ADDING 45.7\nmy_set contains: ";
    print_tree(myset);
    std::cout << "is empty: " << myset.empty() << std::endl;
    std::cout << "size: " << myset.size() << std::endl;
    std::cout << "max_size: " << myset.max_size() << std::endl;

    myset.clear();
    std::cout << "AFTER clear()\nmy_set contains: ";
    print_tree(myset);
    std::cout << "is empty: " << myset.empty() << std::endl;
    std::cout << "size: " << myset.size() << std::endl;
    std::cout << "max_size: " << myset.max_size() << std::endl;
}

void test_iterators() {
    std::cout << RED_COL << "\n***** ITERATOR TESTS ****" << RESET << std::endl;
    NS::set<char> myset;
    for (int i = 7; i <= 20; i++)
        myset.insert((char)(i+ 90));

    std::cout << "my_set print via direct iterators: ";
    print_tree(myset);

    NS::set<char>::reverse_iterator rit = myset.rbegin();
    NS::set<char>::reverse_iterator rite = myset.rend();

    std::cout << "my_set print via reverse iterators: ";
    int flag = 1;
    for (; rit != rite; rit++, flag++){
        std::cout << *rit << " ";
        if (!(flag % 30))
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

void test_observers() {
    std::cout << RED_COL << "\n***** OBSERVERS TESTS ****" << RESET << std::endl;
    {
        NS::set<int> myset;
        for (int i = 10; i <= 10000; i *= 2)
            myset.insert(i);

        NS::set<int>::key_compare mycomp = myset.key_comp();

        std::cout << "myset contains:\n";
        print_tree(myset);

        int highest = 500;
        std::cout << "Print values less than 500 (key_compare):\n";
        NS::set<int>::iterator it = myset.begin();
        for (; mycomp((*it), highest); it++) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    {
        NS::set<int> myset;
        for (int i = 10; i <= 10000; i *= 2)
            myset.insert(i);

        NS::set<int>::value_compare mycomp = myset.value_comp();
       int highest = 2000;

        std::cout << "Print values less than 2000 (value_compare):\n";
        NS::set<int>::iterator it = myset.begin();
        for (; mycomp((*it), highest); it++) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}

void test_find() {
    std::cout << RED_COL << "\n***** FIND TESTS ****" << RESET << std::endl;
    NS::set<char> myset;
    for (int i = 1; i <= 26; i++)
        myset.insert((char)(i + 96));
    std::cout << "myset contains:\n";
    print_tree(myset);

    NS::set<char>::iterator it;
    it = myset.find('n');
    std::cout << "Find key n: " << *it << std::endl;
    myset.erase(myset.begin(), it);
    std::cout << "Erase from begin() till find('n'). Now myset contains:\n";
    print_tree(myset);
}

void test_count() {
    std::cout << RED_COL << "\n***** COUNT TESTS ****" << RESET << std::endl;
    NS::set<char> myset;
    for (int i = 'a'; i <= 'k'; i++)
        myset.insert((char)i);
    std::cout << "myset contains:\n";
    print_tree(myset);
    std::cout << std::endl;
    char c;

    for (c = 'a'; c <= 'z'; c++)
    {
        std::cout << c;
        if (myset.count(c) > 0)
            std::cout << " is an element of myset.\n";
        else
            std::cout << " is not an element of myset.\n";
    }
}

void test_lower_bound() {
    std::cout << RED_COL << "\n***** LOWER/UPPER_BOUND TESTS ****" << RESET << std::endl;
    NS::set<char> myset;
    for (int i = 'a'; i <= 'z'; i++)
        myset.insert((char)i);
    std::cout << "myset contains:\n";
    print_tree(myset);

    NS::set<char>::iterator itlow,itup;

    itlow = myset.lower_bound ('g');
    std::cout << "lower_bound: " << *itlow << '\n';
    itup = myset.upper_bound ('t');
    std::cout << "upper_bound: " << *itup<< '\n';

    myset.erase(itlow,itup);
    std::cout << "Erase from lower_bound till upper_bound:\n";
    print_tree(myset);
}

void test_equal_range() {
    std::cout << RED_COL << "\n***** EQUAL_RANGE TESTS ****" << RESET << std::endl;

    NS::set<int> myset;
    for (int i = 10; i <= 10000; i *= 2)
        myset.insert(i);
    std::cout << "myset contains:\n";
    print_tree(myset);

    NS::pair<NS::set<int>::const_iterator,NS::set<int>::const_iterator> ret;
    ret = myset.equal_range(40);

    std::cout << "the lower bound points to: " << *ret.first << '\n';
    std::cout << "the upper bound points to: " << *ret.second << '\n';
}

void test_allocator() {
    std::cout << RED_COL << "\n***** ALLOCATOR TESTS ****" << RESET << std::endl;
    NS::set<int> myset;
    int *p;
    unsigned int i;

    std::cout << "Allocate an array of 5 elements using myset's allocator:\n";
    p=myset.get_allocator().allocate(5);

    // assign some values to array
    for (i=0; i<5; i++) p[i]=(i+1)*10;

    std::cout << "The allocated array contains:";
    for (i=0; i<5; i++) std::cout << ' ' << p[i];
    std::cout << '\n';
    myset.get_allocator().deallocate(p,5);
}

void test_relational_operators() {
    std::cout << RED_COL << "\n***** RELATIONAL_OPERATORS TESTS ****" << RESET << std::endl;

    NS::set<int> foo,bar;
    foo.insert(10);
    bar.insert(20);
    bar.insert(30);
    foo.insert(40);
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
    foo.insert(20);
    foo.insert(400);
    bar.insert(20);
    bar.insert(30);
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

void test_swap_non_mem() {
    std::cout << RED_COL << "\n***** SWAP_NON-MEMBER TESTS ****" << RESET << std::endl;

    NS::set<std::string> foo,bar;

    foo.insert("hello");
    foo.insert("world");

    bar.insert("C++");
    bar.insert("Ruby-on-rails");
    bar.insert("Python");
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

void test_big_tree() {
    std::cout << RED_COL << "\n***** BIG TREE TESTS ****" << RESET << std::endl;
    NS::set<int> myset;
    std::cout << "Create tree: for i from 0 till 1 000 000: <sqrt(i)>\n";
    for (int i = 0; i < 1000000; i++)
        myset.insert(i);
    NS::set<int>::iterator first, last;
    first = myset.find(3567);
    last = myset.find(9999);
    std::cout << "Erase from 3567 till 99999\n";
    myset.erase(first, last);
    last = myset.find(3500);
    std::cout << "Erase from begin till 3500\n";
    myset.erase(myset.begin(), last);
    std::cout << "myset contains:\n";
//    print_tree(myset);
}

int main () {
//    clock_t t;
//    t = clock();
    long int start = get_time();
    test_insert();
    test_erase();
    test_swap();
    test_clear();
    test_capacity();
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
//    t = clock() - t;
//    printf ("It took me %lu clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

    speed_calculating(start);
    return 0;

}
