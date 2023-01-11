#ifndef SYSTEM_CPP
#define SYSTEM_CPP

#include "../include/System.hpp"
#include "../include/Member.hpp"

#define FILENAME "users.csv"
#define HOUSES_FILENAME "houses.csv"
#define REQUESTS_FILENAME "requests.csv"

unsigned int System::IDCounter = 1;

System::System() {
    reloadData();
    reloadHouseData();
    reloadRequestData();
    // reloadRatingData();
};

System::~System() {
    saveData();
    saveHouseData();
    saveRequestData();
    // saveRatingData();
};


int System::findMember(string username) {
    for (int i = 0; i < members.size(); i++) {
        if (members[i].username == username) {
            return i;
        }
    }
    return -1;
}

// Data saving function, only use when closing out of the program
bool System::saveData() {
    ofstream dataFile(FILENAME);
    if (!dataFile.is_open()) {
        return false;
    }

    for (Member &mem: members) {
        dataFile << mem.ID << '\t' << mem.username << "\t" << mem.password << "\t" 
                    << mem.name << "\t" << mem.phoneNo << "\n";
    }

    dataFile.close();
    return true;
}

// To Register Memeber
// 1) Try to find if the member username exist or not
// 2) Ask user to input password, phone no and name
// 3) Return false until everything is done
bool System::registerMem() {
    string username;
    cout << "Input your username: ";
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
        
        cout << "Enter your phone number (not empty): ";
        do {
            getline(cin, phoneNo);
        } while (phoneNo == "");
        
        Member newMember(username, name, password, phoneNo, IDCounter);
        members.push_back(newMember);
        loggedMember = &members.back();
        IDCounter++;

        cout << "Registration complete!\n";
        return true;
    }
    
}

// Login Function 
// 1) Find if the user name exist or not
// 2) IF found, check if username and password matches
// 3) Return true if done
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

// Load all data into their respected class, only to be use at the start of the program
bool System::reloadData()
{
    ifstream dataFile;
    dataFile.open(FILENAME);

    if (!dataFile.is_open()) {
        return false;
    }

    string username, password, name, phoneNo, ID;
    while (1) {
        getline(dataFile, ID, '\t');
        getline(dataFile, username, '\t');
        getline(dataFile, password, '\t');
        getline(dataFile, name, '\t');
        getline(dataFile, phoneNo);
        
        if (ID == "") {
            break;
        }
        
        members.push_back(Member(username, name, password, phoneNo, stoi(ID))); 
    }
    
    IDCounter = members.size() + 1;

    dataFile.close();
    return true;
}

bool System::saveHouseData() {
    ofstream dataFile;
    dataFile.open(HOUSES_FILENAME);

    if (!dataFile.is_open()) {
        return false;
    }

    for (Member &mem: members) {
        if (mem.house != nullptr) {
            dataFile << mem.ID << '\t' << mem.house->location << '\t' 
                     << mem.house->description << '\t' << mem.house->pricePerDay << '\t' 
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
               secondAvailableDateDay, secondAvailableDateMonth, secondAvailableDateYear;
        stringstream ss(currentLine);

        getline(ss, memberID, '\t');
        getline(ss, location, '\t');
        getline(ss, description, '\t');
        getline(ss, pricePerDay, '\t');

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

        House *memberHouse = new (std::nothrow) House(stoi(memberID), location, description, make_pair(startDate, endDate), stod(pricePerDay), unavailableDates);
        if (memberHouse != nullptr) {
            members[stoi(memberID) - 1].house = memberHouse;
        }
    }
    
    dataFile.close();
    return true;
}

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

        Request *reqPtr = new Request(stoi(requesterMemberID), stoi(accepterMemberID), make_pair(startDate, endDate), members[stoi(accepterMemberID) - 1].viewHouse());

        members[stoi(accepterMemberID) - 1].acceptedRequests.push_back(reqPtr);
        members[stoi(requesterMemberID) - 1].sentRequests.push_back(reqPtr);
        requests.push_back(reqPtr);
    }
    
    dataFile.close();
    return true;
}

