//
// Created by kamil on 17.05.16.
//

#ifndef SOTHREADS_SIMULATIONSTATE_H
#define SOTHREADS_SIMULATIONSTATE_H


#include "resources/Treasury.h"
#include "resources/Armory.h"

class SimulationState {
public:
    Treasury treasury;
    Armory armory;

    enum Oil_Field_State {
        O_DRILLING, O_WAITING_FOR_TREASURY, O_IN_TREASURY
    };
    enum Weapons_Factory_State {
        W_WAITING_FOR_TREASURY, W_IN_TREASURY, W_WAITING_FOR_ARMORY, W_IN_ARMORY, W_PRODUCING_WEAPON, W_WAITING_FOR_MORE_MONEY
    };
    enum Army_State {
        A_WAITING_FOR_TREASURY, A_IN_TREASURY, A_WAITING_FOR_ARMORY, A_IN_ARMORY, A_ATTACKING, A_WAITING_FOR_MORE_RESOURCES
    };
    enum Army_Resources_State {
        AR_EMPTY, AR_MONEY_ACQUIRED, AR_WEAPONS_ACQUIRED, AR_ALL_ACQUIRED
    };
    enum Terrorists_State {
        T_WAITING_FOR_ARMORY, T_IN_ARMORY, T_ATTACKING, T_WAITING_FOR_MORE_WEAPONS
    };

    Oil_Field_State oil_field_state = O_DRILLING;
    Weapons_Factory_State weapons_factory_state = W_WAITING_FOR_MORE_MONEY;
    Army_State army_state = A_WAITING_FOR_MORE_RESOURCES;
    Army_Resources_State army_resources_state = AR_EMPTY;
    Terrorists_State terrorists_state = T_WAITING_FOR_MORE_WEAPONS;
};


#endif //SOTHREADS_SIMULATIONSTATE_H
