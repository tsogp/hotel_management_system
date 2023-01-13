#ifndef DATE_HPP
#define DATE_HPP

#include <string>
#include <iostream>
#include <utility>

using std::string;
using std::to_string;
using std::cout;
using std::cin;
using std::getline;
using std::pair;

class Date {
private:
    unsigned short day, month, year; 
public:
    Date(string inputMessage = "");
    Date(unsigned short day, unsigned short month, unsigned short year);

    friend class House;

    static bool isStringNumeric(const string& str);

    bool constraintCheck(unsigned short dayVal, unsigned short monthVal, unsigned short yearVal, bool isErrorMessageNeeded = false);
    void defaultErrorMessage();
    string stringifyDate(bool forIO = false);

    friend bool operator == (Date &, Date &);
    friend bool operator > (Date &, Date &);
};

#endif