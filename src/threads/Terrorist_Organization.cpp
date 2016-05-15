//
// Created by kamil on 15.05.16.
//

#include <thread>
#include <iostream>
#include "Terrorist_Organization.h"
#include "../util/consts.h"


void Terrorist_Organization::wage_war_with_infidels(Armory &armory) {
    while(true){
        while(!take_weapons_from_armory(armory)){
            wait_for_weapons();
        }
        perform_attack_in_europe();
    }
}

bool Terrorist_Organization::take_weapons_from_armory(Armory &armory) {
    std::unique_lock<std::timed_mutex> armoryLock(armory.weapons_mutex, std::defer_lock);
    armoryLock.lock();
    if(armory.getWeapons_number() < consts::TERRORISTS_WEAPONS_NUMBER_STOLEN){
        return false;
    }
    armory.takeWeapons(consts::TERRORISTS_WEAPONS_NUMBER_STOLEN);
    std::cout << "TERRORISTS STEAL WEAPONS!\n";
    return true;
}

void Terrorist_Organization::perform_attack_in_europe() {
    std::cout << "TERRORISTS ATTACK IN EUROPE!\n";
    std::this_thread::sleep_for(consts::TERRORISTS_ATTACK_TIME);
}

void Terrorist_Organization::wait_for_weapons() {
    std::this_thread::sleep_for(consts::TERRORISTS_NO_WEAPONS_COOLDOWN);
}








