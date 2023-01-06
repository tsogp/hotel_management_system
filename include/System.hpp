#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <iostream>
#include <cstring>
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

#include "Member.hpp"

class System {
    private:
        vector<Member> members;
    public:
        System();

        int findMember(string username);
        bool saveData();
        bool registerMem();
        bool loginUser();
        bool reloadData();
};
#endif