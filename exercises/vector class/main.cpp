#include "Ptr.h"
#include <iostream>
#include <utility>

int main()
{
    Ptr p1{10.5};
    std::cout << *p1 << '\n';

    *p1 = 20.5;
    std::cout << *p1 << '\n';

    Ptr p2{p1};
    std::cout << *p2 << '\n';

    *p2 = 30.5;

    std::cout << *p1 << '\n';
    std::cout << *p2 << '\n';

    Ptr p3{40.5};
    p3 = p1;

    std::cout << *p3 << '\n';

    Ptr p4{std::move(p1)};

    std::cout << *p4 << '\n';

    Ptr p5{50.5};
    p5 = std::move(p2);

    std::cout << *p5 << '\n';
}