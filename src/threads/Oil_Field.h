//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_OIL_FIELD_H
#define SOTHREADS_OIL_FIELD_H


#include <iostream>
#include "../resources/Treasury.h"
#include "../util/consts.h"
#include "../util/utils.h"
#include "../SimulationState.h"

class Oil_Field {

public:
    static void put_petrodollars_in_treasury(SimulationState &simulationState) {
        while(!simulationState.time_to_exit_program){
            drill_oil();
            std::unique_lock<std::timed_mutex> treasuryLock(simulationState.treasury.dollars_mutex, std::defer_lock);
            treasuryLock.lock();
            simulationState.treasury.depositDollars(utils::generateRandomIntInRange(consts::OIL_FIELD_MIN_INCOME, consts::OIL_FIELD_MAX_INCOME));
        }
    }

    static void drill_oil(){std::this_thread::sleep_for(consts::OIL_FIELD_DRILL_TIME);}
};


#endif //SOTHREADS_OIL_FIELD_H
