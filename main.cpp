#include <iostream>
#include <string>

using std::cout;
using std::cin;

#include "include/House.hpp"
#include "include/Member.hpp"
#include "include/System.hpp"

void handleChoiceInput(int &choice, string error_msg = "Please pick one of the listed numbers on the menu: ") {
    cin >> choice;
    while (cin.fail()) {
        cout << error_msg;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> choice;
    }
}

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
            cout << "\n-------------------GUEST MODE-------------------\n"
                 << "Menu:" << "\n"
                 << "1) Guest" << "\n"
                 << "2) Member" << "\n"
                 << "3) Admin" << "\n"
                 << "0) Exit" << "\n\n"
                 << "-> Please enter your choice: ";
            
            handleChoiceInput(choice);

            switch (choice) {
                case 1:
                    exitGuest = false;

                    while (!exitGuest) {
                        cout << "\n-------------------GUEST MODE-------------------\n"
                             << "1) View Houses\n"
                             << "2) Register as Member\n"
                             << "0) Exit\n\n"
                             << "-> Please enter your choice: ";

                        handleChoiceInput(choice);
     
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
                            cout << "\n-------------------MEMBER MODE-------------------\n"
                                    << "1) View Profile + House + Ratings\n"
                                    << "2) Register House\n"
                                    << "3) Delete House\n"
                                    << "4) Search House\n"
                                    << "5) Sent Rent House Request\n"
                                    << "6) Rate House\n"
                                    << "7) Rate Person\n"
                                    << "8) View Rent Requests\n"
                                    << "9) View Your Rent Requests\n"
                                    << "0) Exit\n\n"
                                    << "-> Please enter your choice: ";

                            handleChoiceInput(choice);

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
                                    cout << "Check the available houses first. Type House ID that you want to book: ";

                                    int id;
                                    handleChoiceInput(id, "Please type an available House ID (non-negative integer): ");

                                    sys->handleOccupyHouseRequest(sys->getLoggedMember()->getID(), id);
                                    break;
                                case 6:
                                    sys->handleRateHouse();
                                    break;
                                case 7:
                                    sys->handleRateUser();
                                    break;
                                case 8: {
                                    exitRequest = false;
                                    bool ifAcceptedRequests = sys->getLoggedMember()->viewAcceptedRequestsInfo();
                                    
                                    if (ifAcceptedRequests) {
                                        while (!exitRequest) {
                                            cout << "---------------------------------------\n\n"
                                                << "1) Accept Request\n"
                                                << "2) Decline Request\n"
                                                << "0) Exit\n\n"
                                                << "-> Please enter your choice: ";

                                            handleChoiceInput(choice);

                                            switch (choice) {
                                                case 1:
                                                    int acceptID;
                                                    cout << "\nChoose the Request ID to accept: ";
                                                    handleChoiceInput(acceptID, "Please type an available Request ID (non-negative integer): ");
                                                    sys->handleAcceptHouseRequest(acceptID - 1);
                                                    break;
                                                case 2:
                                                    int declineID;
                                                    cout << "\nChoose the Request ID to decline: ";
                                                    handleChoiceInput(declineID, "Please type an available Request ID (non-negative integer): ");
                                                    sys->handleAccepterDeclinesHouseRequest(declineID - 1);
                                                    break;
                                                case 0:
                                                    exitRequest = true;
                                                    break;
                                                default:
                                                    cout << "Invalid choice.\n";
                                                    break;
                                            }

                                            sys->getLoggedMember()->viewAcceptedRequestsInfo();
                                        }
                                    } 
                                    break;
                                }                          
                                case 9: {
                                    exitRequest = false;
                                    bool ifSentRequests = sys->getLoggedMember()->viewSentRequestsInfo();

                                    if (ifSentRequests) {
                                        while (!exitRequest) {
                                            cout << "---------------------------------------\n\n"
                                                << "1) Cancel Request\n"
                                                << "0) Exit\n\n"
                                                << "-> Please enter your choice: ";

                                            handleChoiceInput(choice);

                                            switch (choice) {
                                                case 1:
                                                    int id;
                                                    cout << "\nChoose the Request ID to cancel: ";
                                                    handleChoiceInput(id, "Please type an available Request ID (non-negative integer): ");
                                                    sys->handleSenderDeclinesHouseRequest(id - 1);
                                                    break;
                                                case 0:
                                                    exitRequest = true;
                                                    break;
                                                default:
                                                    cout << "Invalid choice.\n";
                                                    break;
                                            }

                                            sys->getLoggedMember()->viewSentRequestsInfo();
                                        }
                                    }
                                    break;
                                }
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
                    loopAdmin = false;

                    while (!loopAdmin) {                        
                        if (sys->loginAdmin()) { 
                            while (!loopAdmin) {
                                cout << "\n-------------------ADMIN MODE-------------------\n"
                                     << "1) View House Listing\n"
                                     << "2) View User Profile\n"
                                     << "0) Exit\n\n"
                                     << "-> Please enter your choice: ";

                                handleChoiceInput(choice);

                                switch (choice) {
                                    case 1:
                                        sys->viewHouses(nullptr, true);
                                        break;
                                    case 2:
                                        sys->viewUsers();
                                        break;
                                    case 0:
                                        loopAdmin = true;
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