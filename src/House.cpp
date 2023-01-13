#ifndef HOUSE_CPP
#define HOUSE_CPP

#include <algorithm>

#include "../include/House.hpp"

using std::find;

// House constructor
House::House(
    unsigned int memberIDVal,
    string locationVal, 
    string descriptionVal, 
    pair<Date, Date> availableDateRangeVal, 
    double priceVal,
    double minRequiredRating,
    vector<Date> unavailableDatesVal
) : memberID(memberIDVal),
    location(locationVal), 
    description(descriptionVal), 
    availableDateRange(availableDateRangeVal), 
    pricePerDay(priceVal),
    minRequiredRating(minRequiredRating),
    unavailableDates(unavailableDatesVal) {};

// Function to get the available dates of this house
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

        if (dateConstraintCheckResponse) {
            if (!isCurrentDateIsUnavailable) {
                cout << currentDate.stringifyDate() << '\n';
            }

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

// Function to check if this house is available in a certain time period
unsigned int House::isAvailable(pair<Date, Date> dateRange) {
    if (dateRange.first > dateRange.second) {
        return false;
    }

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

// Function to make a house unavailable for a certain period of time
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

// Function to the the general info about the house
void House::viewHouseInfo() {
    cout << "Location: " << location << '\n'
         << "Description: " << description << '\n'
         << "Daily price: " << pricePerDay << '\n'
         << "Rating: " << rating << '\n'
         << "Minimal required rating: " << minRequiredRating << "\n\n"
         << "Available dates: \n";
    getAvailableDates();
    if (ratings.size() > 0) {
        cout << "House ratings: \n";
        for (Rating &rating: ratings) {
            rating.viewRatingInfo();
        }
    }
}

// Function to calculate house rating
void House::calculateRating() {
    double averageRating = 0.0;
    for (Rating &rating: ratings) {
        averageRating += rating.rating;
    }

    rating = averageRating / ratings.size();
}

#endif