
#include "tree.hpp"

// set::insert (C++98)
#include <iostream>
#include <set>

int main ()
{
    std::set<int> myset;
    std::set<int>::iterator it;
    std::pair<std::set<int>::iterator,bool> ret;

//    // set some initial values:
//    for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50
//
//    ret = myset.insert(20);               // no new element inserted
//
//    if (ret.second==false) it=ret.first;  // "it" now points to element 20

//    myset.insert (it,25);                 // max efficiency inserting
//    myset.insert (it,24);                 // max efficiency inserting
//    myset.insert (it,26);                 // no max efficiency inserting

    myset.insert(10);
    myset.insert(1);
    myset.insert(15);
    myset.insert(7);
    myset.insert(35);
    myset.insert(110);
    myset.insert(0);

//    int myints[]= {5,10,15};              // 10 already in set, not inserted
//    myset.insert (myints,myints+3);

    std::cout << "myset contains:";
    for (it=myset.begin(); it!=myset.end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';


    ft::Tree<int> mytree;

    mytree.insert(10);
    mytree.insert(1);
    mytree.insert(15);
    mytree.insert(7);
    mytree.insert(35);
    mytree.insert(110);
    mytree.insert(0);

    mytree.inOrderPrint();
    std::cout << std::endl;


    mytree.deleteNode(7);
    mytree.inOrderPrint();
    std::cout << std::endl;
//    mytree.deleteNode(12);
//    mytree.inOrderPrint();
//    std::cout << std::endl;
    mytree.deleteNode(35);
    mytree.inOrderPrint();
    std::cout << std::endl;
    mytree.deleteNode(0);
    mytree.inOrderPrint();
    std::cout << std::endl;
    mytree.deleteNode(15);
    mytree.inOrderPrint();
    std::cout << std::endl;
    return 0;
}