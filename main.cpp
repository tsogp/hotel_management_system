#include <iostream>
#include <vector>
#include <string>

#include "include/Admin.hpp"
#include "include/House.hpp"
#include "include/Member.hpp"
#include "include/System.hpp"

int main(int argc, char *argv[]) 
{
    std::cout << "EEET2482/COSC2082 ASSIGNMENT\n"  
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

    System sys;

    while (!exit)
    {
        std::cout << "---------------------------------------\n";
        std::cout << "Menu:" << "\n";
        std::cout << "1. Guest" << "\n";
        std::cout << "2. Member" << "\n";
        std::cout << "3. Admin" << "\n";
        std::cout << "0. Exit" << "\n";
        std::cout << "->Please enter your choice: ";

        cin >> choice;

        switch (choice)
        {
            case 1:
                while (!exitGuest)
                {
                    std::cout << "---------------------------------------\n";
                    std::cout << "This is the guest menu\n";
                    std::cout << "1) View Listing\n";
                    std::cout << "2) Register as Member\n";
                    std::cout << "0) Exit\n";
                    std::cout << "->Please enter your choice: ";

                    cin >> choice;

                    switch (choice)
                    {
                        case 1:


                            break;

                        case 2:
                            while(!loopGuest)
                            {
                                if (/*bool check username function == true*/)
                                {
                                    std::cout << "Name has already been taken. Please choose another name";
                                
                                }
                                else
                                {
                                    std::cout << "Username accepted!";

                                    loopGuest = true;

                                }

                            }
                            break;

                        case 0:
                            exitGuest = true;

                            break;

                        default:
                            std::cout << "Invalid choice." << "\n";

                            break;

                    }                  

                }          

                break;

            case 2:
                while(!loopMember)
                {
                    if (/*sys.loginUser() == true*/)
                    {
                        while(!exitMember)
                        {
                            std::cout << "---------------------------------------\n";
                            std::cout << "This is the member menu:\n";
                            std::cout << "1) View Profile\n";
                            std::cout << "2) List House\n";
                            std::cout << "3) Unlist House\n";
                            std::cout << "4) Search House\n";
                            std::cout << "5) Rent House\n";
                            std::cout << "6) Rate House\n";
                            std::cout << "7) Rate Occupier\n";
                            std::cout << "8) View Rent Request\n";
                            std::cout << "0) Exit\n";
                            std::cout << "->Please enter your choice: ";

                            cin >> choice;

                            switch (choice)
                            {
                                case 1:


                                    break;

                                case 2:


                                    break;

                                case 3:


                                    break;

                                case 4:


                                    break;  

                                case 5:


                                    break;

                                case 6:


                                    break;

                                case 7:


                                    break;

                                case 8:


                                    break;                          

                                case 0:
                                    exitMember = true;

                                default:
                                    std::cout << "Invalid choice." << "\n";

                                    break;

                            }  

                        }

                    }
                    else
                    {    
                        std::cout << "Username or Password did not match. Please try again.";

                        loopMember = true;

                    }

                }

            case 3:
                while(!loopAdmin)
                {
                    if(/*sys.loginUser() == true*/) //Please Change this to check for Admin Login
                    {
                        while(!exitAdmin)
                        {
                            
                            std::cout << "---------------------------------------\n";
                            std::cout << "This is the admin menu:\n";
                            std::cout << "1) View House Listing\n";
                            std::cout << "2) View User Profile\n";
                            std::cout << "0) Exit\n";
                            std::cout << "->Please enter your choice: ";

                            cin >> choice;

                            switch (choice)
                            {
                                case 1:


                                    break;

                                case 2:


                                    break;

                                case 0:
                                    exitAdmin = true;

                                default:
                                    std::cout << "Invalid choice." << "\n";

                                    break;

                            }  

                        }

                    }
                    else
                    {
                        std::cout << "Username or Password did not match. Please try again.";

                        loopAdmin = true;

                    }

                }

                break;

            case 0:
                exit = true;

                break;

            default:
                std::cout << "Invalid choice." << "\n";

                break;

        }

    }
    return 0;

}