#include <iostream>
#include <string>

int main()
{
    int number_of_words = 0;
    std::string previous; // previous word; initialized to ""
    std::string current; // current word
    while (std::cin>>current) { // read a stream of words
        number_of_words++;
        if (previous == current){ // check if the word is the same as last
        std::cout << "repeated word: " << current << '\n';
        }
        previous = current;
           
    }
 return 0;
}
