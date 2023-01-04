#ifndef HOUSE_CPP
#define HOUSE_CPP

#include <algorithm>

#include "../include/House.hpp"

using std::find;

House::House(string locationVal, string descriptionVal, pair<Date, Date> availableDateRangeVal, vector<Date> unavailableDatesVal, double price) {

};

void House::getAvailableDates() {
    for (unsigned short year = availableDateRange.first.year; year < availableDateRange.second.year; year++) {
        for (unsigned short month = availableDateRange.first.month; month < availableDateRange.second.month; month++) {
            for (unsigned short day = availableDateRange.first.day; day < availableDateRange.second.day; day++) {
                Date currentDate(day, month, year);
                vector<Date>::iterator isDateUnavailable = find(unavailableDates.begin(), unavailableDates.end(), currentDate);

                if (isDateUnavailable == unavailableDates.end()) {
                    std::cout << "available date: " << currentDate.stringifyDate() << '\n';
                }
            }    
        }
    }
}

#endif