//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_RANDOM_H
#define SOTHREADS_RANDOM_H


#include <random>

namespace utils {
    int generateRandomIntInRange(int low, int up) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator
        std::uniform_int_distribution<> distr(low, up); // define the range
        return distr(eng);
    }
}

#endif //SOTHREADS_RANDOM_H
