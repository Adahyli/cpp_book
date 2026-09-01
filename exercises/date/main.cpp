#include "date.h"
#include <iostream>

int main()
{
    Date today{2020, Date::Month::feb, 2};

    Date tomorrow = today;
    tomorrow.add_day(1);

    std::cout << "Today: " << today << '\n';
    std::cout << "Tomorrow: " << tomorrow << '\n';

}