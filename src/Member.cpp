#ifndef MEMBER_CPP
#define MEMBER_CPP

#include "../include/Member.hpp"

void handleDoubleInput(double &value, string error_msg = "Please enter a double number and use . as a divider: ") {
    cin >> value;
    while (cin.fail()) {
        cout << error_msg;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> value;
    }
}

Member::Member(string usernameVal, string nameVal, string passwordVal, string phoneNoVal, unsigned int IDVal, int balanceVal) 
    : username(usernameVal), name(nameVal), password(passwordVal), phoneNo(phoneNoVal), ID(IDVal), balance(balanceVal) {};

unsigned int Member::getID() {
    return ID;
}

void Member::viewProfile() {
    cout << "Username: " << username << '\n'
         << "Name: " << name << '\n'
         << "Password: " << password << '\n'
         << "Phone Number: " << phoneNo << "\n"
         << "Balance: " << balance << '\n'
         << "Rating: " << rating << "\n\n";
    if (ratings.size() > 0) {
        cout << "House ratings: \n";
        for (Rating &rating: ratings) {
            rating.viewRatingInfo();
        }
    }

    if (viewHouse() != nullptr) {
        cout << "House info: \n";
        viewHouse()->viewHouseInfo();
    }
}

bool Member::registerHouse() {
    if (house != nullptr) {
        cout << "You have already listed a house!\n";
        return false;
    }

    cout << "House can be available from 1/1/2023 to 31/12/2030\n\n";

    string description = "", location = "";
    double price, minimalRequiredRating;

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

    if (startDate > endDate) {
        cout << "The first date can't be later than the second date.\n";
        return false;
    }

    cout << "Enter daily price for the house (please use . as digit divider): ";
    handleDoubleInput(price);

    cout << "Enter minimum required rating for the guest (please use . as digit divider): ";
    handleDoubleInput(minimalRequiredRating);

    House *housePtr = new House(this->ID, location, description, {startDate, endDate}, price, minimalRequiredRating);
    if (housePtr != nullptr) {
        house = housePtr;
    } else {
        delete housePtr;
    }

    return true;
}

House* Member::viewHouse() {
    return this->house;
}

void Member::deleteHouse() {
    for (Request *request: acceptedRequests) {
        if (request->isAccepted) {
            cout << "You already have an accepted request for this house. Cannon unlist it.\n\n";            
            return;
        }
    }

    delete house;
    this->house = nullptr;
    cout << "House unlisted successfully.\n";
}

bool Member::viewSentRequestsInfo() {
    if (sentRequests.size() != 0) {
        for (int i = 0; i < sentRequests.size(); i++) {
            cout << "ID: " << i + 1 << '\n'
                 << "Location range: " << sentRequests[i]->requestDateRange.first.stringifyDate() << " to " << sentRequests[i]->requestDateRange.second.stringifyDate() << "\n\n";
            cout << "Location: " << sentRequests[i]->house->location << '\n'
                 << "Description: " << sentRequests[i]->house->description << '\n'
                 << "Daily price: " << sentRequests[i]->house->pricePerDay << '\n'
                 << "House and Owner ID: " << acceptedRequests[i]->house->memberID << '\n'
                 << "Is accepted: " << sentRequests[i]->isAccepted << "\n\n";
        }
    } else {
        cout << "You have no sent requests.\n\n";
        return false;
    }

    return true;
}

bool Member::viewAcceptedRequestsInfo() {
    if (acceptedRequests.size() != 0) {
        for (int i = 0; i < acceptedRequests.size(); i++) {
            cout << "ID: " << i + 1 << '\n'
                 << "Location range: " << acceptedRequests[i]->requestDateRange.first.stringifyDate() << " to " << acceptedRequests[i]->requestDateRange.second.stringifyDate() << "\n\n";
            cout << "Location: " << acceptedRequests[i]->house->location << '\n'
                 << "Description: " << acceptedRequests[i]->house->description << '\n'
                 << "Daily price: " << acceptedRequests[i]->house->pricePerDay << '\n'
                 << "House and Owner ID: " << acceptedRequests[i]->house->memberID << '\n'
                 << "Is accepted: " << acceptedRequests[i]->isAccepted << "\n\n";
        }
    } else {
        cout << "You have no incoming requests.\n\n";
        return false;
    }

    return true;
}

void Member::calculateRating() {
    double averageRating = 0.0;
    for (Rating &rating: ratings) {
        averageRating += rating.rating;
    }

    rating = averageRating / ratings.size();
}

#endif