//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_WEAPONS_FACTORY_H
#define SOTHREADS_WEAPONS_FACTORY_H


#include "../resources/Treasury.h"
#include "../resources/Armory.h"

class Weapons_Factory {
public:
    static void produce_weapons(Treasury &treasury, Armory &arsenal, bool &time_to_exit_program);
private:
    static bool take_money_from_treasury(Treasury& treasury);
    static void manufacture_weapons();
    static void deposit_weapon_to_arsenal(Armory& arsenal);

    static void wait_for_money();
};


#endif //SOTHREADS_WEAPONS_FACTORY_H
