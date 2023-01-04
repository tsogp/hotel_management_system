#ifndef HOUSE_HPP
#define HOUSE_HPP

#include <iostream>
#include <vector>
#include <cstring>

using std::cout;
using std::string;
using std::pair;
using std::vector;

#include "Member.hpp"
#include "Date.hpp"

class House {
    private:
        string location;
        string description;
        pair<Date, Date> availableDateRange;
        vector<Date> unavailableDates;
        double price;
    public:
        // House class will be declared in the Member
        House(string locationVal, string descriptionVal, pair<Date, Date> availableDateRangeVal, vector<Date> unavailableDatesVal, double priceVal)
            : location(locationVal), description(descriptionVal), availableDateRange(availableDateRangeVal), unavailableDates(unavailableDatesVal), price(priceVal) {}
        
        friend class Member;
        friend class System;

        void getAvailableDates();
};

#endif