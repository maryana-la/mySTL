#include <iostream>
#include <sys/time.h>
#include "includes/color.hpp"

#ifdef FT
# define NS ft
#else
# define NS std
#endif

void test_map();
void test_vector();
void test_stack();
void test_set();

long int get_time(void) {
    long int current;
    struct timeval now;

    gettimeofday(&now, NULL);
    current = (now.tv_sec * 1000000) + now.tv_usec;
    return (current);
}

void speed_calculating(long int start) {
    std::cout << MAGENTA << "\n***** SPEED TEST ****" << RESET << std::endl;
    std::cout << "Time in microseconds " << (get_time() - start) << std::endl;
}

int main() {
    std::cout << BOLDRED << "***********************" << std::endl;
#ifdef FT
    std::cout << "    Namespace : ft" << std::endl;
#else
    std::cout << "    Namespace : std" << std::endl;
#endif
    std::cout << "***********************" << RESET << std::endl;
    long int start = get_time();
    test_vector();
    test_stack();
    test_map();
    test_set();
    speed_calculating(start);
    return 0;
}
