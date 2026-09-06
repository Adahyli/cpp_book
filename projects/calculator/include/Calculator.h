
#pragma once

#include "TokenStream.h"
#include "SymbolTable.h"

#include <istream>
#include <ostream>
#include <fstream>

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

    std::ifstream input_file;
    std::ofstream output_file;

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