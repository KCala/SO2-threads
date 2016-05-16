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
public:
    void displaySimulationStateUntilKeypress(const Treasury &treasury, const Armory &armory) {
        initialize();
        startDisplayLoop(treasury, armory);
        shutdown();
    }

private:

    void startDisplayLoop(const Treasury &treasury, const Armory &armory) {
        while (true) {
            if(kbhit()) {
                break;
            }
            printw("Treasury: %i\n", treasury.getDollars_number());
            printw("Armory: %i\n", armory.getWeapons_number());
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
        }
    }

    void initialize() {
        initscr();
        raw();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        scrollok(stdscr, TRUE);
    }

    void shutdown() {
        endwin();
        std::cout<<"Shutting down threads..." << std::endl;
    }

    int kbhit(void) {
        int ch = getch();

        if (ch != ERR) {
            ungetch(ch);
            return 1;
        } else {
            return 0;
        }
    }
};


#endif //SOTHREADS_DISPLAYER_H
