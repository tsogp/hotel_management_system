#ifndef SYSTEM_CPP
#define SYSTEM_CPP

#include "../include/System.hpp"
#include "../include/Member.hpp"

#define FILENAME "users.csv"
#define HOUSES_FILENAME "houses.csv"
#define REQUESTS_FILENAME "requests.csv"
#define RATINGS_FILENAME "ratings.csv"

unsigned int System::IDCounter = 1;

// System constructor
System::System() {
    reloadData();
    reloadHouseData();
    reloadRequestData();
    reloadRatingData();

    for (Member &member: members) {
        if (member.ratings.size() > 0) {
            member.calculateRating();
        }

        if (member.viewHouse() != nullptr && member.viewHouse()->ratings.size() > 0) {
            member.viewHouse()->calculateRating();
        }
    }
};

// System destructor
System::~System() {
    saveRatingData();
    saveData();
    saveHouseData();
    saveRequestData();
};

// Function to find member by their name
int System::findMember(string username) {
    for (int i = 0; i < members.size(); i++) {
        if (members[i].username == username) {
            return i;
        }
    }
    return -1;
}

// Function to register member
bool System::registerMem() {
    string username;
    cout << "Input your username (not empty): ";
    do {
        getline(cin, username);
    } while (username == "");

    int position = findMember(username);
    if (position >= 0) {
        cout << "Username is already taken. Please try again.\n";
        return false;
    } else {
        string password, name, phoneNo;

        cout << "Input your password (not empty): ";
        do {
            getline(cin, password);
        } while (password == "");

        cout << "Enter your name (not empty): ";
        do {
            getline(cin, name);
        } while (name == "");
        
        do {
            while (true) {
                cout << "Enter your phone number (not empty and only numeric): ";
                getline(cin, phoneNo);
                if (!Date::isStringNumeric(phoneNo)) {
                    cout << "The number value must only be numeric. Try again.\n";
                } else {
                    break;
                }
            }
        } while (phoneNo == "");
        
        Member newMember(username, name, password, phoneNo, IDCounter);
        members.push_back(newMember);
        IDCounter++;

        cout << "\nRegistration complete!\nPlease exit the guest menu to log in to your account or restart the program if you're already logged in.\n";
        return true;
    }
    
}

// Function to login user
bool System::loginUser() {
    string username, password; 
    int position;
    
    cout << "Please enter your username: ";
    do {
        getline(cin, username);
    } while (username == "");

    position = findMember(username);

    if (position < 0) {
        cout << "Username not found, please register that username!\n";
        return false;
    }

    cout << "Please enter your password: ";
    do {
        getline(cin, password);
    } while (password == "");

    if (password == members[position].password) {
        loggedMember = &members[position];
        cout << "Welcome back " << members[position].username << "\n";
        return true;
    } else {
        loggedMember = nullptr;
        cout << "Username or Password did not match. Please try again.\n";
        return false;
    }
}

// Function to login admin
bool System::loginAdmin() {
    string username, password; 
    int position;
    
    cout << "Please enter your username: ";
    do {
        getline(cin, username);
    } while (username == "");

    if (username != "admin") {
        cout << "Wrong admin username!\n";
        return false;
    }

    cout << "Please enter your password: ";
    do {
        getline(cin, password);
    } while (password == "");

    if (password == admin.password) {
        cout << "Welcome back, " << admin.username << "\n";
        return true;
    } else {
        cout << "Username or Password did not match. Please try again.\n";
        return false;
    }
}

// Function to save the data about the user
bool System::saveData() {
    ofstream dataFile(FILENAME);
    if (!dataFile.is_open()) {
        return false;
    }

    for (Member &mem: members) {
        dataFile << mem.ID << '\t' << mem.username << "\t" << mem.password << "\t" 
                    << mem.name << "\t" << mem.balance << "\t" << mem.phoneNo << "\n";
    }

    dataFile.close();
    return true;
}

// Functino to reload user data to the runtime
bool System::reloadData()
{
    ifstream dataFile;
    dataFile.open(FILENAME);

    if (!dataFile.is_open()) {
        return false;
    }

    string username, password, name, phoneNo, balance, ID;
    while (1) {
        getline(dataFile, ID, '\t');
        getline(dataFile, username, '\t');
        getline(dataFile, password, '\t');
        getline(dataFile, name, '\t');
        getline(dataFile, balance, '\t');
        getline(dataFile, phoneNo);
        
        if (ID == "") {
            break;
        }
        
        members.push_back(Member(username, name, password, phoneNo, stoi(ID), stod(balance))); 
    }
    
    IDCounter = members.size() + 1;

    dataFile.close();
    return true;
}

