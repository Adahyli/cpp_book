
#include "Calculator.h"

#include "Constants.h"
#include "Error.h"

#include <cmath>
#include <exception>

Calculator::Calculator(
    std::istream& input,
    std::ostream& output,
    std::ostream& error_output)
    : input{input},
    ts{input},
    out{output},
    err{error_output}

{   
    symbols.define_name("pi", 3.1415926535);
    symbols.define_name("e", 2.7182818284);
    symbols.define_name("k", 1000);
}

double Calculator::statement() {
    Token t = ts.get();
    switch (t.kind) {
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

double Calculator::expression() {
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

double Calculator::term() {
    double left = factorial();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '*':
            left *= factorial();
            t = ts.get();
            break;
        case '/':
        {
            double d = factorial();
            if (d == 0)
                error(" can not divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = factorial();
            if (d == 0)
                error(" can not divide by zero");
            left = fmod(left, d);
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double Calculator::factorial() {
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

double Calculator::primary() {
    Token t = ts.get();
    switch (t.kind) {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') {
            error("')' expected");
        }
        return d;
    }
    case '{':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != '}') {
            error("'}' expected");
        }
        return d;
    }
    case number:
        return t.value;
    case name:
        return symbols.get_value(t.name);
    case '-':
        return -primary();
    case '+':
        return primary();
    case sqrt_key:
    {
        t = ts.get();

        if (t.kind != '(') {
            error("'(' expected after sqrt");
        }

        double d = expression();

        t = ts.get();

        if (t.kind != ')') {
            error("')' expected after sqrt");
        }

        if (d < 0) {
            error("square root of negative number");
        }

        return std::sqrt(d);
    }
    default:
        error("primary expected");
    }
}

double Calculator::declaration() {
    Token t = ts.get();

    if (t.kind != name) {
        error("name expected in declaration");
    }

    Token t2 = ts.get();

    if (t2.kind != print && t2.kind != printc) {
        error("= missing in declaration of ", t.name);
    }

    double d = expression();

    symbols.define_name(t.name, d);

    return d;
}

//other functions
bool Calculator::calculate() {
    double val = 0;

    while (input) {
        try {
            out << prompt;
            Token t = ts.get();

            switch (t.kind) {
            case quit:
                return false;

            case print:
                out << result << val << '\n';
                return true;

            case printc:
                out << result << val << '\n';
                return true;

            default:
                ts.putback(t);
                val = statement();
                break;
            }
        }
        catch (const std::exception& e) {
            err << e.what() << '\n';
            clean_up_mess();
        }

    }

    return false;

}

void Calculator::introduction() {
    out << "Welcome to our simple calculator.\n";
    out << "Please enter expressions using floating-point numbers.\n";
    out << "Available operators: +, -, *, /, !, and parentheses.\n";
    out << "Use " << print << " or " << printc << " to print the result and " << quit << " to exit.\n";
}

void Calculator::clean_up_mess() {
    ts.ignore(print, printc);

}

void Calculator::run()
{
    introduction();

    while (calculate()) {
    }
}