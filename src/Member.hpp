#ifndef MEMBER_HPP
#define MEMBER_HPP

#include "Request.hpp"
#include "House.hpp"
#include "Rating.hpp"

class Member {
private:

public:
    Member() {};
    
    bool registerUser() {};

    void viewHouses() {};

    bool loginUser() {};

    bool searchHouse() {};

    bool requestToRentAHouse() {};

    void acceptRequestForAHouse() {};

    bool occupyAHouse() {};

    bool rateAHouse() {};

    bool rateAnOwner() {};
};

#endif