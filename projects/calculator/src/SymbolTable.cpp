
#include "SymbolTable.h"
#include "Error.h"


double Symbol_table::get_value(std::string s) {
    for (const Variable& v : var_table)
        if (v.name == s)
            return v.value;
    error("trying to read undefined variable\n ", s);
}

void Symbol_table::set_value(std::string s, double d) {
    for (Variable& v : var_table)
        if (v.name == s) {
            v.value = d;
            return;
        }
    error("trying to write undefined variable ", s);
}

bool Symbol_table::is_declared(std::string var) {
    for (const Variable& v : var_table)
        if (v.name == var)
            return true;
    return false;
}

double Symbol_table::define_name(std::string var, double val) {
    if (is_declared(var))
        error(var, " declared twice");
    var_table.push_back(Variable{ var,val });
    return val;
}
