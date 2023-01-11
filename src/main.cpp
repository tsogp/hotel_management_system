#include <iostream>
#include <string>

using std::cout;
using std::cin;

#include "../include/Admin.hpp"
#include "../include/House.hpp"
#include "../include/Member.hpp"
#include "../include/System.hpp"

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
    bool exitRequest = false;
    bool loopGuest = false;
    bool loopMember = false;
    bool loopAdmin = false;

    std::string username;

    System *sys = new System();

    if (sys != nullptr) {

        while (!exit) {
            cout << "---------------------------------------\n"
                 << "Menu:" << "\n"
                 << "1. Guest" << "\n"
                 << "2. Member" << "\n"
                 << "3. Admin" << "\n"
                 << "0. Exit" << "\n\n"
                 << "-> Please enter your choice: ";
            
            cin >> choice;

            switch (choice) {
                case 1:
                    exitGuest = false;

                    while (!exitGuest) {
                        cout << "\n---------------------------------------\n\n"
                             << "1) View Houses\n"
                             << "2) Register as Member\n"
                             << "0) Exit\n\n"
                             << "-> Please enter your choice: ";

                        cin >> choice;

                        switch (choice) {
                            case 1:
                                sys->viewHouses();
                                break;
                            case 2:
                                sys->registerMem();
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
                    loopMember = false;

                    while (!loopMember) {
                        if ((sys->getLoggedMember() != nullptr) || (sys->getLoggedMember() == nullptr && sys->loginUser())) {
                            cout << "\n---------------------------------------\n\n"
                                    << "1) View Profile\n"
                                    << "2) Register House\n"
                                    << "3) Delete House\n"
                                    << "4) Search House\n"
                                    << "5) Sent Rent House Request\n"
                                    << "6) Rate House\n"
                                    << "7) Rate Occupier\n"
                                    << "8) View Rent Requests\n"
                                    << "9) View Your Rent Requests\n"
                                    << "0) Exit\n\n"
                                    << "-> Please enter your choice: ";

                            cin >> choice;

                            switch (choice) {
                                case 1:
                                    sys->getLoggedMember()->viewProfile();
                                    break;
                                case 2:
                                    sys->getLoggedMember()->registerHouse();
                                    break;
                                case 3:
                                    if (sys->getLoggedMember()->viewHouse() != nullptr) {
                                        sys->getLoggedMember()->deleteHouse();
                                    } else {
                                        cout << "You haven't registered a house yet.\n\n";
                                    }
                                    break;
                                case 4:
                                    sys->viewHouses(sys->getLoggedMember());
                                    break;  
                                case 5:
                                    cout << "Type House ID that you want to book: ";

                                    unsigned int id;
                                    cin >> id;

                                    sys->handleOccupyHouseRequest(sys->getLoggedMember()->getID(), id);
                                    break;
                                case 6:

                                    break;
                                case 7:

                                    break;
                                case 8:
                                    exitRequest = false;
                                    sys->getLoggedMember()->viewAcceptedRequestsInfo();

                                    while (!exitRequest) {
                                        cout << "\n---------------------------------------\n\n"
                                             << "1) Accept Request\n"
                                             << "2) Decline Request\n"
                                             << "0) Exit\n\n"
                                             << "-> Please enter your choice: ";

                                        cin >> choice;

                                        switch (choice) {
                                            case 1:
                                                unsigned int acceptID;
                                                cout << "\nChoose the request ID to accept: ";
                                                cin >> acceptID;
                                                sys->handleAcceptHouseRequest(acceptID - 1);
                                                break;
                                            case 2:
                                                unsigned int declineID;
                                                cout << "\nChoose the request ID to decline: ";
                                                cin >> declineID;
                                                sys->handleAccepterDeclinesHouseRequest(declineID - 1);
                                                break;
                                            case 0:
                                                exitRequest = true;
                                                break;
                                            default:
                                                cout << "Invalid choice.\n";
                                                break;
                                        }
                                    }
                                    break;                          
                                case 9:
                                    exitRequest = false;
                                    sys->getLoggedMember()->viewSentRequestsInfo();

                                    while (!exitRequest) {
                                        cout << "\n---------------------------------------\n\n"
                                             << "1) Cancel Request\n"
                                             << "0) Exit\n\n"
                                             << "-> Please enter your choice: ";

                                        cin >> choice;

                                        switch (choice) {
                                            case 1:
                                                unsigned int id;
                                                cout << "\nChoose the request ID to cancel: ";
                                                cin >> id;
                                                sys->handleSenderDeclinesHouseRequest(id - 1);
                                                break;
                                            case 0:
                                                exitRequest = true;
                                                break;
                                            default:
                                                cout << "Invalid choice.\n";
                                                break;
                                        }
                                    }
                                    break;
                                case 0:
                                    loopMember = true;
                                    break;
                                default:
                                    cout << "Invalid choice.\n";
                                    break;
                            }
                        } else {    
                            loopMember = true;
                        }
                    }
                    break;
                case 3:
                    loopMember = false;

                    while (!loopAdmin) {
                        if ((sys->getLoggedMember() != nullptr) || (sys->getLoggedMember() == nullptr && sys->loginUser())) { //Please Change this to check for Admin Login) 
                            while(!exitAdmin) {
                                cout << "\n---------------------------------------\n\n"
                                     << "1) View House Listing\n"
                                     << "2) View User Profile\n"
                                     << "0) Exit\n\n"
                                     << "-> Please enter your choice: ";

                                cin >> choice;

                                switch (choice) {
                                    case 1:
                                        break;
                                    case 2:
                                        break;
                                    case 0:
                                        exitAdmin = true;
                                        break;
                                    default:
                                        cout << "Invalid choice." << "\n";
                                        break;
                                }  
                            }
                        } else {
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