// Function to save house data
bool System::saveHouseData() {
    ofstream dataFile;
    dataFile.open(HOUSES_FILENAME);

    if (!dataFile.is_open()) {
        return false;
    }

    for (Member &mem: members) {
        if (mem.house != nullptr) {
            dataFile << mem.ID << '\t' << mem.house->location << '\t' 
                     << mem.house->description << '\t' << mem.house->pricePerDay << '\t' << mem.house->minRequiredRating << '\t'
                     << mem.house->availableDateRange.first.stringifyDate(true) << '\t'
                     << mem.house->availableDateRange.second.stringifyDate(true) << '\t';

            for (Date &date: mem.house->unavailableDates) {
                dataFile << date.stringifyDate(true) << '\t';
            }

            dataFile << '\n';

            delete mem.house;
        }
    }

    dataFile.close();
    return true;
}

// Function to reload house data to the runtime
bool System::reloadHouseData() {
    ifstream dataFile;
    dataFile.open(HOUSES_FILENAME);
    
    if (!dataFile.is_open()) {
        return false;
    }

    string currentLine;
    getline(dataFile, currentLine);

    while (currentLine != "") {
        string memberID, location, description, pricePerDay,
               firstAvailableDateDay, firstAvailableDateMonth, firstAvailableDateYear,
               secondAvailableDateDay, secondAvailableDateMonth, secondAvailableDateYear, minRequiredRating;
        stringstream ss(currentLine);

        getline(ss, memberID, '\t');
        getline(ss, location, '\t');
        getline(ss, description, '\t');
        getline(ss, pricePerDay, '\t');
        getline(ss, minRequiredRating, '\t');

        getline(ss, firstAvailableDateDay, '\t');
        getline(ss, firstAvailableDateMonth, '\t');
        getline(ss, firstAvailableDateYear, '\t');
        getline(ss, secondAvailableDateDay, '\t');
        getline(ss, secondAvailableDateMonth, '\t');
        getline(ss, secondAvailableDateYear, '\t');
        
        Date startDate(stoi(firstAvailableDateDay), stoi(firstAvailableDateMonth), stoi(firstAvailableDateYear));
        Date endDate(stoi(secondAvailableDateDay), stoi(secondAvailableDateMonth), stoi(secondAvailableDateYear));
        
        vector<Date> unavailableDates;
        while (!ss.eof()) {
            string day, month, year;
            
            getline(ss, day, '\t');
            getline(ss, month, '\t');
            getline(ss, year, '\t');

            if (day.length() != 0 && month.length() != 0 && year.length() != 0) {
                unavailableDates.push_back(Date(stoi(day), stoi(month), stoi(year)));
            }
        }

        getline(dataFile, currentLine);

        House *memberHouse = new (std::nothrow) House(stoi(memberID), location, description, make_pair(startDate, endDate), stod(pricePerDay), stod(minRequiredRating), unavailableDates);
        if (memberHouse != nullptr) {
            members[stoi(memberID) - 1].house = memberHouse;
            
            for (Member &member: members) {
                if (member.ID != stoi(memberID) && stod(minRequiredRating) <= member.rating && stod(pricePerDay) <= member.balance)  {
                    member.availableHousesToOccupy.push_back(stoi(memberID) - 1);
                }
            }
        }
    }
    
    dataFile.close();
    return true;
}

// Function to save the request data
bool System::saveRequestData() {
    ofstream dataFile;
    dataFile.open(REQUESTS_FILENAME);

    if (!dataFile.is_open()) {
        return false;
    }

    for (Request* request: requests) {
        if (request->isActive) {
                dataFile << request->requesterMemberID << '\t' << request->accepterMemberID << '\t' 
                << request->isAccepted << '\t' << request->isActive << '\t' 
                << request->requestDateRange.first.stringifyDate(true) << '\t'
                << request->requestDateRange.second.stringifyDate(true) << '\n';
        }

        delete request;
    }

    dataFile.close();
    return true;
}

