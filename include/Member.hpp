#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::ofstream;
using std::ios;
using std::getline;
using std::cin;
using std::cout;
using std::ifstream;

#include "Request.hpp"
#include "House.hpp"
#include "Rating.hpp"

class Member {
private:
    string username;
    string name;
    string password;
    string phoneNo;
public:
    //Will include House class for the user to add later 
    Member(string usernameVal = "", string nameVal = "", string passwordVal = "", string phoneNoVal = "");
    
    // All function will be pushed to System class
    void viewHouses();
    bool searchHouse();
    bool requestToRentAHouse();
    void acceptRequestForAHouse();
    bool occupyAHouse();
    bool rateAHouse();
    bool rateAnOwner();

    friend class System;
};

#endif