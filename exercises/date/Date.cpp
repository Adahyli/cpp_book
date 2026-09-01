#include "date.h"

#include <stdexcept>
#include <iostream>

Date::Date(int yy, Month mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
    if (!is_valid())
        throw std::runtime_error{"Invalid date"};
}

bool Date::is_valid() const
{
    return 1 <= static_cast<int>(m)
        && static_cast<int>(m) <= 12
        && 1 <= d
        && d <= 31;
}

void Date::add_day(int n)
{
    d += n;

    while (d > 31) {
        d -= 31;
        ++m;
    }
}

int Date::year() const
{
    return y;
}

Date::Month Date::month() const
{
    return m;
}

int Date::day() const
{
    return d;
}

Date::Month operator++(Date::Month& m)
{
    if (m == Date::Month::dec)
        m = Date::Month::jan;
    else
        m = static_cast<Date::Month>(
            static_cast<int>(m) + 1
        );

    return m;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.year()
       << '/'
       << static_cast<int>(date.month())
       << '/'
       << date.day();

    return os;
}
