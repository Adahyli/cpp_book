
#pragma once

#include "Token.h"

#include <istream>

class Token_stream {
public:
    explicit Token_stream(std::istream& input)
    : input{&input}
    {}

    void set_input(std::istream& in);

    Token get();
    void putback(Token t);
    void ignore(char c1, char c2);

private:
    std::istream* input;

    bool full{ false };
    Token buffer{ ' ' };

};