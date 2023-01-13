#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::find;
using std::string;
using std::vector;
using std::ofstream;
using std::ios;
using std::getline;
using std::cin;
using std::cout;
using std::ifstream;
using std::stringstream;
using std::stoi;
using std::make_pair;

#include "Member.hpp"
#include "Date.hpp"

class System {
    private:
        static unsigned int IDCounter;

        vector<Member> members;
        vector<Request*> requests;
        Member *loggedMember = nullptr;
        Member admin = Member("admin", "admin", "admin", "012345");
    public:
        System();
        ~System();

        int findMember(string username);
        bool registerMem();
        bool loginUser();
        bool loginAdmin();
       
        bool saveData();
        bool reloadData();
        bool saveHouseData();
        bool reloadHouseData();
        bool saveRequestData();
        bool reloadRequestData();
        bool saveRatingData();
        bool reloadRatingData();

        void viewUsers();
        void viewHouses(Member *loggedMember = nullptr, bool isAdmin = false);
 
        bool handleOccupyHouseRequest(unsigned int requesterMemberID, unsigned int accepterMemberID);
        bool handleAcceptHouseRequest(unsigned int index);
        void handleAccepterDeclinesHouseRequest(unsigned int index);
        void handleSenderDeclinesHouseRequest(unsigned int index);

        bool handleRateUser();
        bool handleRateHouse();

        Member* getLoggedMember();
};
#endif