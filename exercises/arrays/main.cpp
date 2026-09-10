
#include <iostream>
#include <vector>

void print_array(std::ostream& os, int* a, int n){
    for (int i = 0; i < n; ++i)
        os << a[i] << ' ';
    os << '\n';
}

void print_vector(std::ostream& os, const std::vector<int>& v){
    for (int x : v)
        os << x << ' ';
    os << '\n';
}

int main(){
    
    int* a = new int[10];
    
    print_array(std::cout, a, 10);

    delete[] a;
  
    a = new int[10];

    for (int i = 0; i < 10; ++i)
        a[i] = 100 + i;

    print_array(std::cout, a, 10);

    int* b = new int[11];

    for (int i = 0; i < 11; ++i)
        b[i] = 100 + i;

    print_array(std::cout, b, 11);

    int* c = new int[20];

    for (int i = 0; i < 20; ++i)
        c[i] = 100 + i;

    print_array(std::cout, c, 20);

    delete[] a;
    delete[] b;
    delete[] c;

    std::vector<int> v1(10);

    for (int i = 0; i < 10; ++i)
        v1[i] = 100 + i;

    print_vector(std::cout, v1);

    std::vector<int> v2(11);

    for (int i = 0; i < 11; ++i)
        v2[i] = 100 + i;

    print_vector(std::cout, v2);

    std::vector<int> v3(20);

    for (int i = 0; i < 20; ++i)
        v3[i] = 100 + i;

    print_vector(std::cout, v3);
}