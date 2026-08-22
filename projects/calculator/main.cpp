#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <cctype>

[[noreturn]] void error(const std::string& e){
    throw std::runtime_error(e);
}

class Token{
public:
 char kind; 
 double value; 
 Token(char k) :kind{k}, value{0.0}{} 
 Token(char k, double v) :kind{k}, value{v}{}

};

class Token_stream {
public:
    Token get();
    void putback(Token t);

private:
    bool full {false};
    Token buffer {' '};
};

double expression();
double term();
double primary();
Token_stream ts;

void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");

    buffer = t;
    full = true;
}

Token Token_stream::get()
{
    if (full) {
        full = false;
        return buffer;
    }

    char ch;
    std::cin >> ch;

    switch (ch) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case ';':
    case 'q':
        return Token{ch};

    default:
        if (std::isdigit(ch)) {
            std::cin.putback(ch);

            double val;
            std::cin >> val;

            return Token{'8', val};
        }

        error("Bad token");
    }
}

double expression(){
    double left = term(); // read and evaluate a Term
    Token t = ts.get(); // get the next Token from the Token stream
    while (true) {
        switch (t.kind) {
        case '+':
            left += term(); // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term(); // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t); // put t back into the token stream
            return left; // finally: no more + or -; return the answer
        }
    }
}

double term(){
    double left = primary();
    Token t = ts.get(); // get the next Token from the Token stre
    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
            { double d = primary();
            if (d == 0)
                error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
        default:
            ts.putback(t); // put t back into the Token stream
            return left;
            }
    }
}

double primary(){
    Token t = ts.get();
    switch (t.kind) {
    case '(': // handle ’(’ expression ’)’
        {   double d = expression();
            t = ts.get();
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
try {
    double val = 0;  // version 3: 'q' and ';' added

    while (std::cin) {
        Token t = ts.get();

        if (t.kind == 'q')     // 'q' for quit
            break;

        if (t.kind == ';')     // ';' for print now
            std::cout << "=" << val << '\n';

        else
            ts.putback(t);

        val = expression();
    }

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