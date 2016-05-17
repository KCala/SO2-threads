//
// Created by kamil on 16.05.16.
//

#ifndef SOTHREADS_DISPLAYER_H
#define SOTHREADS_DISPLAYER_H


#include <ncurses.h>
#include <thread>
#include <iostream>
#include <fstream>
#include "../resources/Treasury.h"
#include "../resources/Armory.h"

class Displayer {
private:
    SimulationState &simulationState;
    int min_window_y = 24;
    int min_window_x = 74;
    std::vector<std::string> scene;

    int get_current_window_y() {
        return getmaxy(stdscr);
    }

    int get_cuurent_window_x() {
        return getmaxx(stdscr);
    }

public:
    Displayer(SimulationState &simulationState) : simulationState(simulationState) { }

    void displaySimulationStateUntilKeypress() {
        initialize();
        startDisplayLoop();
        shutdown();
    }

private:
    void startDisplayLoop() {
        while (true) {
            if (kbhit()) {
                break;
            }
            if (get_current_window_y() < min_window_y || get_cuurent_window_x() < min_window_x) {
                displayResizePrompt();
            } else {
                displayActualSimulationState();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void displayResizePrompt() {
        clear();
        mvaddstr(get_current_window_y() / 2 - 1, get_cuurent_window_x() / 2 - 11, "Resize to bigger window...");
        mvaddstr(get_current_window_y() / 2 + 1, get_cuurent_window_x() / 2 - 7, "ENTER to exit");
    }

    void displayActualSimulationState() {
        drawBackground();
        placeActors();
        mvaddstr(min_window_y,min_window_x-10,"~by kcala");
        refresh();
    }

    void drawBackground() {
        int i = 0;
        for (auto line : scene) {
            mvaddstr(i, 0, line.c_str());
            i++;
        }
    }

    void placeActors() {
        placeOilFieldActor();
        placeFactoryActor();
        placeArmyActor();
        placeArmyResourcesActor();
        placeTerroristsActor();
        placeMoneyAmount();
        placeWeaponsAmount();
    }

    void placeOilFieldActor() {
        attron(COLOR_PAIR(2));
        switch (simulationState.oil_field_state) {
            case SimulationState::O_DRILLING:
                mvaddstr(2,2,"O drilling...");
                break;
            case SimulationState::O_WAITING_FOR_TREASURY:
                mvaddstr(5,49,"O");
                break;
            case SimulationState::O_IN_TREASURY:
                mvaddstr(5,30,"O");
                break;
        }
        attroff(COLOR_PAIR(2));
    }

    void placeFactoryActor() {
        attron(COLOR_PAIR(3));
        switch (simulationState.weapons_factory_state) {
            case SimulationState::W_WAITING_FOR_TREASURY:
                mvaddstr(5,51, "F");
                break;
            case SimulationState::W_IN_TREASURY:
                mvaddstr(5,32, "F");
                break;
            case SimulationState::W_WAITING_FOR_ARMORY:
                mvaddstr(12,51,"F");
                break;
            case SimulationState::W_IN_ARMORY:
                mvaddstr(12,32,"F");
                break;
            case SimulationState::W_PRODUCING_WEAPON:
                mvaddstr(8,2, "F producing...");
                break;
            case SimulationState::W_WAITING_FOR_MORE_MONEY:
                mvaddstr(8,2, "F waiting...");
                break;
        }
        attroff(COLOR_PAIR(3));
    }

    void placeArmyActor() {
        attron(COLOR_PAIR(4));
        switch (simulationState.army_state){
            case SimulationState::A_WAITING_FOR_TREASURY:
                mvaddstr(5,53, "A");
                break;
            case SimulationState::A_IN_TREASURY:
                mvaddstr(5,34, "A");
                break;
            case SimulationState::A_WAITING_FOR_ARMORY:
                mvaddstr(12,53,"A");
                break;
            case SimulationState::A_IN_ARMORY:
                mvaddstr(12,34,"A");
                break;
            case SimulationState::A_ATTACKING:
                mvaddstr(20,34, "A attacking...");
                break;
            case SimulationState::A_WAITING_FOR_MORE_RESOURCES:
                mvaddstr(14,2, "A waiting...");
                break;
        }
        attroff(COLOR_PAIR(4));
    }

    void placeArmyResourcesActor() {
        attron(COLOR_PAIR(5));
        switch (simulationState.army_resources_state){
            case SimulationState::AR_EMPTY:

                break;
            case SimulationState::AR_MONEY_ACQUIRED:
                mvaddstr(15,3, "$$$");
                break;
            case SimulationState::AR_WEAPONS_ACQUIRED:
                mvaddstr(15,7, "wpns");
                break;
            case SimulationState::AR_ALL_ACQUIRED:
                mvaddstr(15,3, "$$$ wpns");
                break;
        }
        attroff(COLOR_PAIR(5));
    }

    void placeTerroristsActor(){
        attron(COLOR_PAIR(6));
        switch(simulationState.terrorists_state){

            case SimulationState::T_WAITING_FOR_ARMORY:
                mvaddstr(12,55,"T");
                break;
            case SimulationState::T_IN_ARMORY:
                mvaddstr(12,36,"T");
                break;
            case SimulationState::T_ATTACKING:
                mvaddstr(20,60, "T attacking...");
                mvaddstr(21,3, "wpns");
                break;
            case SimulationState::T_WAITING_FOR_MORE_WEAPONS:
                mvaddstr(20,2, "T waiting...");
                break;
        }
        attroff(COLOR_PAIR(6));
    }

    void placeMoneyAmount(){
        attron(COLOR_PAIR(7));
        std::string amount(std::to_string(simulationState.treasury.getDollars_number()));
        amount += "$";
        mvaddstr(4,30, amount.c_str());
        attroff(COLOR_PAIR(7));
    }

    void placeWeaponsAmount(){
        attron(COLOR_PAIR(8));
        std::string amount(std::to_string(simulationState.armory.getWeapons_number()));
        amount += "p";
        mvaddstr(11,30, amount.c_str());
        attroff(COLOR_PAIR(8));
    }


    void loadSceneFromFile(std::string filePath) {
        std::string inString;
        std::ifstream infile;
        infile.open(filePath);
        while (!infile.eof()) {
            getline(infile, inString);
            scene.push_back(inString);
        }
        infile.close();
    }

    void initialize() {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        scrollok(stdscr, TRUE);

        start_color();

        init_pair(1, COLOR_BLACK, COLOR_WHITE); //background
        init_pair(2, COLOR_YELLOW, COLOR_WHITE); //oil_field
        init_pair(3, COLOR_BLUE, COLOR_WHITE); //factory
        init_pair(4, COLOR_GREEN, COLOR_WHITE); //army
        init_pair(5, COLOR_WHITE, COLOR_GREEN); //army_resource
        init_pair(6, COLOR_WHITE, COLOR_BLACK); //terrorist

        init_pair(7, COLOR_GREEN, COLOR_WHITE); //money amount
        init_pair(8, COLOR_MAGENTA, COLOR_WHITE); //weapons amount



        bkgd(COLOR_PAIR(1));

        loadSceneFromFile("../scene.txt");
    }

    void shutdown() {
        endwin();
        std::cout << "Shutting down threads..." << std::endl;
    }

    bool kbhit(void) {
        int ch = getch();
        if (ch != ERR && ch == '\n') {
//            ungetch(ch);
            return true;
        } else {
            return false;
        }
    }
};


#endif //SOTHREADS_DISPLAYER_H
