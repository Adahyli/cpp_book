#include <iostream>
#include <cmath>

int main() // simple program to exercise operators
{
 std::cout << "Please enter a value: ";
 int n = 0;
 std::cin >> n;

 bool even = n % 2 == 0;

 std::cout << std::boolalpha;
 std::cout << "n == " << n
 << "\nn+1 == " << n+1
 << "\nthree times n == " << 3*n
 << "\ntwice n == " << n+n
 << "\nn squared == " << n*n
 << "\nhalf of n == " << n/2
 << "\nsquare root of n == " << sqrt(n)
 << "\nis n even == " << even
 << '\n';
 return 0;
}
