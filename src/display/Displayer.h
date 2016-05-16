//
// Created by kamil on 16.05.16.
//

#ifndef SOTHREADS_DISPLAYER_H
#define SOTHREADS_DISPLAYER_H


#include <ncurses.h>
#include <thread>
#include "../resources/Treasury.h"
#include "../resources/Armory.h"

class Displayer {
public:
    void initialize() {
        initscr();
        raw();
    }

    void displayStateAsText(const Treasury &treasury, const Armory &armory) {
        cbreak();
        noecho();
        nodelay(stdscr, TRUE);
        scrollok(stdscr, TRUE);

        while (true) {
            if(kbhit()) {
                break;
            }
            printf("Treasury: %i\n", treasury.getDollars_number());
            printf("Armory: %i\n", armory.getWeapons_number());
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
        }
    }

    void shutdown() {
        endwin();
    }

private:

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
