//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_TERRORIST_ORGANIZATION_H
#define SOTHREADS_TERRORIST_ORGANIZATION_H


#include "../resources/Armory.h"
#include "../util/consts.h"

class Terrorist_Organization {
public:
    static void wage_war_with_infidels(SimulationState &simulationState){
        while (!simulationState.time_to_exit_program) {
            (take_weapons_from_armory(simulationState.armory) ? perform_attack_in_europe : wait_for_weapons)();
        }
    }

private:
    static bool take_weapons_from_armory(Armory& armory){
        std::unique_lock<std::timed_mutex> armoryLock(armory.weapons_mutex, std::defer_lock);
        armoryLock.lock();
        if (armory.getWeapons_number() < consts::TERRORISTS_WEAPONS_NUMBER_STOLEN) {
            return false;
        }
        armory.takeWeapons(consts::TERRORISTS_WEAPONS_NUMBER_STOLEN);
//    std::cout << "TERRORISTS STEAL WEAPONS!\n";
        return true;
    }
    static void perform_attack_in_europe(){
        std::this_thread::sleep_for(consts::TERRORISTS_ATTACK_TIME);
    }

    static void wait_for_weapons(){
        std::this_thread::sleep_for(consts::TERRORISTS_NO_WEAPONS_COOLDOWN);
    }
};


#endif //SOTHREADS_TERRORIST_ORGANIZATION_H
