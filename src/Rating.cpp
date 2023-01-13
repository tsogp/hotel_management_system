#ifndef RATING_CPP
#define RATING_CPP

#include "../include/Rating.hpp"

// Rating constructor
Rating::Rating(unsigned int IDVal, string raterNameVal, string messageVal, short ratingVal, bool ratingForHouseVal) 
    : ID(IDVal), raterName(raterNameVal), message(messageVal), rating(ratingVal), ratingForHouse(ratingForHouseVal) {};

// Function to print the info stored in rating object
void Rating::viewRatingInfo() {
    cout << "\nRated by: " << raterName << '\n'
         << "Message: " << message << '\n'
         << "Rating: " << rating << "\n\n";
}

#endif