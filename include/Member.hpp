#ifndef MEMBER_HPP
#define MEMBER_HPP

#include "Request.hpp"
#include "House.hpp"
#include "Rating.hpp"

class Member
{
    private:
        int ID;
        string userType;
        string username;
        string name;
        string password;
        int phoneNo;
        double credits;
        House house;
        vector<Rating> occupierRating;

    public:
        //Will include House class for the user to add later 
        Member(int IDVal, string userTypeVal, string usernameVal, string nameVal
                , string passwordVal, int phoneNoVal, double creditsVal, 
                string locationVal = "", string descriptionVal = "", vector<Rating> ratingVal = {})
                :ID(IDVal), userType(userTypeVal), username(usernameVal), name(nameVal),
                password(passwordVal), phoneNo(phoneNoVal), credits(creditsVal),
                house(locationVal,descriptionVal), occupierRating(ratingVal){}

        double average()
        {
            double average,total = 0;
            int count = 0;
            while (count != occupierRating.size())
            {
                total = total + occupierRating[count].rating;
                count++;
            }
            average = total/count; 
            
            return average;
        }

        friend class System;
};

#endif