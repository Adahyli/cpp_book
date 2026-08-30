
#pragma once

#include <string>

class Token {
public:
    char kind{ 0 };
    double value{ 0.0 };
    std::string name;

    Token() = default;

    Token(char k)
        : kind{ k }
    {
    }

    Token(char k, double v)
        : kind{ k }, value{ v }
    {
    }

    Token(char ch, std::string n)
        : kind{ ch }, name{ n }
    {
    }
};