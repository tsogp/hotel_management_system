#ifndef REQUEST_CPP
#define REQUEST_CPP

#include "../include/Request.hpp"

Request::Request(unsigned int requesterMemberIDVal, unsigned int accepterMemberIDVal, pair<Date, Date> requestDateRangeVal, House* houseVal, bool isAcceptedVal, bool isActiveVal) 
    : requesterMemberID(requesterMemberIDVal), accepterMemberID(accepterMemberIDVal), requestDateRange(requestDateRangeVal), house(houseVal), isAccepted(isAcceptedVal), isActive(isActiveVal) {};

#endif