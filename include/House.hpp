#ifndef HOUSE_HPP
#define HOUSE_HPP

#include <iostream>
#include <vector>
#include <cstring>

using std::string;

#include "Member.hpp"

class House {
    private:
        string location;
        string description;
    public:
        //House class will be declared in the Member
        House(string locationVal, string descriptionVal)
            : location(locationVal), description(descriptionVal) {}
        
        friend class Member;
        friend class System;
        void getAvailableDates();
};

#endif