// inserting into a vector
#include <iostream>
#include <vector>
//#include "../../Downloads/davidarbib_ft_containers/includes/vector.hpp"
#include "/Users/rchelsea/Desktop/ft_cont/42pde-bakk/srcs/vector/Vector.hpp"
//#include "vector.hpp"

int main ()
{
    ft::vector<int> myvector (3,100);
    ft::vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert ( it , 200 );
    for (it=myvector.begin(); it<myvector.end(); it++)
        std::cout << ' ' << *it;
    std::cout << '\n';
    it = myvector.end();
    it++;
    it++;
    it++;
    it++;
    it++;
    it++;
    myvector.insert (it,2,300);

    for (it=myvector.begin(); it<myvector.end(); it++)
        std::cout << ' ' << *it;
    std::cout << '\n';
    // "it" no longer valid, get a new one:
    it = myvector.begin();

    ft::vector<int> anothervector (2,400);
    myvector.insert (it+2,anothervector.begin(),anothervector.end());

    int myarray [] = { 501,502,503 };
    myvector.insert (myvector.begin(), myarray, myarray+3);

    std::cout << "myvector contains:";
    for (it=myvector.begin(); it<myvector.end(); it++)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}