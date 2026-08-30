
#pragma once

#include "TokenStream.h"
#include "SymbolTable.h"

#include <istream>
#include <ostream>

class Calculator {
public:
    Calculator(std::istream& input,
        std::ostream& output,
        std::ostream& error_output);

    void run();

private:
    std::istream& input;

    Token_stream ts;
    Symbol_table symbols;

    std::ostream& out;
    std::ostream& err;

    double statement();
    double expression();
    double term();
    double factorial();
    double primary();
    double declaration();

    bool calculate();
    void introduction();
    void clean_up_mess();

};