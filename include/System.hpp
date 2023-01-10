#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

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
        Member *loggedMember = nullptr;
    public:
        System();

        int findMember(string username);
        bool registerMem();
        bool loginUser();

        vector<House> viewHouses(Member *loggedMember = nullptr);
        
        bool saveData();
        bool reloadData();
        bool saveHouseData();
        bool reloadHouseData();

        bool handleOccupyHouseRequest(unsigned int requesterMemberID, unsigned int accepterMemberID);
        bool handleAcceptHouseRequest(unsigned int index);
        void handleAccepterDeclinesHouseRequest(unsigned int index);
        void handleSenderDeclinesHouseRequest(unsigned int index);

        Member* getLoggedMember();
};
#endif