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
#define FILENAME "dataFile.csv"

class System {
    private:
        vector<Member> members {};
    public:
        // Use to locate the user in the CSV file, then return the line of that specific username to be use
        int findMember(string username) {
            for(int i = 0; i < members.size(); i++) {
                if(members[i].username == username) {
                    cout << i;
                    return i;
                }
            }
            return -1;
        }
        
        // Data saving function, only use when closing out of the program
        bool saveData() {
            ofstream dataFile;
            dataFile.open(FILENAME, ios::out);
            if (!dataFile.is_open()) {
                return false;
            }

            for (Member &mem: members) {
                dataFile << mem.username << "\t" << mem.password << "\t" 
                         << mem.name << "\t" << mem.phoneNo << "\n";
            }
            return true;
        }

        // To Register Memeber
        // 1) Try to find if the member username exist or not
        // 2) Ask user to input password, phone no and name
        // 3) Return false until everything is done

        bool registerMem() {
            string username;
            cout << "Input your username: ";
            getline(cin, username);

            int position = findMember(username);
            if (position >= 0) {
                cout << "Username is already taken\n";
                return false;
            } else {
                string password,name;
                int phoneNo;

                cout << "Input your password: ";
                do {
                    getline(cin, password);
                } while (password == "");

                cout << "Enter your name: ";
                do {
                    getline(cin,name);
                } while (name == "");
                
                cout << "Enter your phone number: ";
                do {
                    cin >> phoneNo;
                    getchar();
                } while (phoneNo == 0);
                
                members.push_back(Member(username,name,password,phoneNo));
                cout << "Registration complete!\n";
                return true;
            }
            
        }

        // Login Function 
        // 1) Find if the user name exist or not
        // 2) IF found, check if username and password matches
        // 3) Return true if done
        bool login() {
            string username, password; 
            int position;
            
            cout << "Please enter your username: ";
            getline(cin, username);
            position = findMember(username);

            if(position < 0) {
                cout << "Username not found, please register that username!\n";
                return false;
            }

            cout << "Please enter your password: ";
            getline(cin, password);

            if (password == members[position].password) {
                cout << "Welcome back " << members[position].username << "\n";
                return true;
            } else {
                return false;
            }
        }
        
        // Load all data into their respected class, only to be use at the start of the program
        bool reloadData()
        {
            ifstream dataFile;
            dataFile.open(FILENAME, ios::in);

            if(!dataFile.is_open()) {
                return false;
            }

            string username, password, name, phoneNo;
            int i = 0;
            while (1) {
                i++;
                cout << i;
                getline(dataFile, username, '\t');
                getline(dataFile, password, '\t');
                getline(dataFile, name, '\t');
                getline(dataFile, phoneNo);
                if (username == "") {
                    break;
                }
                members.push_back(Member(username, name, password, stoi(phoneNo))); 
            }
            
            return true;
        }
};
#endif