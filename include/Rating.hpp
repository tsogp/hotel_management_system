#ifndef RATING_HPP
#define RATING_HPP

#include <iostream>
using namespace std;

class Rating
{
    private:
        string rater;
        int rating;
        string comment;
    
    public:
        Rating(string raterVal,int ratingVal, string commentVal)
        :rater(raterVal),rating(ratingVal), comment(commentVal){}

        friend class House;
        friend class Member;
};

#endif