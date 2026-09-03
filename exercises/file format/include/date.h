#pragma once

#include "error.cpp"

#include <string>
#include <vector>

std::vector<std::string> month_input_tbl = {
 "-not a month-",
 "jan", "feb", "mar", "apr", "may", "jun", 
 "jul", "aug", "sep", "oct", "nov", "dec"
};

int month_to_int(std::string s)
{
 for (int i=1; i<13; ++i)
 if (month_input_tbl[i]==s)
 return i;
 return 0;
}

std::vector<std::string> month_print_tbl = {
 "-not a month-",
 "January", "February", "March", "April", "May", "June", "July",
 "August", "September", "October", "November", "December"
};


std::string int_to_month(int i)
{
 if (i<1 || 12<=i)
 error("bad month index");
 return month_print_tbl[i];
}