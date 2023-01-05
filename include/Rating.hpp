#ifndef RATING_HPP
#define RATING_HPP

#include <iostream>
using namespace std;
class Rating {
    private:
        int score;
        string comment;
    public:
        Rating(int scoreVal = 0, string commentVal = "")
        :score(scoreVal), comment(commentVal){}

    bool constraintCheck();
};

#endif