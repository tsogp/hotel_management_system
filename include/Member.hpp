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
using std::stod;

#include "Request.hpp"
#include "House.hpp"
#include "Rating.hpp"

class Member {
private:
    unsigned int ID;
    string username;
    string name;
    string password;
    string phoneNo;
    House *house = nullptr;
    vector<Request*> sentRequests;
    vector<Request*> acceptedRequests;
public:
    // Will include House class for the user to add later 
    Member(string usernameVal = "", string nameVal = "", string passwordVal = "", string phoneNoVal = "", unsigned int IDVal = 0);
    
    bool registerHouse();
    House* viewHouse();
    void deleteHouse();

    void viewSentRequestsInfo();
    void viewAcceptedRequestsInfo();

    bool rateAHouse();
    bool rateAnOwner();

    friend class System;
    friend class Request;
};

#endif