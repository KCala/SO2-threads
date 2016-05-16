#include <iostream>
#include <thread>
#include "resources/Treasury.h"
#include "threads/Oil_Field.h"
#include "resources/Armory.h"
#include "threads/Weapons_Factory.h"
#include "threads/Army.h"
#include "threads/Terrorist_Organization.h"
#include "display/Displayer.h"
#include "SimulationState.h"


using namespace std;

int main() {
    SimulationState simulationState;

    std::thread oil_field_thread(Oil_Field::put_petrodollars_in_treasury, std::ref(simulationState));
    std::thread weapons_factory_thread(Weapons_Factory::produce_weapons, std::ref(simulationState));
    std::thread army_thread(Army::wage_war_with_neighbours, std::ref(simulationState));
    std::thread terrorists_thread(Terrorist_Organization::wage_war_with_infidels, std::ref(simulationState));

    Displayer displayer;
    displayer.displaySimulationStateUntilKeypress(simulationState);

    simulationState.time_to_exit_program = true;
    oil_field_thread.join();
    weapons_factory_thread.join();
    army_thread.join();
    terrorists_thread.join();

}