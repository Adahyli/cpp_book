#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <exception>

void error (std::string e){
    std::cerr << e << std::endl;
}

class Token{
public:
 char kind; // what kind of token
 double value; // for numbers: a value
 Token(char k) :kind{k}, value{0.0}{} // construct from one value
 Token(char k, double v) :kind{k}, value{v}{} // construct from two values

};

Token get_token()
{
    char ch;
    std::cin >> ch;

    switch (ch) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
        return Token{ch};

    default:
        if (std::isdigit(ch)) {
            std::cin.putback(ch);

            double val;
            std::cin >> val;

            return Token{'8', val}; // example number token
        }
    }
}

double expression(){
    double left = term(); // read and evaluate a Term
    Token t = get_token(); // get the next token
    while (true) {
        switch (t.kind) {
        case '+':
            left += term(); // evaluate Term and add
            t = get_token();
            break;
        case '-':
            left -= term(); // evaluate Term and subtract
            t = get_token();
            break;
        default:
            return left; // finally: no more + or -; return the answer
        }
    }
}


double term(){
    double left = primary();
    Token t = get_token();
    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = get_token();
            break;
        case '/':
            {   double d = primary();
                if (d == 0)
                error("divide by zero");
                left /= d;
                t = get_token();
                break;
            }
        default:
            return left;
        }
    }
}

double primary(){
    Token t = get_token();
    switch (t.kind) {
    case '(': // handle ’(’ expression ’)’
        {   double d = expression();
            t = get_token();
            if (t.kind != ')')
            error("')' expected");
            return d;
        }
    case '8': // we use ’8’ to represent a number
        return t.value; // return the number’s value
    default:
        error("primary expected");
 }
}

int main()
    try{
        while (std::cin)
        std::cout << expression() << '\n';
        }
        catch (std::exception& e) {
            std::cerr << e.what() << '\n';
            return 1;
        }
        catch (...) {
            std::cerr << "exception \n";
            return 2;
}