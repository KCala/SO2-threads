//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_CONSTS_H
#define SOTHREADS_CONSTS_H

namespace consts{
    //oil field
    const int OIL_FIELD_MIN_INCOME = 200;
    const int OIL_FIELD_MAX_INCOME = 1000;
    const std::chrono::milliseconds OIL_FIELD_DRILL_TIME(2000);

    //weapon factory
    const int WEAPONS_PRICE = 800;
    const int WEAPONS_TO_DEPOSIT = 6;
    const std::chrono::milliseconds WEAPONS_ARMORY_NO_MONEY_COOLDOWN(1000);
    const std::chrono::milliseconds WEAPONS_ARMORY_MANUFACTURING_TIME(1000);

    //army
    const int ARMY_ATTACK_PRICE = 1000;
    const int ARMY_WEAPONS_NUMBER_FOR_SINGLE_ATTACK = 5;
    const std::chrono::milliseconds ARMY_ATTACK_TIME(5000);
    const std::chrono::milliseconds ARMY_NO_RESOURCES_COOLDOWN(1000);

    //terrorists
    const int TERRORISTS_WEAPONS_NUMBER_STOLEN = 5;
    const std::chrono::milliseconds TERRORISTS_NO_WEAPONS_COOLDOWN(3000);
    const std::chrono::milliseconds TERRORISTS_ATTACK_TIME(5000);

    //all
    const std::chrono::milliseconds TREASURY_TIME(1000);
    const std::chrono::milliseconds ARMORY_TIME(1000);

}

#endif //SOTHREADS_CONSTS_H
