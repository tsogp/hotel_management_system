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
    bool isAccepted;
    bool isActive;
public:
    Request(unsigned int requesterMemberIDVal, unsigned int accepterMemberIDVal, pair<Date, Date> requestDateRangeVal, House* houseVal, bool isAcceptedVal = false, bool isActiveVal = true);

    friend class System;
    friend class Member;
};

#endif