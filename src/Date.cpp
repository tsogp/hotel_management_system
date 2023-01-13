#ifndef DATE_CPP
#define DATE_CPP

#include "../include/Date.hpp"

// Function to check in the year is leap
bool isYearLeap(unsigned short year) {
    return ((!(year % 4) && (year % 100) || !(year % 400)));
}

// Default constructor of the Date class
Date::Date(string inputMessage) {
    string dayVal = "0", monthVal = "0", yearVal = "0";

    do {
        cout << inputMessage << '\n';
        cout << "Enter day: ";
        
        do {
            getline(cin, dayVal);
        } while (dayVal == "");
        
        if (!((dayVal.length() == 2 || dayVal.length() == 1) && isStringNumeric(dayVal))) {
            cout << "Incorrect day format, please try again.\n";
            dayVal = "0";
            continue;
        }

        cout << "Enter the month: "; 
        do {
            getline(cin, monthVal);
        } while (monthVal == "");
        
        if (!((monthVal.length() == 2 || monthVal.length() == 1) && isStringNumeric(monthVal))) {
            cout << "Incorrect month format, please try again.\n";
            monthVal = "0";
            continue;
        }

        cout << "Enter the year: "; 
        do {
            getline(cin, yearVal);
        } while (yearVal == "");
        
        if (!(yearVal.length() == 4 && isStringNumeric(yearVal))) {
            cout << "Incorrect year format, please try again.\n";
            yearVal = "0";
            continue;
        }
    } while (!constraintCheck(stoi(dayVal), stoi(monthVal), stoi(yearVal), true) || (dayVal == "0" || monthVal == "0" || yearVal == "0"));

    day = stoi(dayVal);
    month = stoi(monthVal);
    year = stoi(yearVal);
};

// Overloaded constructor of the Date class with date attributes (day, month, year) provided
Date::Date(unsigned short dayVal, unsigned short monthVal, unsigned short yearVal)
    : day(dayVal), month(monthVal), year(yearVal) {};

bool Date::isStringNumeric(const string& str) {
    string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        ++it;
    } 
    return it == str.end();
}

// Function to check if this date exists
bool Date::constraintCheck(unsigned short dayVal, unsigned short monthVal, unsigned short yearVal, bool isErrorMessageNeeded) {
    // Booking is only available between 2023 and 2030
    if (!(yearVal <= 2030 && yearVal >= 2023) || !(monthVal <= 12 && monthVal >= 1) || !(dayVal <= 31 && dayVal >= 1)) {
        if (isErrorMessageNeeded) {
            defaultErrorMessage();
        }
        return false;
    }

    if (monthVal == 2) {
        if (isYearLeap(yearVal)) {
            if (!(dayVal <= 29)) {
                if (isErrorMessageNeeded) {
                    defaultErrorMessage();
                }
                return false;
            } else {
                return true;
            }
        } else {
            if (!(dayVal <= 28)) {
                if (isErrorMessageNeeded) {
                    defaultErrorMessage();
                }
                return false;
            } else {
                return true;
            }
        }
    }

    if (monthVal == 4 || monthVal == 6 || monthVal == 9 || monthVal == 11) {
        if (!(dayVal <= 30)) {
            if (isErrorMessageNeeded) {
                defaultErrorMessage();
            }
            return false;
        } else {
            return true;
        }
    }

    return true;
}

// Function to print out the default error message for invalid date.
void Date::defaultErrorMessage() {
    cout << "Your date format is invalid. Please try again.\n";
};

// Function to stringiry Date object either for console or file output
string Date::stringifyDate(bool forIO) {
    char divSymbol = (forIO) ? '\t' : '/';
    return to_string(day) + divSymbol + to_string(month) + divSymbol + to_string(year);
}

// Overloaded operator to check if two Date objects are equal
bool operator == (Date &date1, Date &date2) {
    return date1.day == date2.day && date1.month == date2.month && date1.year == date2.year; 
}

// Overloaded operator to check if the first Date object is greater
bool operator > (Date &date1, Date &date2) {
    return (
        (date1.day > date2.day && date1.month == date2.month && date1.year == date2.year)
            || (date1.month > date2.month && date1.year == date2.year)
            || (date1.year > date2.year) 
    );
}

#endif