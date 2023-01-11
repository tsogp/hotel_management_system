#include <iostream>
#include <string>

using std::cout;
using std::cin;

#include "include/Admin.hpp"
#include "include/House.hpp"
#include "include/Member.hpp"
#include "include/System.hpp"

int main(int argc, char *argv[]) 
{
    cout << "EEET2482/COSC2082 ASSIGNMENT\n"  
         << "VACATION HOUSE EXCHANGE APPLICATION\n" 
         << "Instructors: Mr. Linh Tran & Phong Ngo\n\n"  
         << "Group: 17\n"
         << "s3777235, Hua Ha Bao Long\n"
         << "s3884998, Tran Nguyen Huynh Trung\n"
         << "s3938011, Vu Thien Minh Hao\n"
         << "s3963284, Potemkin Pavel\n\n";

    int choice;

    bool exit = false;
    bool exitGuest = false;
    bool exitMember = false;
    bool exitAdmin = false;
    bool loopGuest = false;
    bool loopMember = false;
    bool loopAdmin = false;

    std::string username;

    System *sys = new System();

    if (sys != nullptr) {
        sys->reloadData();
        sys->reloadHouseData();

        while (!exit) {
            cout << "---------------------------------------\n"
                 << "Menu:" << "\n"
                 << "1. Guest" << "\n"
                 << "2. Member" << "\n"
                 << "3. Admin" << "\n"
                 << "0. Exit" << "\n"
                 << "-> Please enter your choice: ";

            cin >> choice;

            switch (choice) {
                case 1:
                    while (!exitGuest) {
                        cout << "\n---------------------------------------\n\n"
                             << "1) View Houses\n"
                             << "2) Register as Member\n"
                             << "0) Exit\n"
                             << "-> Please enter your choice: ";

                        cin >> choice;

                        switch (choice) {
                            case 1:
                                break;
                            case 2:
                                while (!loopGuest) {
                                    loopGuest = sys->registerMem();
                                }
                                break;
                            case 0:
                                exitGuest = true;

                                break;
                            default:
                                cout << "Invalid choice." << "\n";

                                break;
                        }                  
                    }          
                    break;
                case 2:
                    while (!loopMember) {
                        sys->loginUser();    

                        if (sys->getLoggedMember() != nullptr) {
                            while (!exitMember) {
                                cout << "\n---------------------------------------\n\n"
                                     << "1) View Profile\n"
                                     << "2) Register House\n"
                                     << "3) Delete House\n"
                                     << "4) Search House\n"
                                     << "5) Rent House\n"
                                     << "6) Rate House\n"
                                     << "7) Rate Occupier\n"
                                     << "8) View Rent Request\n"
                                     << "9) View Your Rent Requests\n"
                                     << "0) Exit\n"
                                     << "-> Please enter your choice: ";

                                cin >> choice;

                                switch (choice) {
                                    case 1:
                                        break;

                                    case 2:
                                        sys->getLoggedMember()->registerHouse();
                                        break;
                                    case 3:

                                        break;
                                    case 4:
                                        sys->viewHouses(sys->getLoggedMember());
                                        break;  
                                    case 5:


                                        break;

                                    case 6:


                                        break;

                                    case 7:


                                        break;

                                    case 8:
                                        sys->getLoggedMember()->viewAcceptedRequestsInfo();
                                        break;                          
                                    case 9:
                                        sys->getLoggedMember()->viewSentRequestsInfo();
                                        break;
                                    case 0:
                                        exitMember = true;

                                    default:
                                        cout << "Invalid choice." << "\n";

                                        break;
                                }  
                            }
                        } else {    
                            loopMember = true;
                        }
                    }
                case 3:
                    while (!loopAdmin) {
                        if (sys->getLoggedMember() != nullptr) { //Please Change this to check for Admin Login) 
                            while(!exitAdmin) {
                                cout << "\n---------------------------------------\n\n"
                                     << "1) View House Listing\n"
                                     << "2) View User Profile\n"
                                     << "0) Exit\n"
                                     << "-> Please enter your choice: ";

                                cin >> choice;

                                switch (choice) {
                                    case 1:


                                        break;

                                    case 2:


                                        break;

                                    case 0:
                                        exitAdmin = true;

                                    default:
                                        cout << "Invalid choice." << "\n";

                                        break;
                                }  
                            }
                        } else {
                            cout << "Username or Password did not match. Please try again.";
                            loopAdmin = true;
                        }
                    }
                    break;

                case 0:
                    exit = true;

                    break;

                default:
                    cout << "Invalid choice." << "\n";

                    break;
            }
        }
    }
    

    delete sys;

    return 0;
}