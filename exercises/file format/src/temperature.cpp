
#include "temperature.h"
#include "error.cpp"

#include <iostream>

void fill_vector(std::istream& ist, std::vector<int>& v, char terminator){
    for (int x; ist >> x;)
        v.push_back(x);

    if (ist.eof())
        return;

    if (ist.bad())
        error("ist is bad");

    if (ist.fail()) {
        ist.clear();

        char c = 0;
        ist >> c;

        if (c != terminator) {
            ist.unget();
            ist.clear(std::ios::failbit);
        }
    }
}

std::istream& operator>>(std::istream& is,Reading& r)
{
    char ch1 = 0;

    if (is >> ch1 && ch1 != '(') {
        is.unget();
        is.clear(std::ios::failbit);
        return is;
    }

    char ch2 = 0;
    int d;
    int h;
    double t;

    is >> d >> h >> t >> ch2;

    if (!is || ch2 != ')')
        error("bad reading");

    r.day = d;
    r.hour = h;
    r.temperature = t;

    return is;
}

std::istream& operator>>(std::istream& is, Month& m)
{
    char ch = 0;

    if (is >> ch && ch != '{') {
        is.unget();
        is.clear(std::ios::failbit);
        return is;
    }

    std::string month_marker;
    std::string mm;

    is >> month_marker >> mm;

    if (!is || month_marker != "month")
        error("bad start of month");

    m.month = month_to_int(mm);

    int duplicates = 0;
    int invalids = 0;

    for (Reading r; is >> r;) {
        if (is_valid(r)) {

            if (m.day[r.day].hour[r.hour] != not_a_reading)
                ++duplicates;

            m.day[r.day].hour[r.hour] = r.temperature;
        }
        else {
            ++invalids;
        }
    }

    if (invalids)
        error("invalid readings in month");

    if (duplicates)
        error("duplicate readings in month");

    end_of_loop(
        is,
        '}',
        "bad end of month");

    return is;
}


std::istream& operator>>(std::istream& is,Year& y){

    char ch = 0;

    is >> ch;

    if (ch != '{') {
        is.unget();
        is.clear(std::ios::failbit);
        return is;
    }

    std::string year_marker;
    int yy = -1;

    is >> year_marker >> yy;

    if (!is || year_marker != "year")
        error("bad start of year");

    y.year = yy;

    while (true) {
        Month m;

        if (!(is >> m))
            break;

        y.month[m.month] = m;
    }

    end_of_loop(
        is,
        '}',
        "bad end of year");

    return ;
}

int month_to_int(const std::string& s)
{
    std::vector<std::string> month_input_tbl{
        "jan", "feb", "mar", "apr", "may", "jun",
        "jul", "aug", "sep", "oct", "nov", "dec"
    };

    for (int i = 0; i < 12; ++i)
        if (month_input_tbl[i] == s)
            return i;

    return -1;
}

bool is_valid(const Reading& r)
{
    constexpr int implausible_min = -200;
    constexpr int implausible_max = 200;

    if (r.day < 1 || r.day > 31)
        return false;

    if (r.hour < 0 || r.hour > 23)
        return false;

    if (r.temperature < implausible_min ||
        r.temperature > implausible_max)
        return false;

    return true;
}

void end_of_loop(
    std::istream& ist,
    char term,
    const std::string& message)
{
    if (ist.fail()) {
        ist.clear();

        char ch = 0;

        if (ist >> ch && ch == term)
            return;

        error(message);
    }
}

std::ostream& operator<<(std::ostream& os, const Year& y){
    return os << y.year;
    }

void print_year(std::ostream& ost, const Year& y){
    ost << y;
}