// Function to reload request data to the runtime
bool System::reloadRequestData() {
    ifstream dataFile;
    dataFile.open(REQUESTS_FILENAME);
    
    if (!dataFile.is_open()) {
        return false;
    }

    string currentLine;
    getline(dataFile, currentLine);

    while (currentLine != "") {
        string requesterMemberID, accepterMemberID, isAccepted, isActive,
               firstDateDay, firstMonth, firstYear,
               secondDay, secondMonth, secondYear;
        stringstream ss(currentLine);

        getline(ss, requesterMemberID, '\t');
        getline(ss, accepterMemberID, '\t');
        getline(ss, isAccepted, '\t');
        getline(ss, isActive, '\t');

        getline(ss, firstDateDay, '\t');
        getline(ss, firstMonth, '\t');
        getline(ss, firstYear, '\t');
        getline(ss, secondDay, '\t');
        getline(ss, secondMonth, '\t');
        getline(ss, secondYear, '\t');
        
        Date startDate(stoi(firstDateDay), stoi(firstMonth), stoi(firstYear));
        Date endDate(stoi(secondDay), stoi(secondMonth), stoi(secondYear));
        
        getline(dataFile, currentLine);

        Request *reqPtr = new Request(stoi(requesterMemberID), stoi(accepterMemberID), make_pair(startDate, endDate), members[stoi(accepterMemberID) - 1].viewHouse(), stoi(isAccepted), stoi(isActive));

        members[stoi(accepterMemberID) - 1].acceptedRequests.push_back(reqPtr);
        members[stoi(requesterMemberID) - 1].sentRequests.push_back(reqPtr);
        requests.push_back(reqPtr);

        if (stoi(isAccepted)) {
            members[stoi(accepterMemberID) - 1].availableUsersToRate.push_back(stoi(requesterMemberID) - 1);
            
            members[stoi(requesterMemberID) - 1].availableUsersToRate.push_back(stoi(accepterMemberID) - 1);
            members[stoi(requesterMemberID) - 1].availableHousesToRate.push_back(stoi(accepterMemberID) - 1);
        }
    }
    
    dataFile.close();
    return true;
}

// Function to reload rating data to the runtime
bool System::reloadRatingData() {
    ifstream dataFile;
    dataFile.open(RATINGS_FILENAME);
    
    if (!dataFile.is_open()) {
        return false;
    }

    string currentLine;
    getline(dataFile, currentLine);

    while (currentLine != "") {
        string ID, message, raterName, rating, ratingForHouse;
        stringstream ss(currentLine);

        getline(ss, ID, '\t');
        getline(ss, raterName, '\t');
        getline(ss, message, '\t');
        getline(ss, rating, '\t');
        getline(ss, ratingForHouse, '\t');
        
        getline(dataFile, currentLine);
        
        if (stoi(ratingForHouse)) {
            members[stoi(ID) - 1].viewHouse()->ratings.push_back(Rating(stoi(ID), raterName, message, stoi(rating)));
        } else {
            members[stoi(ID) - 1].ratings.push_back(Rating(stoi(ID), raterName, message, stoi(rating), false));
        }
    }
    
    dataFile.close();
    return true;
}

// Function to save the rating data
bool System::saveRatingData() {
    ofstream dataFile;
    dataFile.open(RATINGS_FILENAME);

    if (!dataFile.is_open()) {
        return false;
    }

    for (Member &member: members) {
        for (Rating &rating: member.ratings) {
            dataFile << rating.ID << '\t' << rating.raterName << '\t' 
                     << rating.message << '\t' << rating.rating << '\t' 
                     << rating.ratingForHouse << '\n';
        }

        if (member.viewHouse() != nullptr) {
            for (Rating &rating: member.viewHouse()->ratings) {
                dataFile << rating.ID << '\t' << rating.raterName << '\t' 
                            << rating.message << '\t' << rating.rating << '\t' 
                            << rating.ratingForHouse << '\n';
            }
        }
    }

    dataFile.close();
    return true;
}

// Function to view users
void System::viewUsers() {
    for (Member &member: members) {
        cout << "Username: " << member.username << '\n'
             << "Name: " << member.name << '\n'
             << "Password: " << member.password << '\n'
             << "Phone Number: " << member.phoneNo << "\n"
             << "Balance: " << member.balance << '\n'
             << "Rating: " << member.rating << "\n\n";
        if (member.ratings.size() > 0) {
            cout << "Member ratings: \n";
            for (Rating &rating: member.ratings) {
                rating.viewRatingInfo();
            }
        }
    }
}

