#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <cctype>
#include <cmath>

constexpr char number = '8';
constexpr char quit = 'x';
constexpr char print = '=';
constexpr char printc = ';';
constexpr std::string prompt = "> ";
constexpr std::string result = "= "; 

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
    void ignore(char c1,char c2);

private:
    bool full {false};
    Token buffer {' '};
};


class Variable {
public:
    std::string name;
    double value;
};

//puts a token from input stream into the token stream
void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");

    buffer = t;
    full = true;
}

void Token_stream::ignore(char c1,char c2){
    if (full &&  buffer.kind == c1|| buffer.kind == c2) { 
        full = false;
        return;
        }
    full = false;
    char ch = 0;
    while (std::cin>>ch)
        if (ch == c1 || ch == c2)
            return;
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
    case print:
    case printc:
    case quit:
    case '!':
    case '%':
        return Token{ch};

    default:
        if (std::isdigit(ch)) {
            std::cin.putback(ch);

            double val;
            std::cin >> val;

            return Token{number, val};
        }

        error("Bad token");
    }
}

//declarations
double expression();
double term();
double primary();
double factorial();
bool calculate();
void introduction();
void clean_up_mess();
Token_stream ts;


//parser functions
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
                error(" can not divide by zero");
            left /= d;
            t = ts.get();
            break;
            }
        case '%':
            { double d = factorial();
            if (d == 0)
                error(" can not divide by zero");
            left = fmod(left,d);
            t = ts.get();
            break;
            }
        default:
            ts.putback(t); 
            return left;
            }
    }
}

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
    case number: 
        return t.value; 
    case '-':
        return - primary();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
}

void clean_up_mess() {
    ts.ignore(print,printc);

}

//other functions
bool calculate(){
    double val = 0;

    while (std::cin)  {
        try{
            std::cout << prompt;
            Token t = ts.get();

            switch (t.kind) {
            case quit:
                return false;  

            case print:
                std::cout << result << val << '\n';
                return true;   
        
            case printc:
                std::cout << result << val << '\n';
                return true;

            default:
                ts.putback(t);
                val = expression();
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n'; 
            clean_up_mess();
        }

    }

    return false;
    
}

void introduction(){
    std::cout << "Welcome to our simple calculator.\n";
    std::cout << "Please enter expressions using floating-point numbers.\n";
    std::cout << "Available operators: +, -, *, /, !, and parentheses.\n";
    std::cout << "Use '=' to print the result and 'x' to exit.\n";
}


int main()
try {
    introduction();

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