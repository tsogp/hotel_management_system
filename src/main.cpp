#include <iostream>
#include <vector>
#include <string>

#include "../include/Admin.hpp"
#include "../include/House.hpp"
#include "../include/Member.hpp"
#include "../include/System.hpp"

int main(int argc, char *argv[]) {
    std::cout << "EEET2482/COSC2082 ASSIGNMENT\n"  
         << "VACATION HOUSE EXCHANGE APPLICATION\n" 
         << "Instructors: Mr. Linh Tran & Phong Ngo\n\n"  
         << "Group: 17\n"
         << "s3777235, Hua Ha Bao Long\n"
         << "s3884998, Tran Nguyen Huynh Trung\n"
         << "s3938011, Vu Thien Minh Hao\n"
         << "s3963284, Potemkin Pavel\n\n";
        //  << "1. Guest\n"
        //  << "2. Member\n"   
        //  << "3. Admin\n"
        //  << "Use the app as:";

    System *sys = new (std::nothrow) System;

    if (sys != nullptr) {
        sys->reloadData();
        sys->reloadHouseData();
        
        sys->viewHouses();

        sys->loginUser();
        sys->viewHouses(sys->getLoggedMember());
        sys->handleOccupyHouseRequest(6, 8);
        sys->getLoggedMember()->viewSentRequestsInfo();

        sys->saveData();
        sys->saveHouseData();
    }

    delete sys;

    return 0;
}