// Function to view all the houses info
void System::viewHouses(Member *loggedMember, bool isAdmin) {
    cout << "Here are the available houses:\n\n";
    bool isEmpty = true;

    if (loggedMember == nullptr && !isAdmin) {
        cout << "You're viewing the houses in guest mode. No reviews or available dates are shown.\n\n";
        
        for (Member &mem: members) {
            if (mem.house != nullptr) {
                isEmpty = false;
                cout << "House ID: " << mem.house->memberID << '\n'
                     << "Owner name: " << mem.name << '\n'
                     << "Location: " << mem.house->location << '\n'
                     << "Description: " << mem.house->description << '\n'
                     << "Daily price: " << mem.house->pricePerDay << "\n";
            }
        }
    } else {
        string ifWantsLocation;
        cout << "Would you like to choose a particular location for the house (type yes for yes, anything else for for no): ";
        
        do {
            getline (cin, ifWantsLocation);
        } while (ifWantsLocation == "");

        string locationChoice, location;

        if (ifWantsLocation == "yes") {
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
        }

        for (Member &mem: members) {
            if (mem.house != nullptr && (isAdmin || (mem.house->memberID != loggedMember->ID && mem.house->minRequiredRating <= loggedMember->rating && mem.house->pricePerDay <= loggedMember->balance))) {
                if (ifWantsLocation == "yes") {
                    if (mem.house->location == location) {
                        isEmpty = false;
                        cout << "House ID: " << mem.house->memberID << '\n'
                             << "Owner name: " << mem.name << '\n';
                        mem.house->viewHouseInfo(); 
                    }
                } else {
                    isEmpty = false;
                    cout << "House ID: " << mem.house->memberID << '\n'
                         << "Owner name: " << mem.name << '\n';
                    mem.house->viewHouseInfo();   
                }
            }
        }
    }

    if (isEmpty) {
        cout << "Sorry, there're currently no suitable houses for you. Try again later.\n";
    }
}

// Function to make a house rent request
bool System::handleOccupyHouseRequest(unsigned int requesterMemberID, unsigned int accepterMemberID) {
    vector<unsigned int>::iterator ifRequesterCanOccupy = find(members[requesterMemberID - 1].availableHousesToOccupy.begin(), members[requesterMemberID - 1].availableHousesToOccupy.end(), accepterMemberID - 1);
    if (ifRequesterCanOccupy == members[requesterMemberID - 1].availableHousesToOccupy.end()) {
        cout << "You can't send request for this house.\n";
        return false;
    }

    House *house = members[accepterMemberID - 1].viewHouse();

    Date startDate("Please provide the start date from when you want to book the house.");
    
    if (house->availableDateRange.first > startDate) {
        cout << "The first date can't be earlier that the house's available range.\n";
        return false;
    } else if (startDate > house->availableDateRange.second) {
        cout << "The first date can't be later that the house's available range.\n";
        return false;
    }
    
    Date endDate("Please provide the end date from when you want to book the house.");

    if (startDate > endDate) {
        cout << "The first date can't be later than the second date.\n";
        return false;
    } else if (endDate > house->availableDateRange.second) {
        cout << "The second date can't be later than the house's available range.\n";
        return false;
    } 

    unsigned int dayAmount = house->isAvailable(make_pair(startDate, endDate));;
    if (dayAmount) {
        Request *reqPtr = new Request(requesterMemberID, accepterMemberID, make_pair(startDate, endDate), house);

        members[accepterMemberID - 1].acceptedRequests.push_back(reqPtr);
        members[requesterMemberID - 1].sentRequests.push_back(reqPtr);
        requests.push_back(reqPtr);

        cout << "Request has been created successfully.\n";
        return true;
    } 
    
    cout << "Sorry, these dates are unavailable or you don't have enough balance. Please try booking again.\n";
    return false;
}

// Function to accept house rent request
bool System::handleAcceptHouseRequest(unsigned int index) {
    if (index < loggedMember->acceptedRequests.size() && !loggedMember->acceptedRequests[index]->isAccepted) {
        Request *requestToBeAccepted = loggedMember->acceptedRequests[index];
        
        unsigned int dayVal = loggedMember->viewHouse()->isAvailable(requestToBeAccepted->requestDateRange);
        if (dayVal) {
            requestToBeAccepted->isAccepted = true;
            loggedMember->viewHouse()->makeUnavailable(requestToBeAccepted->requestDateRange);

            loggedMember->balance += dayVal * loggedMember->viewHouse()->pricePerDay;
            members[requestToBeAccepted->requesterMemberID - 1].balance -= dayVal * loggedMember->viewHouse()->pricePerDay;

            cout << "You have successfully accepted the request.\n";
            return true;
        } else {
            cout << "You have already chosen another customer for this dates. Cancelling request.\n";
            requestToBeAccepted->isActive = false;
        }
    } else if (loggedMember->acceptedRequests[index]->isAccepted) {
        cout << "You have already accepted this request.\n";
        return true;
    } else {
        cout << "Invalid request index.\n";
    }

    return false;
}

