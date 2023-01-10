#ifndef HOUSE_HPP
#define HOUSE_HPP

#include <iostream>
#include <vector>
#include <cstring>
#include <utility>

using std::cout;
using std::string;
using std::pair;
using std::make_pair;
using std::vector;

#include "Date.hpp"
class House {
    private:
        unsigned int memberID;
        string location;
        string description;
        pair<Date, Date> availableDateRange;
        vector<Date> unavailableDates;
        double pricePerDay;
    public:
        House(
            unsigned int memberIDVal,
            string locationVal, 
            string descriptionVal, 
            pair<Date, Date> availableDateRangeVal, 
            double priceVal,
            vector<Date> unavailableDatesVal = {}
        );

        friend class Member;
        friend class System;
        friend class Request;

        void getAvailableDates();
        void viewHouseInfo();
        bool isAvailable(pair<Date, Date> dateRange);
        void makeUnavailable(pair<Date, Date> dateRange);
};

#endif