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


// Token_stream stores a token in a buffer
class Token_stream {
public:
    Token get();
    void putback(Token t);

private:
    bool full {false};
    Token buffer {' '};
};


//declarations
double expression();
double term();
double primary();
double factorial();
Token_stream ts;
void print();
void quit();
bool calculate();

//puts a token from input stream into the token stream
void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");

    buffer = t;
    full = true;
}


//returns operations into token stream and assigns numbers to value
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
    case '{':
    case '}':
    case '=':
    case 'x':
    case '!':
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


//parser functions
//handles + and -
double expression(){
    double left = term(); 
    Token t = ts.get(); 
    while (true) {
        switch (t.kind) {
        case '+':
            left += term(); 
            t = ts.get();
            break;
        case '-':
            left -= term(); 
            t = ts.get();
            break;
        default:
            ts.putback(t); 
            return left;
        }
    }
}

//handles * and /
double term(){
    double left = factorial();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '*':
            left *= factorial();
            t = ts.get();
            break;
        case '/':
            { double d = factorial();
            if (d == 0)
                error("divide by zero");
            left /= d;
            t = ts.get();
            break;
            }
        default:
            ts.putback(t); 
            return left;
            }
    }
}

//handles !
double factorial(){
    double left = primary();
    Token t = ts.get();

    if (t.kind != '!') {
        ts.putback(t);
        return left;
    }

    int x = static_cast<int>(left);

    int result = 1;

    for (int i = x; i > 0; --i) {
        result *= i;
    }

    return result;
}

//handles () and numbers
double primary(){
    Token t = ts.get();
    switch (t.kind) {
    case '(': 
        {   double d = expression();
            t = ts.get();
            if (t.kind != ')')
            error("')' expected");
            return d;
        }
    case '{': 
        {   double d = expression();
            t = ts.get();
            if (t.kind != '}')
            error("'}' expected");
            return d;
        }
    case '8': 
        return t.value; 
    default:
        error("primary expected");
    }
}


//other functions
void print(double val)
{
    std::cout << "=" << val << '\n';
}

bool quit(Token t)
{
    return t.kind == 'x';
}

bool calculate()
{
    double val = 0;

    while (std::cin) {
        Token t = ts.get();

        switch (t.kind) {
        case 'x':
            return false;  // tell main to quit

        case '=':
            std::cout << "=" << val << '\n';
            return true;   // expression finished

        default:
            ts.putback(t);
            val = expression();
            break;
        }
    }

    return false;
}

int main()
try {
    double val = 0;  
    std::cout << "Welcome to our simple calculator.\n";
    std::cout << "Please enter expressions using floating-point numbers.\n";
    std::cout << "Available operators: +, -, *, /, !, and parentheses.\n";
    std::cout << "Use '=' to print the result and 'x' to exit.\n";

    while (calculate()){

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