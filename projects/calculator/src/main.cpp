
#include "Calculator.h"

#include <exception>
#include <iostream>

int main()
try {
    Calculator calculator{
        std::cin,
        std::cout,
        std::cerr
    };

    calculator.run();

    return 0;
}
catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
}
catch (...) {
    std::cerr << "Unknown exception\n";
    return 2;
}