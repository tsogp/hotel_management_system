#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

#include "Request.hpp"
#include "House.hpp"
#include "Rating.hpp"
#include "Date.hpp"

class Member {
private:
    string username;
    string name;
    string password;
    int phoneNo;
public:
    //Will include House class for the user to add later 
    Member(string usernameVal, string nameVal, string passwordVal, int phoneNoVal)
            : username(usernameVal), name(nameVal), password(passwordVal), phoneNo(phoneNoVal) {};
    
    // All function will be pushed to System class
    bool registerUser();
    void viewHouses();
    bool loginUser();
    bool searchHouse();
    bool requestToRentAHouse();
    void acceptRequestForAHouse();
    bool occupyAHouse();
    bool rateAHouse();
    bool rateAnOwner();

    friend class System;
};

#endif