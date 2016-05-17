//
// Created by kamil on 16.05.16.
//

#ifndef SOTHREADS_DISPLAYER_H
#define SOTHREADS_DISPLAYER_H


#include <ncurses.h>
#include <thread>
#include <iostream>
#include "../resources/Treasury.h"
#include "../resources/Armory.h"

class Displayer {
private:
    SimulationState &simulationState;
    int min_window_y = 40;
    int min_window_x = 100;

    int get_current_window_y(){
        return getmaxy(stdscr);
    }
    int get_cuurent_window_x(){
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
        mvaddstr(get_current_window_y()/2-1, get_cuurent_window_x()/2-11, "Resize to bigger window...");
        mvaddstr(get_current_window_y()/2+1, get_cuurent_window_x()/2-7, "ENTER to exit");
    }

    void displayActualSimulationState() {
        clear();
    }

    void initialize() {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        scrollok(stdscr, TRUE);
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
