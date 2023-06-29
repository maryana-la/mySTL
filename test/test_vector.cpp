#include <iostream>
#include "../includes/color.hpp"

#ifdef FT
# define NS ft
# include "../includes/vector.hpp"
#else
# include <vector>
# define NS std
#endif

template <typename T>
static void print_vector(NS::vector<T> &cont) {
    typename NS::vector<T>::iterator it, ite;
    it = cont.begin();
    ite = cont.end();

    for (; it != ite; it++)
        std::cout << CYAN << *it << " ";
    std::cout << RESET << std::endl;
}

static void test_assign() {
    std::cout << MAGENTA << "\n***** ASSIGN TEST ****" << RESET << std::endl;
    NS::vector<int> first;
    NS::vector<int> second;
    NS::vector<int> third;

    first.assign (7,100);
    std::cout << "Assign 7 ints with a value of 100\n";
    std::cout << "Size: " << int (first.size()) << " | ";
    print_vector(first);

    NS::vector<int>::iterator it;
    it = first.begin() + 1;

    second.assign (it,first.end() - 1);
    std::cout << "Assign the 5 central values of first\n";
    std::cout << "Size: " << int (second.size()) << " | ";
    print_vector(second);
}

static void test_push_pop_back() {
    std::cout << MAGENTA << "\n***** PUSH_BACK - POP_BACK TEST ****" << RESET << std::endl;
    NS::vector<int> vec;
    vec.push_back(34);
    print_vector(vec);
    vec.push_back(454);
    print_vector(vec);
    vec.push_back(232);
    print_vector(vec);
    vec.push_back(67);
    print_vector(vec);
    vec.push_back(90);
    print_vector(vec);
    vec.pop_back();
    print_vector(vec);
    vec.pop_back();
    print_vector(vec);
    vec.pop_back();
    print_vector(vec);
    vec.pop_back();
    print_vector(vec);
    vec.pop_back();
    print_vector(vec);
}

static void test_insert() {
    std::cout << MAGENTA << "\n***** INSERT TEST ****" << RESET << std::endl;
    NS::vector<int> myvector (1,100);
    myvector.push_back(101);
    myvector.push_back(102);
    print_vector(myvector);

    NS::vector<int>::iterator it;
    it = myvector.begin();
    std::cout << "Insert 200 in the beginning: ";
    it = myvector.insert ( it , 200 );
    print_vector(myvector);

//    it--; - should not segfault
    std::cout << "Insert 2 ints of value 300: ";
    myvector.insert (it,2,300);
    print_vector(myvector);

    it = myvector.begin();
    std::cout << "Insert a range {400, 400} to position begin() += 2: ";
    NS::vector<int> anothervector (2,400);
    myvector.insert (it + 2, anothervector.begin(),anothervector.end());
    print_vector(myvector);

    std::cout << '\n';

    NS::vector<int> vec1;
    std::cout << "Insert i*10, i++ in reverse order: ";
    for (int i = 0; i < 15; i++)
        vec1.insert(vec1.begin(), i * 10);
    print_vector(vec1);

    NS::vector<int> vec2;
    std::cout << "Insert 15 ints of value 10: ";
    vec2.insert(vec2.begin(), 15, 10);
    print_vector(vec2);

    NS::vector<int> vec3;
    std::cout << "Insert from begin till end previous vector: ";
    vec3.insert(vec3.begin(), vec2.begin(), vec2.end());
    print_vector(vec3);
}

static void test_erase() {
    std::cout << MAGENTA << "\n***** ERASE TEST ****" << RESET << std::endl;
    NS::vector<char> myvector;


    NS::vector<char>::iterator it;

    for (int i = 'a'; i <= 'z'; i++)
        myvector.push_back((char)i);
    std::cout << "myvector contains: ";
    print_vector(myvector);

    myvector.erase (myvector.begin()+5);
    std::cout << "erase the 6th element: ";
    print_vector(myvector);

    it = myvector.begin();
//    it--; // might segfault, STL as well

    myvector.erase (it,myvector.begin() + 10);
    std::cout << "erase the first 10 elements: ";
    print_vector(myvector);
}

