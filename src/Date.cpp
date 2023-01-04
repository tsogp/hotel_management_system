#ifndef DATE_CPP
#define DATE_CPP

#include "../include/Date.hpp"

Date::Date(unsigned short dayVal, unsigned short monthVal, unsigned short yearVal) 
    : day(dayVal), month(monthVal), year(yearVal) {};

string Date::stringifyDate() {
    return to_string(day) = "/" + to_string(month) + "/" + to_string(year);
}


#endif