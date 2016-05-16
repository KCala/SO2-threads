//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_ARMY_H
#define SOTHREADS_ARMY_H


#include <thread>
#include "../resources/Treasury.h"
#include "../resources/Armory.h"
#include "../util/consts.h"

class Army {
public:
    static void wage_war_with_neighbours(Treasury &treasury, Armory &armory, bool &time_to_exit_program){
        bool moneyTaken = false;
        bool weaponsTaken = false;

        while (!time_to_exit_program) {
            if(moneyTaken && weaponsTaken){
                attack_neighbours();
                moneyTaken = false;
                weaponsTaken = false;
            } else {
                wait_for_resources();
                moneyTaken = moneyTaken ? moneyTaken : take_money_from_treasury(treasury);
                weaponsTaken = weaponsTaken ? weaponsTaken : take_weapons_from_armory(armory);
            }
        }
    }
private:
    static bool take_money_from_treasury(Treasury& treasury){
        std::unique_lock<std::timed_mutex> treasuryLock(treasury.dollars_mutex, std::defer_lock);
        treasuryLock.lock();
        auto current_dollars = treasury.getDollars_number();
        if (current_dollars < consts::ARMY_ATTACK_PRICE) {
            return false;
        }
        treasury.takeDolars(consts::WEAPONS_PRICE);
//    std::cout << "ARMY TAKES MONEY FROM TREASURY!\n";
        return true;
    }
    static bool take_weapons_from_armory(Armory& armory){
        std::unique_lock<std::timed_mutex> armoryLock(armory.weapons_mutex, std::defer_lock);
        armoryLock.lock();
        if (armory.getWeapons_number() < consts::ARMY_WEAPONS_NUMBER_FOR_SINGLE_ATTACK) {
            return false;
        }
        armory.takeWeapons(consts::ARMY_WEAPONS_NUMBER_FOR_SINGLE_ATTACK);
//    std::cout << "ARMY TAKES WEAPONS!\n";
        return true;
    }
    static bool attack_neighbours(){
        std::this_thread::sleep_for(consts::ARMY_ATTACK_TIME);
    }

    static void wait_for_resources(){
        std::this_thread::sleep_for(consts::ARMY_NO_RESOURCES_COOLDOWN);
    }
};


#endif //SOTHREADS_ARMY_H
