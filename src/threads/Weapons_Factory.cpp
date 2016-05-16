//
// Created by kamil on 15.05.16.
//

#include <thread>
#include <iostream>
#include "Weapons_Factory.h"
#include "../util/consts.h"

void Weapons_Factory::produce_weapons(Treasury &treasury, Armory &arsenal, bool &time_to_exit_program) {
    while (!time_to_exit_program) {
        if (take_money_from_treasury(treasury)) {
            deposit_weapon_to_arsenal(arsenal);
            manufacture_weapons();
        } else {
            wait_for_money();
        }
    }
}

void Weapons_Factory::wait_for_money() { std::this_thread::sleep_for(consts::WEAPONS_ARMORY_NO_MONEY_COOLDOWN); }

bool Weapons_Factory::take_money_from_treasury(Treasury &treasury) {
    std::unique_lock<std::timed_mutex> treasuryLock(treasury.dollars_mutex, std::defer_lock);
    treasuryLock.lock();
    auto current_dollars = treasury.getDollars_number();
    if (current_dollars < consts::WEAPONS_PRICE) {
        return false;
    }
    treasury.takeDolars(consts::WEAPONS_PRICE);
    return true;
}

void Weapons_Factory::deposit_weapon_to_arsenal(Armory &arsenal) {
    std::unique_lock<std::timed_mutex> arsenalLock(arsenal.weapons_mutex, std::defer_lock);
    arsenalLock.lock();
    arsenal.depositWeapons(consts::WEAPONS_TO_DEPOSIT);
}

void Weapons_Factory::manufacture_weapons() {
    std::this_thread::sleep_for(consts::WEAPONS_ARMORY_MANUFACTURING_TIME);
}







