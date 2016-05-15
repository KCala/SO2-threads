//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_TERRORIST_ORGANIZATION_H
#define SOTHREADS_TERRORIST_ORGANIZATION_H


#include "../resources/Armory.h"

class Terrorist_Organization {
public:
    static void wage_war_with_infidels(Armory& armory);

private:
    static bool take_weapons_from_armory(Armory& armory);
    static void perform_attack_in_europe();

    static void wait_for_weapons();
};


#endif //SOTHREADS_TERRORIST_ORGANIZATION_H
