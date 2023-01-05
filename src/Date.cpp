#ifndef DATE_CPP
#define DATE_CPP

#include "../include/Date.hpp"

bool isYearLeap(unsigned short year) {
    return ((!(year % 4) && (year % 100) || !(year % 400)));
}

void Date::defaultErrorMessage() {
    cout << "Your date format is invalid. Please try again.\n";
};

Date::Date(string inputMessage) {
    unsigned short dayVal = 0, monthVal = 0, yearVal = 0;

    while (!constraintCheck(dayVal, monthVal, yearVal)) {
        cout << inputMessage << '\n';
        cin >> dayVal >> monthVal >> yearVal;
    }

    day = dayVal;
    month = monthVal;
    year = yearVal;
};

bool Date::constraintCheck(unsigned short dayVal, unsigned short monthVal, unsigned short yearVal) {
    // Booking is only available between 2023 and 2030
    if (!(yearVal <= 2030 && yearVal >= 2023) || !(monthVal <= 12 && monthVal >= 1) || !(dayVal <= 31 && dayVal >= 1)) {
        defaultErrorMessage();
        return false;
    }

    if (monthVal == 2) {
        if (isYearLeap(yearVal)) {
            if (!(dayVal <= 29)) {
                defaultErrorMessage();
                return false;
            } else {
                return true;
            }
        } else {
            if (!(dayVal <= 28)) {
                defaultErrorMessage();
                return false;
            } else {
                return true;
            }
        }
    }

    if (monthVal == 4 || monthVal == 6 || monthVal == 9 || monthVal == 11) {
        if (!(dayVal <= 30)) {
            defaultErrorMessage();
            return false;
        } else {
            return true;
        }
    }
}

string Date::stringifyDate() {
    return to_string(day) = "/" + to_string(month) + "/" + to_string(year);
}

#endif