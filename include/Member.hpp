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
    int balance;
    double rating = 0.0;
    string username;
    string name;
    string password;
    string phoneNo;
    House *house = nullptr;
    vector<Request*> sentRequests;
    vector<Request*> acceptedRequests;
    vector<Rating> ratings;
    vector<unsigned int> availableUsersToRate;
    vector<unsigned int> availableHousesToRate;
    vector<unsigned int> availableHousesToOccupy;
public:
    // Will include House class for the user to add later 
    Member(string usernameVal = "", string nameVal = "", string passwordVal = "", string phoneNoVal = "", unsigned int IDVal = 0, int balanceVal = 500);
    
    unsigned int getID();

    void viewProfile();

    bool registerHouse();
    House* viewHouse();
    void deleteHouse();

    bool viewSentRequestsInfo();
    bool viewAcceptedRequestsInfo();

    void calculateRating();

    friend class System;
    friend class Request;
};

#endif