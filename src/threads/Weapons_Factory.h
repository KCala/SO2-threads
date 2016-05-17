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
    static void produce_weapons(SimulationState &simulationState) {
        while (!simulationState.time_to_exit_program) {
            if (take_money_from_treasury(simulationState)) {
                deposit_weapon_to_arsenal(simulationState);
                manufacture_weapons(simulationState);
            } else {
                wait_for_money(simulationState);
            }
        }
    }

private:
    static bool take_money_from_treasury(SimulationState &simulationState) {
        simulationState.weapons_factory_state = SimulationState::Weapons_Factory_State::W_WAITING_FOR_TREASURY;
        std::unique_lock<std::timed_mutex> treasuryLock(simulationState.treasury.dollars_mutex, std::defer_lock);
        treasuryLock.lock();
        simulationState.weapons_factory_state = SimulationState::Weapons_Factory_State::W_IN_TREASURY;
        std::this_thread::sleep_for(consts::TREASURY_TIME);
        auto current_dollars = simulationState.treasury.getDollars_number();
        if (current_dollars < consts::WEAPONS_PRICE) {
            return false;
        }
        simulationState.treasury.takeDolars(consts::WEAPONS_PRICE);
        simulationState.weapons_factory_state = SimulationState::Weapons_Factory_State::W_WAITING_FOR_MORE_MONEY;
        return true;
    }

    static void manufacture_weapons(SimulationState &simulationState) {
        simulationState.weapons_factory_state = SimulationState::Weapons_Factory_State::W_PRODUCING_WEAPON;
        std::this_thread::sleep_for(consts::WEAPONS_ARMORY_MANUFACTURING_TIME);
    }

    static void deposit_weapon_to_arsenal(SimulationState &simulationState) {
        simulationState.weapons_factory_state = SimulationState::Weapons_Factory_State::W_WAITING_FOR_ARMORY;
        std::unique_lock<std::timed_mutex> arsenalLock(simulationState.armory.weapons_mutex, std::defer_lock);
        arsenalLock.lock();
        simulationState.weapons_factory_state = SimulationState::Weapons_Factory_State::W_IN_ARMORY;
        std::this_thread::sleep_for(consts::ARMORY_TIME);
        simulationState.armory.depositWeapons(consts::WEAPONS_TO_DEPOSIT);
        simulationState.weapons_factory_state = SimulationState::Weapons_Factory_State::W_WAITING_FOR_MORE_MONEY;
    }

    static void wait_for_money(SimulationState &simulationState) {
        simulationState.weapons_factory_state = SimulationState::Weapons_Factory_State::W_WAITING_FOR_MORE_MONEY;
        std::this_thread::sleep_for(consts::WEAPONS_ARMORY_NO_MONEY_COOLDOWN);
    }
};


#endif //SOTHREADS_WEAPONS_FACTORY_H
