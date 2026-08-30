
#pragma once

#include <string>
#include <vector>

class Variable {
public:
    std::string name;
    double value;
};

class Symbol_table {
public:
    double get_value(std::string s);
    void set_value(std::string s, double d);
    bool is_declared(std::string var);
    double define_name(std::string var, double val);

private:
    std::vector<Variable> var_table;
};