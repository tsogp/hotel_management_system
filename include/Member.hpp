#ifndef MEMBER_HPP
#define MEMBER_HPP

#include "Request.hpp"
#include "House.hpp"
#include "Rating.hpp"

class Member {
private:
    int ID;
    string userType;
    string username;
    string name;
    string password;
    int phoneNo;
    //House listedHouse;
    //vector<Rating> occupierRating;
public:
    //Will include House class for the user to add later 
    Member(int idVal,string userTypeVal,string usernameVal,string nameVal
          ,string passwordVal,int phoneNoVal)
            :ID(idVal),userType(userTypeVal), username(usernameVal), name(nameVal),
            password(passwordVal), phoneNo(phoneNoVal){}
    friend class System;
public:
    Member();
    
    bool registerUser();
    void viewHouses();
    bool loginUser();
    bool searchHouse();
    bool requestToRentAHouse();
    void acceptRequestForAHouse();
    bool occupyAHouse();
    bool rateAHouse();
    bool rateAnOwner();
};

#endif