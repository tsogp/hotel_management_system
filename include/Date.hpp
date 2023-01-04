#ifndef DATE_HPP
#define DATE_HPP

#include <string>

using std::string;
using std::to_string;

class Date {
public:
    unsigned short day, month, year; 
    Date(unsigned short dayVal, unsigned short monthVal, unsigned short yearVal) 
        : day(dayVal), month(monthVal), year(yearVal) {};

    string stringifyDate();
};

#endif