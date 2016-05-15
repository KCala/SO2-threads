//
// Created by kamil on 15.05.16.
//

#include <thread>
#include "Oil_Field.h"
#include "../util/utils.h"
#include "../util/consts.h"


void Oil_Field::put_petrodollars_in_treasury(Treasury &treasury) {
    while(true){
        drill_oil();
        std::unique_lock<std::timed_mutex> treasuryLock(treasury.dollars_mutex, std::defer_lock);
        treasuryLock.lock();
        treasury.depositDollars(utils::generateRandomIntInRange(consts::OIL_FIELD_MIN_INCOME, consts::OIL_FIELD_MAX_INCOME));
    }
}

void Oil_Field::drill_oil() { std::this_thread::sleep_for(consts::OIL_FIELD_DRILL_TIME); }