// Function to decline house rent request
void System::handleAccepterDeclinesHouseRequest(unsigned int index) {
    if (index < loggedMember->acceptedRequests.size() && loggedMember->acceptedRequests[index]->isActive) {
        Request *requestToBeAccepted = loggedMember->acceptedRequests[index];
        if (requestToBeAccepted->isAccepted) {
            cout << "\nThis request is already accepted, can't cancel it.\n\n";
            return;
        }
        requestToBeAccepted->isActive = false;
        cout << "Request declined successfully.\n";
    } else {
        cout << "Invalid request index.\n";
    }
}

// Function to decline your rent request
void System::handleSenderDeclinesHouseRequest(unsigned int index) {
    if (index < loggedMember->sentRequests.size() && loggedMember->sentRequests[index]->isActive) {
        Request *requestToBeAccepted = loggedMember->sentRequests[index];
        if (requestToBeAccepted->isAccepted) {
            cout << "\nThis request is already accepted, can't cancel it.\n\n";
            return;
        }
        requestToBeAccepted->isActive = false;

        cout << "Request declined successfully.\n";
    } else {
        cout << "Invalid request index.\n";
    }
}

// Function to rate the user
bool System::handleRateUser() {
    string IDVal, message, rating;

    do {
        cout << "You can rate the users that have approved you or have been approved by you. \nYou can check those in the requests tab. Type the ID of the house to rate it's owner: ";
        cin.ignore();
        getline(cin, IDVal);
    } while (IDVal == "");

    vector<unsigned int>::iterator ifRequesterCanRate = find(members[loggedMember->ID - 1].availableUsersToRate.begin(), members[loggedMember->ID - 1].availableUsersToRate.end(), stoi(IDVal) - 1);
    if (!(Date::isStringNumeric(IDVal) && ifRequesterCanRate != members[loggedMember->ID - 1].availableUsersToRate.end())) {
        cout << "Incorrect ID value, please try again. You can only rate users that have approved your housing request or have been approved by you.\n";
        return false;
    } 

    do {
        cout << "Type rating message: ";
        getline(cin, message);
    } while (message == "");

    do {
        cout << "Type rating value: ";
        getline(cin, rating);
    } while (rating == "");

    if (!(Date::isStringNumeric(rating) && stoi(rating) >= -10 && stoi(rating) <= 10)) {
        cout << "Incorrect rating value, please choose an integer from -10 to 10.\n";
        return false;
    } 
    
    string name = loggedMember->name;

    members[stoi(IDVal) - 1].ratings.push_back(Rating(stoi(IDVal), name, message, stoi(rating), false));
    members[stoi(IDVal) - 1].calculateRating();
    return true;
}

// Function to rate the houses
bool System::handleRateHouse() {
    string IDVal, message, rating;

    do {
        cout << "You can rate the houses that have been approved for you. You can check those in the requests tab. Type the house ID to rate it: ";
        cin.ignore();
        getline(cin, IDVal);
    } while (IDVal == "");

    vector<unsigned int>::iterator ifRequesterCanRate = find(members[loggedMember->ID - 1].availableHousesToRate.begin(), members[loggedMember->ID - 1].availableHousesToRate.end(), stoi(IDVal) - 1);
    if (!(Date::isStringNumeric(IDVal) && ifRequesterCanRate != members[loggedMember->ID - 1].availableHousesToRate.end())) {
        cout << "Incorrect ID value, please try again. You can only rate houses that have been approved for you to use.\n";
        return false;
    } 

    do {
        cout << "Type rating message: ";
        getline(cin, message);
    } while (message == "");

    do {
        cout << "Type rating value: ";
        getline(cin, rating);
    } while (rating == "");

    if (!(Date::isStringNumeric(rating) && stoi(rating) >= -10 && stoi(rating) <= 10)) {
        cout << "Incorrect rating value, please choose an integer from -10 to 10.\n";
        return false;
    } 
    
    string name = loggedMember->name;

    members[stoi(IDVal) - 1].viewHouse()->ratings.push_back(Rating(stoi(IDVal), name, message, stoi(rating), true));
    members[stoi(IDVal) - 1].viewHouse()->calculateRating();
    return true;
}

// Function to get logged member pointer
Member* System::getLoggedMember() {
    return this->loggedMember;
}

#endif
