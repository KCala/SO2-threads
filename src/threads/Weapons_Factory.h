//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_WEAPONS_FACTORY_H
#define SOTHREADS_WEAPONS_FACTORY_H


#include "../resources/Treasury.h"
#include "../resources/Armory.h"
#include "../util/consts.h"

class Weapons_Factory {
public:
    static void produce_weapons(Treasury &treasury, Armory &arsenal, bool &time_to_exit_program) {
        while (!time_to_exit_program) {
            if (take_money_from_treasury(treasury)) {
                deposit_weapon_to_arsenal(arsenal);
                manufacture_weapons();
            } else {
                wait_for_money();
            }
        }
    }

private:
    static bool take_money_from_treasury(Treasury &treasury) {
        std::unique_lock<std::timed_mutex> treasuryLock(treasury.dollars_mutex, std::defer_lock);
        treasuryLock.lock();
        auto current_dollars = treasury.getDollars_number();
        if (current_dollars < consts::WEAPONS_PRICE) {
            return false;
        }
        treasury.takeDolars(consts::WEAPONS_PRICE);
        return true;
    }

    static void manufacture_weapons() {
        std::this_thread::sleep_for(consts::WEAPONS_ARMORY_MANUFACTURING_TIME);
    }

    static void deposit_weapon_to_arsenal(Armory &arsenal) {
        std::unique_lock<std::timed_mutex> arsenalLock(arsenal.weapons_mutex, std::defer_lock);
        arsenalLock.lock();
        arsenal.depositWeapons(consts::WEAPONS_TO_DEPOSIT);
    }

    static void wait_for_money() { std::this_thread::sleep_for(consts::WEAPONS_ARMORY_NO_MONEY_COOLDOWN); }
};


#endif //SOTHREADS_WEAPONS_FACTORY_H
