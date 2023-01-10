#ifndef HOUSE_HPP
#define HOUSE_HPP

#include <vector>
#include "Member.hpp"

class House
{
    private:
        string name;
        string location;
        string description;
        vector<Rating> houseRating;
        vector<int> userID;
        int occupy;

    public:
        House(string nameVal = "", string locationVal = "",string descriptionVal = "", vector<Rating> houseRating = {}, vector<int> userIDVal = {},
              int occupyVal = 0)
            :name(nameVal), location(locationVal), description(descriptionVal), houseRating(houseRating),
             userID(userIDVal), occupy(occupyVal){}

        double average()
        {
            double average,total = 0;
            int count = 0;
            while (count != houseRating.size())
            {
                total = total + houseRating[count].rating;
                count++;
            }
            average = total/count; 
            
            return average;
        }

        friend class Member;
        friend class System;
};

#endif