//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_TERRORIST_ORGANIZATION_H
#define SOTHREADS_TERRORIST_ORGANIZATION_H


#include "../resources/Armory.h"
#include "../util/consts.h"

class Terrorist_Organization {
public:
    static void wage_war_with_infidels(SimulationState &simulationState) {
        while (!simulationState.time_to_exit_program) {
            take_weapons_from_armory(simulationState) ? perform_attack_in_europe(simulationState)
                                                             : wait_for_weapons(simulationState);
        }
    }

private:
    static bool take_weapons_from_armory(SimulationState &simulationState) {
        simulationState.terrorists_state = SimulationState::Terrorists_State::T_WAITING_FOR_ARMORY;
        std::unique_lock<std::timed_mutex> armoryLock(simulationState.armory.weapons_mutex, std::defer_lock);
        armoryLock.lock();
        simulationState.terrorists_state = SimulationState::Terrorists_State::T_IN_ARMORY;
        std::this_thread::sleep_for(consts::ARMORY_TIME);
        if (simulationState.armory.getWeapons_number() < consts::TERRORISTS_WEAPONS_NUMBER_STOLEN) {
            return false;
        }
        simulationState.armory.takeWeapons(consts::TERRORISTS_WEAPONS_NUMBER_STOLEN);
        simulationState.terrorists_state = SimulationState::Terrorists_State::T_WAITING_FOR_MORE_WEAPONS;
        return true;
    }

    static void perform_attack_in_europe(SimulationState &simulationState) {
        simulationState.terrorists_state = SimulationState::Terrorists_State::T_ATTACKING;
        std::this_thread::sleep_for(consts::TERRORISTS_ATTACK_TIME);
    }

    static void wait_for_weapons(SimulationState &simulationState) {
        simulationState.terrorists_state = SimulationState::Terrorists_State::T_WAITING_FOR_MORE_WEAPONS;
        std::this_thread::sleep_for(consts::TERRORISTS_NO_WEAPONS_COOLDOWN);
    }
};


#endif //SOTHREADS_TERRORIST_ORGANIZATION_H
