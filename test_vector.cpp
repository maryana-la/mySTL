#include "vector.hpp"
#include <vector>
//#include <ctime>
#include <sys/time.h>
#include "color.hpp"
#include <cmath>

#ifndef NS
# define NS std
#endif

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

template <typename T>
void print_vector(NS::vector<T> &cont) {
    typename NS::vector<T>::iterator it, ite;
    it = cont.begin();
    ite = cont.end();

    for (; it != ite; it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void test_assign() {
    std::cout << RED_COL << "\n***** ASSIGN TEST ****" << RESET << std::endl;
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

void test_push_pop_back() {
    std::cout << RED_COL << "\n***** PUSH_BACK - POP_BACK TEST ****" << RESET << std::endl;
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

void test_insert() {
    std::cout << RED_COL << "\n***** INSERT TEST ****" << RESET << std::endl;
    NS::vector<int> myvector (1,100);
    myvector.push_back(101);
    myvector.push_back(102);
    NS::vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert ( it , 200 );
    print_vector(myvector);

//    it--; - should not segfault
    myvector.insert (it,2,300);
    print_vector(myvector);
    it = myvector.begin();

    NS::vector<int> anothervector (2,400);
    myvector.insert (it+2,anothervector.begin(),anothervector.end());
    print_vector(myvector);

    std::cout << '\n';
/*
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
    print_vector(vec3); */
}


int main() {
    long int start = get_time();

    test_assign();
    test_push_pop_back();
    test_insert();

    speed_calculating(start);
}

/*
(constructor)
(destructor)
operator=


Modifiers:
assign
push_back
pop_back
insert
erase
swap
clear

Iterators:
begin
end
rbegin
rend

Element access:
operator[]
at
front
back

Capacity:
size
max_size
resize
capacity
empty
reserve

Allocator:
get_allocator

Non-member function overloads
relational operators
swap
 */