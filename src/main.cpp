#include <iostream>
#include <thread>
#include "resources/Treasury.h"
#include "threads/Oil_Field.h"
#include "resources/Armory.h"
#include "threads/Weapons_Factory.h"
#include "threads/Army.h"
#include "threads/Terrorist_Organization.h"


using namespace std;

int main() {
    Treasury treasury;
    Armory armory;

    std::thread oil_field_thread(Oil_Field::put_petrodollars_in_treasury, std::ref(treasury));
    std::thread weapons_factory_thread(Weapons_Factory::produce_weapons, std::ref(treasury), std::ref(armory));
    std::thread army_thread(Army::wage_war_with_neighbours, std::ref(treasury), std::ref(armory));
    std::thread terrorists_thread(Terrorist_Organization::wage_war_with_infidels, std::ref(armory));

    while (true) {
        std::cout << "Treasury: " << treasury.getDollars_number() << std::endl;
        std::cout << "Armory: " << armory.getWeapons_number() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

}