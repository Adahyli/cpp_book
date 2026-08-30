
#pragma once

#include <stdexcept>
#include <string>

[[noreturn]] inline void error(const std::string& e) {
    throw std::runtime_error(e);
}

[[noreturn]] inline void error(const std::string& s1, const std::string& s2)
{
    throw std::runtime_error(s1 + s2);
}