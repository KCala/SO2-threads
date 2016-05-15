//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_ARMY_H
#define SOTHREADS_ARMY_H


#include "../resources/Treasury.h"
#include "../resources/Armory.h"

class Army {
public:
    static void wage_war_with_neighbours(Treasury &treasury, Armory &armory);
private:
    static bool take_money_from_treasury(Treasury& treasury);
    static bool take_weapons_from_armory(Armory& armory);
    static bool attack_neighbours();

    static void wait_for_resources();
};


#endif //SOTHREADS_ARMY_H
