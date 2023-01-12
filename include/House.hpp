#ifndef HOUSE_HPP
#define HOUSE_HPP

#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

using std::cout;
using std::string;
using std::pair;
using std::make_pair;
using std::vector;

#include "Date.hpp"
#include "Rating.hpp"

class House {
    private:
        unsigned int memberID;
        double rating = 0.0;
        double minRequiredRating = 0.0;
        string location;
        string description;
        pair<Date, Date> availableDateRange;
        vector<Date> unavailableDates;
        vector<Rating> ratings;
        double pricePerDay;
    public:
        House(
            unsigned int memberIDVal,
            string locationVal, 
            string descriptionVal, 
            pair<Date, Date> availableDateRangeVal, 
            double priceVal,
            double minRequiredRating,
            vector<Date> unavailableDatesVal = {}
        );

        friend class Member;
        friend class System;
        friend class Request;

        void calculateRating();
        void getAvailableDates();
        void viewHouseInfo();
        unsigned int isAvailable(pair<Date, Date> dateRange);
        void makeUnavailable(pair<Date, Date> dateRange);
};

#endif