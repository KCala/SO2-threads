//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_TREASURY_H
#define SOTHREADS_TREASURY_H


#include <mutex>

class Treasury {
private:
    int dollars_number = 0;
public:

    Treasury() {
    }

    std::timed_mutex dollars_mutex;

    int getDollars_number() const {
        return dollars_number;
    }

    void setDollars_number(int dollars_number) {
        Treasury::dollars_number = dollars_number;
    }

    bool takeDolars(int value) {
        if (value >= dollars_number) {
            return false;
        }
        dollars_number -= value;
        return true;
    }

    void depositDollars(int value) {
        dollars_number += value;
    }

};


#endif //SOTHREADS_TREASURY_H
