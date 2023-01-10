#ifndef MEMBER_CPP
#define MEMBER_CPP

#include "../include/Member.hpp"

Member::Member(string usernameVal, string nameVal, string passwordVal, string phoneNoVal, unsigned int IDVal) 
    : username(usernameVal), name(nameVal), password(passwordVal), phoneNo(phoneNoVal), ID(IDVal) {};

bool Member::registerHouse() {
    if (house != nullptr) {
        cout << "You have already listed a house!\n";
        return false;
    }

    string description = "", location = "", price = "";

    while (true) {
        string locationChoice;
        cout << "Choose the city of the house (type 1, 2 or 3): \n"
             << "1. Sai Gon\n"
             << "2. Hanoi\n"   
             << "3. Hue\n";
        
        do {
            getline(cin, locationChoice);
        } while (locationChoice == "");
        
        if (locationChoice == "1" || locationChoice == "2" || locationChoice == "3") {
            location = (locationChoice == "1") ? "Sai Gon" : (locationChoice == "2") ? "Hanoi" : "Hue";
            break;
        } else {
            cout << "Incorrect input, please try again.\n";
        }
    }
    
    while (true) {
        cout << "Enter description for the house (please don\'t include TABs in it): \n";
        do {
            getline(cin, description);
        } while (description == "");
        
        if (description.find('\t') != -1) {
            cout << "Incorrect input, please try again.\n";
            description = "";
        } else {
            break;
        }
    }
    
    Date startDate("Now enter the start date when your house is available.");
    Date endDate("Now enter the end date when your house is available.");

    while (true) {
        cout << "Enter daily price for the house (please use . as digit divider): \n";
        do {
            getline(cin, price);
        } while (price == "");
        
        if (price.find('.') == -1) {
            cout << "Incorrect input for the price value, please try again.";
            price = "";
        } else {
            break;
        }
    }

    House *housePtr = new House(this->ID, location, description, {startDate, endDate}, stod(price));
    if (housePtr != nullptr) {
        house = housePtr;
    } else {
        delete housePtr;
    }
}

House* Member::viewHouse() {
    return this->house;
}

void Member::viewSentRequestsInfo() {
    if (sentRequests.size() != 0) {
        for (int i = 0; i < sentRequests.size(); i++) {
            cout << "ID: " << i + 1 << '\n'
                 << "Location range: " << sentRequests[i]->requestDateRange.first.stringifyDate() << " to " << sentRequests[i]->requestDateRange.second.stringifyDate() << "\n\n";
            sentRequests[i]->house->viewHouseInfo();
        }
    } else {
        cout << "You have no sent requests.\n\n";
    }
}

void Member::viewAcceptedRequestsInfo() {
    if (acceptedRequests.size() != 0) {
        for (int i = 0; i < acceptedRequests.size(); i++) {
            cout << "ID: " << i + 1 << '\n'
                 << "Location range: " << acceptedRequests[i]->requestDateRange.first.stringifyDate() << " to " << acceptedRequests[i]->requestDateRange.second.stringifyDate() << "\n\n";
            acceptedRequests[i]->house->viewHouseInfo();
        }
    } else {
        cout << "You have no incoming requests.\n\n";
    }
}

bool Member::rateAHouse() {

}

bool Member::rateAnOwner() {

}

#endif