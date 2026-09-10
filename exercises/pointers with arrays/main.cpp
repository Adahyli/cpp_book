
#include <iostream>
#include <vector>

void print_array(std::ostream& os, int* a, int n)
{
    for (int i = 0; i < n; ++i)
        os << a[i] << ' ';
    os << '\n';
}

void print_vector(std::ostream& os, const std::vector<int>& v)
{
    for (int x : v)
        os << x << ' ';
    os << '\n';
}

int main()
{

    int* p1 = new int{7};

    
    std::cout << "p1: " << static_cast<void*>(p1) << '\n';
    std::cout << "*p1: " << *p1 << '\n';


    int* p2 = new int[7];

    for (int i = 0; i < 7; ++i)
        p2[i] = 1 << i;

    std::cout << "p2: " << static_cast<void*>(p2) << '\n';
    print_array(std::cout, p2, 7);


    int* p3 = p2;


    p2 = p1;


    p2 = p3;


    std::cout << "p1: " << static_cast<void*>(p1) << '\n';
    std::cout << "*p1: " << *p1 << '\n';

    std::cout << "p2: " << static_cast<void*>(p2) << '\n';
    print_array(std::cout, p2, 7);


    delete p1;
    delete[] p2;


    p1 = new int[10];

    for (int i = 0; i < 10; ++i)
        p1[i] = 1 << i;


    p2 = new int[10];


    for (int i = 0; i < 10; ++i)
        p2[i] = p1[i];

    std::cout << "p1 array: ";
    print_array(std::cout, p1, 10);

    std::cout << "p2 array: ";
    print_array(std::cout, p2, 10);


    std::vector<int> v1(10);
    std::vector<int> v2(10);

    for (int i = 0; i < 10; ++i)
        v1[i] = 1 << i;

    for (int i = 0; i < 10; ++i)
        v2[i] = v1[i];

    std::cout << "v1: ";
    print_vector(std::cout, v1);

    std::cout << "v2: ";
    print_vector(std::cout, v2);


    delete[] p1;
    delete[] p2;
}