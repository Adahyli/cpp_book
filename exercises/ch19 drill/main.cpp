
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

template<std::input_iterator Iter1,
         std::output_iterator<std::iter_value_t<Iter1>> Iter2>
Iter2 copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
    while (f1 != e1) {
        *f2 = *f1;
        ++f1;
        ++f2;
    }

    return f2;
}

int main()
{
    
    int a[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};


    std::vector<int> v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};


    std::list<int> l {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};


    int a2[10];
    std::vector<int> v2(v);
    std::list<int> l2(l);

    copy(a, a + 10, a2);


    for (int& x : a)
        x += 2;

    for (int& x : v)
        x += 3;

    for (int& x : l)
        x += 5;


    
    copy(a, a + 10, v.begin());

 
    copy(l.begin(), l.end(), a2);


   
    auto pv = std::find(v.begin(), v.end(), 3);

    if (pv != v.end())
        std::cout << "3 is at position " << pv - v.begin() << " in vector\n";
    else
        std::cout << "3 not found in vector\n";


    
    auto pl = std::find(l.begin(), l.end(), 27);

    if (pl != l.end()) {
        int position = std::distance(l.begin(), pl);
        std::cout << "27 is at position " << position << " in list\n";
    }
    else {
        std::cout << "27 not found in list\n";
    }
}