#include <iostream>
#include "../includes/color.hpp"

#ifdef FT
# define NS ft
# include "../includes/stack.hpp"
#else
# define NS std
# include <stack>
#endif

static void test_empty() {
    std::cout << MAGENTA << "\n***** EMPTY TEST ****" << RESET << std::endl;
    NS::stack<int> mystack;
    int sum (0);

    std::cout << "Create stack 1...10\n";
    for (int i = 1; i <= 10; i++)
        mystack.push(i);
    std::cout << "Is empty? " << mystack.empty() << std::endl;

    while (!mystack.empty()) {
        sum += mystack.top();
        mystack.pop();
    }
    std::cout << "While not empty, sum all content\n";
    std::cout << "sum: " << sum << std::endl;
}

static void test_size() {
    std::cout << MAGENTA << "\n***** SIZE TEST ****" << RESET << std::endl;
    NS::stack<int> mystack;

    std::cout << "Create stack 1...10\n";
    for (int i = 1; i <= 10; i++)
        mystack.push(i);
    std::cout << "Size " << mystack.size() << std::endl;

    mystack.pop();
    mystack.pop();
    std::cout << "pop twice\nSize " << mystack.size() << std::endl;
}

static void test_top() {
    std::cout << MAGENTA << "\n***** TOP TEST ****" << RESET << std::endl;
    NS::stack<int> mystack;

    std::cout << "Create stack 1...20\n";
    for (int i = 0; i < 20; i++)
        mystack.push(i);

    std::cout << "while not empty, print top() then pop()\n";
    while (!mystack.empty()) {
        std::cout << mystack.top() << " ";
        mystack.pop();
    }
    std::cout << std::endl;
}

static void test_push() {
    std::cout << MAGENTA << "\n***** PUSH TEST ****" << RESET << std::endl;
    NS::stack<std::string> mystack;

    std::cout << "Create stack<std::string> Zombie for 1...10\n";
    for (int i = 0; i < 10; i++)
        mystack.push("Zombie");

    while (!mystack.empty()) {
        std::cout << mystack.top() << " ";
        mystack.pop();
    }
    std::cout << std::endl;
}

static void test_pop() {
    std::cout << MAGENTA << "\n***** POP TEST ****" << RESET << std::endl;
    NS::stack<char> mystack;

    std::cout << "Create stack<char> for a...z\n";
    for (int i = 'a'; i <= 'z'; i++)
        mystack.push((char)i);
    std::cout << "Popping out elements:\n";
    while (!mystack.empty()) {
        std::cout << mystack.top() << " ";
        mystack.pop();
    }
    std::cout << std::endl;
}

static void test_big_stack() {
    std::cout << MAGENTA << "\n***** POP TEST ****" << RESET << std::endl;
    NS::stack<int> mystack;

    std::cout << "Create stack<int> for 0...100000\n";
    for (int i = 0; i < 100000; i++)
        mystack.push(i);
    std::cout << "Popping out elements:\n";
    while (!mystack.empty()) {
        std::cout << mystack.top() << " ";
        mystack.pop();
    }
    std::cout << std::endl;
}

void test_stack() {
    std::cout << std::endl;
    std::cout << RED_COL << "-------------------------------------" << std::endl;
    std::cout << RED_COL << "--------------- STACK ---------------" << std::endl;
    std::cout << RED_COL << "-------------------------------------" << std::endl;
    test_empty();
    test_size();
    test_top();
    test_push();
    test_pop();
    test_big_stack();
}
