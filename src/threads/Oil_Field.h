//
// Created by kamil on 15.05.16.
//

#ifndef SOTHREADS_OIL_FIELD_H
#define SOTHREADS_OIL_FIELD_H


#include <iostream>
#include "../resources/Treasury.h"

class Oil_Field {

public:
    static void put_petrodollars_in_treasury(Treasury &treasury, bool& time_to_exit_program);

    static void drill_oil();
};


#endif //SOTHREADS_OIL_FIELD_H
