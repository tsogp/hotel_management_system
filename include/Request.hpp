#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <utility>

#include "Date.hpp"
#include "House.hpp"
using std::pair;

class Request {
private:
    unsigned int requesterMemberID;
    unsigned int accepterMemberID;
    pair<Date, Date> requestDateRange;
    House* house = nullptr;
    bool isAccepted = false;
    bool isActive = true;
public:
    Request(unsigned int requesterMemberIDVal, unsigned int accepterMemberIDVal, pair<Date, Date> requestDateRangeVal, House* houseVal);

    friend class System;
    friend class Member;
};

#endif