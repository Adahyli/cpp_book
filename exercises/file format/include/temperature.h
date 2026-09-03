#pragma once

#include <vector>

constexpr int not_a_reading = -7777;
constexpr int not_a_month = -1;

struct Reading {
    int day;
    int hour;
    double temperature;
};

struct Day {
    std::vector<double> hour{24, not_a_reading};
};

struct Month {
    int month = not_a_month;
    std::vector<Day> day{32};
};

struct Year {
    int year;
    std::vector<Month> month{12};
};


void fill_vector(std::istream& ist, std::vector<int>& v, char terminator);

void print_year(std::ostream& ost, const Year& y);