static void test_swap(){
    std::cout << MAGENTA << "\n***** SWAP TEST ****" << RESET << std::endl;
    NS::vector<int> foo (3,100);   // three ints with a value of 100
    NS::vector<int> bar (5,200);   // five ints with a value of 200
    std::cout << "foo: size " << foo.size() << " contains: ";
    print_vector(foo);
    std::cout << "bar: size "  << bar.size() << " contains: ";
    print_vector(bar);

    foo.swap(bar);

    std::cout << "AFTER SWAP:\nfoo: size " << foo.size() << " contains: ";
    print_vector(foo);
    std::cout << "bar: size "  << bar.size() << " contains: ";
    print_vector(bar);
}

static void test_clear() {
    std::cout << MAGENTA << "\n***** CLEAR TEST ****" << RESET << std::endl;

    NS::vector<char> myvector(10, 'a');

    std::cout << "myvector contains: ";
    print_vector(myvector);

    myvector.clear();
    std::cout << "AFTER CLEAR:\nmyvector contains: size " << myvector.size();
    std::cout << "\nIs empty? " << myvector.empty();
    print_vector(myvector);
}

static void test_iterators() {
    std::cout << MAGENTA << "\n***** ITERATORS TEST ****" << RESET << std::endl;

    NS::vector<char> myvector;
    NS::vector<char>::reverse_iterator it, ite;


    for (int i = 'a'; i <= 'z'; i++)
        myvector.push_back((char)i);
    std::cout << "print vector via iterator: ";
    print_vector(myvector);


    NS::vector<char>::iterator it2, ite2;
    it2 = myvector.begin();
    NS::vector<char>::const_iterator it1 = it2;
    (void)it1;

    it = myvector.rbegin();
    ite = myvector.rend();

    std::cout << "print vector via reverse_iterator: ";
    for (; it != ite; it++)
        std::cout << CYAN << *it << " ";
    std::cout << RESET << std::endl;
}

