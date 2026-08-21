#include <iostream>
#include <string>

int main()
{
 std::cout << "Please enter your first and second names\n";
 std::string first;
 std::string second;
 int age;
 std::cin >> first >> second; // read two strings
 std::cout << "Hello, " << first << " " << second << " \nHow old are you? " << '\n';
 std::cin >> age; 
 std::cout << "you are " << age * 12 <<" months old\n";
 return 0;
}