vector<House> System::viewHouses(Member *loggedMember) {
    vector<House> houses;

    cout << "Here are the available houses:\n\n";

    if (loggedMember == nullptr) {
        cout << "You're viewing the houses in guest mode. No reviews or available dates are shown.\n\n";
        
        for (Member &mem: members) {
            if (mem.house != nullptr) {
                cout << "House ID: " << mem.house->memberID << '\n'
                     << "Owner name: " << mem.name << '\n'
                     << "Location: " << mem.house->location << '\n'
                     << "Description: " << mem.house->description << '\n'
                     << "Daily price: " << mem.house->pricePerDay << "\n\n";
            }
        }
    } else {
        for (Member &mem: members) {
            if (mem.house != nullptr) {
                houses.push_back(*(mem.house));
                cout << "House ID: " << mem.house->memberID << '\n'
                     << "Owner name: " << mem.name << '\n'
                     << "Location: " << mem.house->location << '\n'
                     << "Description: " << mem.house->description << '\n'
                     << "Daily price: " << mem.house->pricePerDay << '\n'
                     << "Availbale dates:\n";
                mem.house->getAvailableDates();
                cout << "\n\n";
            }
        }
    }

    return houses;
}

bool System::handleOccupyHouseRequest(unsigned int requesterMemberID, unsigned int accepterMemberID) {
    Date startDate("Please provide the start date from when you want to book the house.");
    Date endDate("Please provide the end date from when you want to book the house.");

    House *house = members[accepterMemberID - 1].viewHouse();
    house->isAvailable(make_pair(startDate, endDate));

    unsigned int dayAmount = members[accepterMemberID - 1].viewHouse()->isAvailable(make_pair(startDate, endDate));
    if (dayAmount && members[requesterMemberID - 1].balance >= dayAmount * members[accepterMemberID - 1].viewHouse()->pricePerDay) {
        Request *reqPtr = new Request(requesterMemberID, accepterMemberID, make_pair(startDate, endDate), members[accepterMemberID - 1].viewHouse());

        members[accepterMemberID - 1].acceptedRequests.push_back(reqPtr);
        members[requesterMemberID - 1].sentRequests.push_back(reqPtr);
        requests.push_back(reqPtr);

        members[requesterMemberID - 1].balance -= dayAmount * members[accepterMemberID - 1].viewHouse()->pricePerDay;

        cout << "Request has been created successfully.\n";
        return true;
    } 
    
    cout << "Sorry, these dates are unavailable or you don't have enough balance. Please try booking again.\n";
    return false;
}

bool System::handleAcceptHouseRequest(unsigned int index) {
    if (index < loggedMember->acceptedRequests.size()) {
        Request *requestToBeAccepted = loggedMember->acceptedRequests[index];
        
        unsigned int dayVal = loggedMember->viewHouse()->isAvailable(requestToBeAccepted->requestDateRange);
        if (dayVal) {
            requestToBeAccepted->isAccepted = true;
            loggedMember->viewHouse()->makeUnavailable(requestToBeAccepted->requestDateRange);
            loggedMember->balance += dayVal * loggedMember->viewHouse()->pricePerDay;
            cout << "You have successfully accepted the request.\n";
            return true;
        } else {
            cout << "You have already chosen another customer for this dates. Cancelling request.\n";
            requestToBeAccepted->isActive = false;
        }
    } else {
        cout << "Invalid request index.\n";
    }

    return false;
}

void System::handleAccepterDeclinesHouseRequest(unsigned int index) {
    if (index < loggedMember->acceptedRequests.size()) {
        Request *requestToBeAccepted = loggedMember->acceptedRequests[index];
        requestToBeAccepted->isActive = false;

        cout << "Request declined successfully.\n";
    } else {
        cout << "Invalid request index.\n";
    }
}

void System::handleSenderDeclinesHouseRequest(unsigned int index) {
    if (index < loggedMember->acceptedRequests.size()) {
        Request *requestToBeAccepted = loggedMember->sentRequests[index];
        requestToBeAccepted->isActive = false;

        cout << "Request declined successfully.\n";
    } else {
        cout << "Invalid request index.\n";
    }
}

Member* System::getLoggedMember() {
    return this->loggedMember;
}

#endif
