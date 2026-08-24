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
constexpr char quit = 'q';
constexpr char print = '=';
constexpr char printc = ';';
constexpr std::string prompt = "> ";
constexpr std::string result = "= "; 
const char name = 'a'; 
const char let = 'L'; 
const std::string declkey = "let"; 
const char sqrt_key = 's';
const std::string sqrtkey = "sqrt";


[[noreturn]] void error(const std::string& e){
    throw std::runtime_error(e);
}

[[noreturn]] void error(const std::string& s1, const std::string& s2)
{
    throw std::runtime_error(s1 + s2);
}


class Token{
public:
 char kind; 
 double value; 
 std::string name;
 Token() :kind{0} {}
 Token(char k) :kind{k}, value{0.0}{} 
 Token(char k, double v) :kind{k}, value{v}{}
 Token(char ch, std::string n) :kind{ch}, name{n} { }

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

//puts a token from input stream into the token stream
void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");

    buffer = t;
    full = true;
}

void Token_stream::ignore(char c1,char c2){
    if (full &&  (buffer.kind == c1 || buffer.kind == c2)) { 
        full = false;
        return;
        }
    full = false;
    char ch = 0;
    while (std::cin>>ch){
        if (ch == c1 || ch == c2)
            return;
    }
}

//returns operations into token stream and assigns numbers to value and keys to string
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

        if (std::isalpha(ch)) {
            std::string s;
            s += ch;
            while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch))){
                if (!std::isalpha(ch) && !std::isdigit(ch))
                    break;

                s += ch;
            }
            if (std::cin)
                std::cin.putback(ch);

            if (s == declkey)
                return Token{let};

            if (s == sqrtkey)
                return Token{sqrt_key};


            return Token{name, s};
        }
        error("Bad token");
    }
}


class Variable {
public:
    std::string name;
    double value;
};

std::vector<Variable> var_table;

double get_value(std::string s){
    for (const Variable& v : var_table)
        if (v.name == s)
            return v.value;
    error("trying to read undefined variable\n ", s);
}

void set_value(std::string s, double d){
    for (Variable& v : var_table)
        if (v.name == s) {
            v.value = d;
            return;
        }
    error("trying to write undefined variable ", s);
}

bool is_declared(std::string var){
    for (const Variable& v : var_table)
        if (v.name == var)
            return true;
    return false;
}

double define_name(std::string var, double val){
    if (is_declared(var))
        error(var," declared twice");
    var_table.push_back(Variable{var,val});
    return val;
}


//declarations
double statement();
double expression();
double term();
double primary();
double factorial();
double declaration();
bool calculate();
void introduction();
void clean_up_mess();
double get_value(std::string s);
void set_value(std::string s, double d);
bool is_declared(std::string var);
double define_name(std::string var, double val);
Token_stream ts;


//parser functions
double statement(){
    Token t = ts.get();
    switch (t.kind) {
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

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
            if (t.kind != ')'){
                error("')' expected");
            }
            return d;
        }
    case '{': 
        {   double d = expression();
            t = ts.get();
            if (t.kind != '}'){
                error("'}' expected");
            }
            return d;
        }
    case number: 
        return t.value; 
    case name:
        return get_value(t.name);
    case '-':
        return - primary();
    case '+':
        return primary();
    case sqrt_key:
        {   t = ts.get();

            if (t.kind != '('){
                error("'(' expected after sqrt");
            }

            double d = expression();

            t = ts.get();

            if (t.kind != ')'){
                error("')' expected after sqrt");
            }

            return std::sqrt(d);
        }
    default:
        error("primary expected");
    }
}

double declaration(){
    Token t = ts.get();

    if (t.kind != name){
        error ("name expected in declaration");
    }

    Token t2 = ts.get();

    if (t2.kind != (print || printc)){
        error("= missing in declaration of ", t.name);
    }

    double d = expression();

    define_name(t.name,d);

    return d;
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
                val = statement();
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
    std::cout << "Use "<< print << " or " << printc << " to print the result and " << quit << " to exit.\n";
}

void clean_up_mess() {
    ts.ignore(print,printc);

}


int main()
try {
    introduction();

    define_name("pi",3.1415926535);
    define_name("e",2.7182818284);
    define_name("k", 1000);

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