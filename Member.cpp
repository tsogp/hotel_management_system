#ifndef MEMBER_CPP
#define MEMBER_CPP

#include <iostream>
#include <string>
#include <fstream>

#include "../include/Member.hpp"

/* 
Member::Member() {

};

bool Member::registerUser() {

}

void Member::viewHouses() {

}

bool Member::loginUser() {

}

bool Member::searchHouse() {

}

bool Member::requestToRentAHouse() {

}

void Member::acceptRequestForAHouse() {

}

bool Member::occupyAHouse() {

}

bool Member::rateAHouse() {

}

bool Member::rateAnOwner() {

} 

*/

bool registerUser() 
{
    std::string userInput;
    std::string passInput;
    
    std::string location = "../people/list.csv";
    std::string name;
    std::string line;

    std::fstream fileRead;
    std::fstream fileWrite;

    bool endAll = false; // End all Loop

    fileWrite.open(location, std::ios::app | std::ios::out);

    while (true) // Name Maker loop
    {
        int elementCount = 1; // To pinpoint which element in the csv line

        if (endAll == true)
        {
            break;

        }
        else
        {
            bool loop1 = false;  // *Loop Switch 1*

            fileRead.open(location, std::ios::in);

            std::cout << "Username: ";

            std::cin >> userInput;

            if(fileRead.peek() == std::ifstream::traits_type::eof()) // Check if this the 1st name in the list
            {
                fileWrite << userInput << ",";

                std::cout << "Username " << userInput << " is the 1st in our list! Congrat! \n";

                break;

            }
            else 
            {
                if (loop1 == true) // *Loop Switch 1*
                {
                    break;

                }
                else
                {
                    while(!fileRead.eof()) // Till the end of file
                    {
                        while(std::getline(fileRead, name, ',')) // Get the elements
                        {

                            std::cout << name << "\n";
                            std::cout << elementCount << "\n";

                            if(name == userInput && (elementCount % 2 != 0)) // If 1st element which is name already exist make them input again
                            {
                                std::cout << "Username have already been taken! Pls choose another name. \n";

                                elementCount++;

                                loop1 = true;

                                fileRead.close();

                            }
                            else if(name != userInput && fileRead.eof() && (elementCount % 2 != 0)) // If name not yet appear and it not at the end of the file write it into the file
                            {
                                fileWrite << "\n" << userInput << ",";

                                std::cout << "Username Accepted! Hello " << userInput << "\n";

                                endAll = true;

                            }
                            else
                            {
                                elementCount++;

                            };

                        };
                        
                    };

                }

            };            

        }

    };
    
    std::cout << "Password: ";
    
    std::cin >> passInput;

    fileWrite << passInput << "\n"; 

    fileRead.close();
    fileWrite.close();

    return true;

};

int main(int argc, char *argv[])
{
    std::string username = "user1";
    std::string password = "pass1";

    registerUser();

};

#endif