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
    static void wage_war_with_neighbours(SimulationState &simulationState) {
        bool moneyTaken = false;
        bool weaponsTaken = false;

        while (!simulationState.time_to_exit_program) {
            if (moneyTaken && weaponsTaken) {
                simulationState.army_resources_state = SimulationState::Army_Resources_State ::AR_ALL_ACQUIRED;
                attack_neighbours(simulationState);
                moneyTaken = false;
                weaponsTaken = false;
                simulationState.army_resources_state = SimulationState::Army_Resources_State ::AR_EMPTY;
            } else {
                wait_for_resources(simulationState);
                if (moneyTaken) {
                    simulationState.army_resources_state = SimulationState::Army_Resources_State::AR_MONEY_ACQUIRED;
                } else {
                    moneyTaken = take_money_from_treasury(simulationState);
                }
                if (weaponsTaken) {
                    simulationState.army_resources_state = SimulationState::Army_Resources_State::AR_WEAPONS_ACQUIRED;
                } else {
                    weaponsTaken = take_weapons_from_armory(simulationState);
                }
            }
        }
    }

private:
    static bool take_money_from_treasury(SimulationState &simulationState) {
        simulationState.army_state = SimulationState::Army_State::A_WAITING_FOR_TREASURY;
        std::unique_lock<std::timed_mutex> treasuryLock(simulationState.treasury.dollars_mutex, std::defer_lock);
        treasuryLock.lock();
        simulationState.army_state = SimulationState::Army_State::A_IN_TREASURY;
        std::this_thread::sleep_for(consts::TREASURY_TIME);
        auto current_dollars = simulationState.treasury.getDollars_number();
        if (current_dollars < consts::ARMY_ATTACK_PRICE) {
            return false;
        }
        simulationState.treasury.takeDolars(consts::WEAPONS_PRICE);
        simulationState.army_state = SimulationState::Army_State::A_WAITING_FOR_MORE_RESOURCES;
        return true;
    }

    static bool take_weapons_from_armory(SimulationState &simulationState) {
        simulationState.army_state = SimulationState::Army_State::A_WAITING_FOR_ARMORY;
        std::unique_lock<std::timed_mutex> armoryLock(simulationState.armory.weapons_mutex, std::defer_lock);
        armoryLock.lock();
        simulationState.army_state = SimulationState::Army_State::A_IN_ARMORY;
        std::this_thread::sleep_for(consts::ARMORY_TIME);
        if (simulationState.armory.getWeapons_number() < consts::ARMY_WEAPONS_NUMBER_FOR_SINGLE_ATTACK) {
            return false;
        }
        simulationState.armory.takeWeapons(consts::ARMY_WEAPONS_NUMBER_FOR_SINGLE_ATTACK);
        simulationState.army_state = SimulationState::Army_State::A_WAITING_FOR_MORE_RESOURCES;
        return true;
    }

    static bool attack_neighbours(SimulationState &simulationState) {
        simulationState.army_state = SimulationState::Army_State::A_ATTACKING;
        std::this_thread::sleep_for(consts::ARMY_ATTACK_TIME);
    }

    static void wait_for_resources(SimulationState &simulationState) {
        simulationState.army_state = SimulationState::Army_State::A_WAITING_FOR_MORE_RESOURCES;
        std::this_thread::sleep_for(consts::ARMY_NO_RESOURCES_COOLDOWN);
    }
};


#endif //SOTHREADS_ARMY_H
