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

    fileRead.open(location, std::ios::in);
    fileWrite.open(location, std::ios::app | std::ios::out);

    while (true)
    {
        std::cout << "Pls Type your Username and Password: \n";

        nameMaker:

        std::cout << "Username: ";

        std::cin >> userInput;

        if(fileRead.peek() == std::ifstream::traits_type::eof())
        {
            fileWrite << userInput << ",";

            std::cout << "Username " << userInput << " is the 1st in our list! Congrat! \n";

            break;

        }
        else
        {
            while(!fileRead.eof())
            {
                while(std::getline(fileRead, name, ','))
                {
                    if(name == userInput)
                    {
                        std::cout << "Username have already been taken! Pls choose another name. \n";

                        goto nameMaker;

                    }
                    else if(name != userInput && fileRead.eof())
                    {
                        fileWrite << userInput << ",";

                        std::cout << "Username Accepted! Hello " << userInput << "\n";

                        goto checkEnd;

                    }
                    else
                    {
                        continue;

                    };

                };
                
            };

        };
        checkEnd:break;

    };
    
    std::cout << "Password: ";
    
    std::cin >> passInput;

    fileWrite << passInput
        << "\n"; 

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