static void test_elem_access() {
    std::cout << MAGENTA << "\n***** ELEMENT ACCESS TEST ****" << RESET << std::endl;

    NS::vector<char> myvector;
    NS::vector<char>::reverse_iterator it, ite;
    for (int i = 'a'; i <= 'z'; i++)
        myvector.push_back((char)i);
    std::cout << "myvector contains: ";
    print_vector(myvector);

    std::cout << "***** operator[] *****" << std::endl;
    std::cout << "myvector[10] - " << myvector[10] << std::endl;
    std::cout << "myvector[1]  - " << myvector[1] << std::endl;
//    std::cout << "myvector[100]  - " << myvector[100] << std::endl; // UB
    std::cout << std::endl;
    std::cout << "***** operator at *****" << std::endl;
    try {
        std::cout << "myvector.at(10) - " << myvector.at(10) << std::endl;
        std::cout << "myvector.at(1)  - " << myvector.at(1) << std::endl;
        std::cout << "myvector.at(100)  - " << myvector.at(100) << std::endl; //should throw exception
    }
    catch (std::exception &e) {
        std::cout << "catched exception - ";
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "***** operator front *****" << std::endl;
    std::cout << "myvector.front() - " << myvector.front() << std::endl;
    std::cout << std::endl;
    std::cout << "***** operator back *****" << std::endl;
    std::cout << "myvector.back() - " << myvector.back() << std::endl;
}

static void test_capacity() {
    std::cout << MAGENTA << "\n***** CAPACITY TEST ****" << RESET << std::endl;
    NS::vector<int> myvector;
    NS::vector<int>::reverse_iterator it, ite;
    for (int i = 0; i < 100; i++)
        myvector.push_back(i * i);
    std::cout << "myvector contains: ";
    print_vector(myvector);

    std::cout << "size: " << myvector.size() << std::endl;
    std::cout << "max_size: " << myvector.max_size() << std::endl;
    std::cout << "capacity: " << myvector.capacity() << std::endl;
    std::cout << "empty: " << myvector.empty() << std::endl;
    std::cout << std::endl;

    std::cout << "***** resize *****" << std::endl;
    myvector.resize(10);
    std::cout << "resize(10):\nnew size() " << myvector.size() << std::endl << "now myvector contains: ";
    print_vector(myvector);
    myvector.resize(20);
    std::cout << "resize(20):\nnew size() " << myvector.size() << std::endl << "now myvector contains: ";
    print_vector(myvector);
    std::cout << std::endl;

    std::cout << "***** reserve *****" << std::endl;
    myvector.reserve(10);
    std::cout << "reserve(10)\nsize: " << myvector.size() << std::endl;
    std::cout << "capacity: " << myvector.capacity() << std::endl;
    print_vector(myvector);

    myvector.reserve(1000);
    std::cout << "reserve(1000)\nsize: " << myvector.size() << std::endl;
    std::cout << "capacity: " << myvector.capacity() << std::endl;
    print_vector(myvector);
}

static void test_allocator(){
    std::cout << MAGENTA << "\n***** ALLOCATOR TEST ****" << RESET << std::endl;
    NS::vector<int> myvector;
    NS::vector<int>::reverse_iterator it, ite;
    for (int i = 0; i < 10; i++)
        myvector.push_back(i * i);
    std::cout << "myvector contains: ";
    print_vector(myvector);

    int * p;
    unsigned int i;

    std::cout << "allocate an array for 5 elements using vector's allocator" << std::endl;
    p = myvector.get_allocator().allocate(5);

    // construct values in-place on the array:
    for (i = 0; i < 5; i++)
        myvector.get_allocator().construct(&p[i],i);

    std::cout << "The allocated array contains:";
    for (i = 0; i < 5; i++)
        std::cout << ' ' << p[i];
    std::cout << std::endl;

    // destroy and deallocate:
    for (i = 0; i < 5; i++) myvector.get_allocator().destroy(&p[i]);
    myvector.get_allocator().deallocate(p,5);
}

static void test_relational() {
    std::cout << MAGENTA << "\n***** RELATIONAL OPERATORS TEST ****" << RESET << std::endl;
    NS::vector<int> foo(3, 100);   // three ints with a value of 100
    NS::vector<int> bar(2, 200);   // two ints with a value of 200
    std::cout << "foo contains: ";
    print_vector(foo);
    std::cout << "bar contains: ";
    print_vector(bar);

    if (foo == bar) std::cout << "foo and bar are equal\n";
    if (foo != bar) std::cout << "foo and bar are not equal\n";
    if (foo < bar) std::cout << "foo is less than bar\n";
    if (foo > bar) std::cout << "foo is greater than bar\n";
    if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
    if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
    std::cout << std::endl;

    bar.clear();
    bar.assign(2,100);
    bar.push_back(90);
    std::cout << "foo contains: ";
    print_vector(foo);
    std::cout << "bar contains: ";
    print_vector(bar);

    if (foo == bar) std::cout << "foo and bar are equal\n";
    if (foo != bar) std::cout << "foo and bar are not equal\n";
    if (foo < bar) std::cout << "foo is less than bar\n";
    if (foo > bar) std::cout << "foo is greater than bar\n";
    if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
    if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
}

static void test_swap_non_member() {
    std::cout << MAGENTA << "\n***** SWAP (non-member) TEST ****" << RESET << std::endl;
    NS::vector<int> foo (3,100);   // three ints with a value of 100
    NS::vector<int> bar (5,200);   // five ints with a value of 200
    std::cout << "foo contains: ";
    print_vector(foo);
    std::cout << "bar contains: ";
    print_vector(bar);

    swap(foo, bar);

    std::cout << "foo contains: ";
    print_vector(foo);
    std::cout << "bar contains: ";
    print_vector(bar);
}

static void test_big_vector() {
    std::cout << MAGENTA << "\n***** BIG VECTOR TEST ****" << RESET << std::endl;
    NS::vector<int> myvector;
    for (int i = 0; i < 100000; i++)
        myvector.push_back(i);
    std::cout << "myvector contains: ";
//    print_vector(myvector);
    myvector.resize(1000);
    print_vector(myvector);
    myvector.erase(myvector.begin(), myvector.end());
    print_vector(myvector);
}

void test_vector() {
    std::cout << std::endl;
    std::cout << RED_COL << "-------------------------------------" << std::endl;
    std::cout << RED_COL << "--------------- VECTOR --------------" << std::endl;
    std::cout << RED_COL << "-------------------------------------" << std::endl;
    test_assign();
    test_push_pop_back();
    test_insert();
    test_erase();
    test_swap();
    test_clear();
    test_iterators();
    test_elem_access();
    test_capacity();
    test_allocator();
    test_relational();
    test_swap_non_member();
    test_big_vector();
}
