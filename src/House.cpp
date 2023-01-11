#ifndef HOUSE_CPP
#define HOUSE_CPP

#include <algorithm>

#include "../include/House.hpp"

using std::find;

House::House(
    unsigned int memberIDVal,
    string locationVal, 
    string descriptionVal, 
    pair<Date, Date> availableDateRangeVal, 
    double priceVal,
    vector<Date> unavailableDatesVal
) : memberID(memberIDVal),
    location(locationVal), 
    description(descriptionVal), 
    availableDateRange(availableDateRangeVal), 
    pricePerDay(priceVal),
    unavailableDates(unavailableDatesVal) {};

void House::getAvailableDates() {
    unsigned short currentDay = availableDateRange.first.day, 
                   currentMonth = availableDateRange.first.month,
                   currentYear = availableDateRange.first.year;
    
    while (true) {
        Date currentDate(currentDay, currentMonth, currentYear);
        unsigned short dateConstraintCheckResponse = currentDate.constraintCheck(currentDay, currentMonth, currentYear, true);
        
        bool isCurrentDateIsUnavailable = false;
        for (Date &date: unavailableDates) {
            if (date == currentDate) {
                isCurrentDateIsUnavailable = true;
                break;
            }
        }

        if (dateConstraintCheckResponse && !isCurrentDateIsUnavailable) {
            cout << currentDate.stringifyDate() << '\n';
            if (currentDay == availableDateRange.second.day && currentMonth == availableDateRange.second.month && currentYear == availableDateRange.second.year) {
                break;
            }
            currentDay++;
        } else {
            currentDay = 1;
            if (currentMonth == 12) {
                currentMonth = 1;
                currentYear++;
            } else {
                currentMonth++;
            }
        }
    }
}

unsigned int House::isAvailable(pair<Date, Date> dateRange) {
    unsigned short currentDay = dateRange.first.day, 
                   currentMonth = dateRange.first.month,
                   currentYear = dateRange.first.year;
    
    unsigned int dayAmount = 0;
    while (true) {
        dayAmount++;

        Date currentDate(currentDay, currentMonth, currentYear);
        unsigned short dateConstraintCheckResponse = currentDate.constraintCheck(currentDay, currentMonth, currentYear);
        
        for (Date &date: unavailableDates) {
            if (date == currentDate) {
                return false;
            }
        }

        if (dateConstraintCheckResponse) {
            if (currentDay == dateRange.second.day && currentMonth == dateRange.second.month && currentYear == dateRange.second.year) {
                break;
            }
            currentDay++;
        } else {
            currentDay = 1;
            if (currentMonth == 12) {
                currentMonth = 1;
                currentYear++;
            } else {
                currentMonth++;
            }
        }
    }

    return dayAmount;
}

void House::makeUnavailable(pair<Date, Date> dateRange) {
    unsigned short currentDay = dateRange.first.day, 
                   currentMonth = dateRange.first.month,
                   currentYear = dateRange.first.year;
    
    while (true) {
        Date currentDate(currentDay, currentMonth, currentYear);
        unsigned short dateConstraintCheckResponse = currentDate.constraintCheck(currentDay, currentMonth, currentYear);
        
        unavailableDates.push_back(currentDate);

        if (dateConstraintCheckResponse) {
            if (currentDay == dateRange.second.day && currentMonth == dateRange.second.month && currentYear == dateRange.second.year) {
                break;
            }
            currentDay++;
        } else {
            currentDay = 1;
            if (currentMonth == 12) {
                currentMonth = 1;
                currentYear++;
            } else {
                currentMonth++;
            }
        }
    }
}

void House::viewHouseInfo() {
    cout << "Location: " << location << '\n'
         << "Description: " << description << '\n'
         << "Daily price: " << pricePerDay << "\n\n";
}

#endif