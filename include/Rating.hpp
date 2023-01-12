#ifndef RATING_HPP
#define RATING_HPP

#include <string>
#include <iostream>

using std::string;
using std::cout;

class Rating {
private:
    unsigned int ID;
    string raterName;
    string message;
    short rating;
    bool ratingForHouse;
public:
    Rating(unsigned int IDVal, string raterNameVal, string messageVal, short ratingVal, bool ratingForHouseVal = true);

    void viewRatingInfo();

    friend class System;
    friend class Member;
    friend class House;
};

#endif