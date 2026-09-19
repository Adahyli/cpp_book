
#include "vector.h"

#include <iostream>
#include <utility>

int main()
{
    Vector<int> v{1, 2, 3};

    std::cout << "size: " << v.size() << '\n';
    std::cout << "capacity: " << v.capacity() << '\n';

    for (int x : v)
        std::cout << x << ' ';

    std::cout << '\n';
}