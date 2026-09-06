
#pragma once

#include "Token.h"

#include <istream>
#include <string>

class Token_stream {
public:
    explicit Token_stream(std::istream& input);

    void set_input(std::istream& in);
    std::string get_filename();

    Token get();
    void putback(Token t);
    void ignore(char c1, char c2);

private:
    std::istream* input;

    bool full{ false };
    Token buffer{ ' ' };

};