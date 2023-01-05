#ifndef DATE_HPP
#define DATE_HPP

#include <string>
#include <iostream>

using std::string;
using std::to_string;
using std::cout;
using std::cin;

class Date {
public:
    unsigned short day, month, year; 
    Date(string inputMessage);

    bool constraintCheck(unsigned short dayVal, unsigned short monthVal, unsigned short yearVal);
    void defaultErrorMessage();
    string stringifyDate();
};

#endif