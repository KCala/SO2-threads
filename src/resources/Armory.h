//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_ARSENAL_H
#define SOTHREADS_ARSENAL_H


#include <mutex>

class Armory {
private:
    int weapons_number = 0;
public:
    std::timed_mutex weapons_mutex;

    int getWeapons_number() const {
        return weapons_number;
    }

    void setWeapons_number(int weapons_number) {
        Armory::weapons_number = weapons_number;
    }

    bool takeWeapons(int number){
        if(number>weapons_number){
            return false;
        }
        weapons_number-=number;
        return true;
    }

    bool depositWeapons(int number){
        weapons_number+=number;
    }
};


#endif //SOTHREADS_ARSENAL_H
