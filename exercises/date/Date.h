#pragma once

#include <iostream>

class Date {
public:
    enum class Month {
        jan = 1,
        feb,
        mar,
        apr,
        may,
        jun,
        jul,
        aug,
        sep,
        oct,
        nov,
        dec
    };

    Date(int y, Month m, int d);

    void add_day(int n);

    int year() const;
    Month month() const;
    int day() const;

    bool is_valid() const;

private:
    int y;
    Month m;
    int d;
};

Date::Month operator++(Date::Month& m);

std::ostream& operator<<(std::ostream& os, const Date& date);