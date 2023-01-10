#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include "Member.hpp"
#include "House.hpp"
#define FILENAME "dataFile.csv"

class System
{
    private:
        vector<Member> members{};

    public:

        // Use to locate the user in the CSV file, then return the line of that specific username to be use
        int findMember(string username)
        {
            for(int i = 0; i < members.size(); i++)
            {
                if(members[i].username == username)
                {
                    cout << i;
                    return i;
                }
            }
            return -1;
        }
        
        // Data saving function, only use when closing out of the program
        bool saveData()
        {
            ofstream dataFile;
            dataFile.open(FILENAME,ios::out);
            if (!dataFile.is_open())
            {
                return false;
            }

            for (Member &mem: members)
            {
                dataFile << mem.ID << "/t" << mem.userType<< "\t" << mem.username << "\t" << mem.password << "\t" 
                         << mem.name << "\t" << mem.phoneNo << "\t" << mem.credits << "\n";
            }
            return true;
        }

        // To Register Memeber
        // 1) Try to find if the member username exist or not
        // 2) Ask user to input password, phone no and name
        // 3) Return false until everything is done
        bool registerMem()
        {   
            int ID;
            string username;
            cout << "Input your username: ";
            getline(cin,username);

            int position = findMember(username);
            if (position >= 0)
            {
                cout << "Username is already taken\n";
                return false;
            }
            else
            {
                string password,name;
                int phoneNo;

                cout << "Input your password: ";
                do
                {
                    getline(cin, password);
                } while (password == "");

                cout << "Enter your name: ";
                do
                {
                    getline(cin,name);
                } while (name == "");
                
                cout << "Enter your phone number: ";
                do
                {
                    cin >> phoneNo;
                    getchar();
                } while (phoneNo == 0);
                ID = members.size() + 1;
                members.push_back(Member(ID,"Member",username,name,password,phoneNo, 500));
                cout << "Registration complete!\n";
                return true;
            }
            
        }

        // Login Function 
        // 1) Find if the user name exist or not
        // 2) IF found, check if username and password matches
        // 3) Return true if done
        bool memberLogin(string userTypeVal)
        {
            string username, password; 
            int position;
            
            cout << "Please enter your username: ";
            getline(cin, username);
            position = findMember(username);

            if(position < 0 )
            {
                cout << "Username not found, please register that username!\n";
                return false;
            }

            if(members[position].userType != userTypeVal)
            {
                cout << "Username not found, please register that username!\n";
                return false;
            }

            cout << "Please enter your password: ";
            getline(cin,password);

            if(password == members[position].password)
            {
                cout << "Welcome back " << members[position].username << "\n";
                return true;
            }
            else
            {
                return false;
            }
        }
        
        // Load all data into their respected class, only to be use at the start of the program
        bool reloadData()
        {
            ifstream dataFile;
            dataFile.open(FILENAME, ios::in);

            if(!dataFile.is_open())
            {
                return false;
            }

            string username, password, name, phoneNo, ID, userType, credits;
            while (1)
            {
                getline(dataFile,ID,'\t');
                getline(dataFile,userType,'\t');
                getline(dataFile, username, '\t');
                getline(dataFile, password, '\t');
                getline(dataFile, name, '\t');
                getline(dataFile, phoneNo,'\t')
                getline(dataFile,credits);
                if (username == "")
                {
                    break;
                }
                members.push_back(Member(stoi(ID), userType, username, name, password, stoi(phoneNo),stod(credits)));
                
            }
            return true;
        }

        void viewProfile(string username)
        {
            int position = findMember(username);
            cout << "User Profile of " << members[position].username << "\n";
            cout << "User full name: " << members[position].name << "\n";
            cout << "User phone number: " << members[position].phoneNo << "\n";
            cout << "Credits amount: " << members[position].credits << "\n";

            // cout for house class in member
            
        }

        void guestView()
        {
            ///guest view for house
            //should only include a list of house with their location and description

            for(int i = 0; i < members.size(); i++)
            {
                cout << "House name: " << members[i].house.name << "\n";
                cout << "\tLocation: " << members[i].house.location << "\n";
                cout << "\tDescription: " << members[i].house.description << endl;
            }
        }
        
        void adminView()
        {
            //admin view
            //should inclue house location and description and amount of request

            for(int i = 0; i < members.size(); i++)
            {
                cout << "ID: " << members[i].ID << "| Username: " << members[i].username << endl;
                cout << "House name: " << members[i].house.name << "\n"; // add rating 
                // output number of request
                // if user request show occupier
            }
        }

        void searchHouse()
        {
            //check and return a valid list of house | Linked list for easy removal ?
        }

        bool rateOccupier()
        {
            // Return true when complete
            // Return false when failed
            
            int ID, score;
            string comment;

            // Check if the people 
            // Cout a list of occupier
            // If not on the list ask the user again

            cout << "Please enter the ID your occupier: ";
            cin >> ID;

            //pass check
            cout << "Please enter the rating from -10 to 10 four your occupier: ";
            cin >> score;
            //Check if it is in the -10 to 10 range

            cout << "Please enter the comment for your occupier: ";
            getline(cin,comment);

            members[ID-1].occupierRating.push_back(Rating(username,score,comment));

            return true;

            //return false when fail

        }

        bool rateHouse()
        {
            int ID, score;
            string comment;

            // Check if the people 
            // Cout a list of occupier
            // If not on the list ask the user again

            cout << "Please enter the ID the House you have occupied: ";
            cin >> ID;

            //pass check
            cout << "Please enter the rating from -10 to 10 for the house you have occupied: ";
            cin >> score;
            //Check if it is in the -10 to 10 range

            cout << "Please enter the comment for the house you have occupied: ";
            getline(cin,comment);

            members[ID-1].house.houseRating.push_back(Rating(username,score,comment));

            return true;

            //return false when fail
        }

        bool requestRent()
        {
            int position = findMember(username);

            // Check search house for suitable location
            // User input 
            // Validate user input
            // Once check is done pushback int the username of the person wanting to request rent
        }

        bool acceptRequest()
        {
            // Return true when complete
                //Remove everything else 
            // Return false when failed

            // Show list of requested user
            // Ask user to select a name or exit the tab
            // Validate user input
            // Clear the vector and pass the value through to 
        }

        void listHouse(string username)
        {
            string name;
            string location;
            string description;

            int postion = findMember(username);

            cout << "Please enter the name of the listed house: ";
            getline(cin,name);
            cout << "Please enter the location of your listed house: ";
            getline(cin,location);
            cout << "Pleae enter the description of your listed house: ";
            getline(cin,description);

            members[postion].house.name = name;
            members[postion].house.location = location;
            members[postion].house.description = description;
            //date to be added later
        }

        void unlistHouse(string username)
        {
            int postion = findMember(username);

            members[postion].house.name = "";
            members[postion].house.location = "";
            members[postion].house.description = "";
            //date to be added later
        }
};
#endif