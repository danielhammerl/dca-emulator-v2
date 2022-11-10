//
// Created by Daniel Hammerl on 10.11.22.
//

#ifndef DCAEMULATOR_CPU_H
#define DCAEMULATOR_CPU_H


#include "../memory/Memory.h"
#include "Register.h"

class CPU {
public:
    CPU(Memory *memory, unsigned long instructionsCount);

    bool run();

private:
    Memory *memory;

    Register RPC = Register(1);
    Register R00 = Register(2);
    Register R01 = Register(3);
    Register R02 = Register(4);
    Register R03 = Register(5);
    Register R04 = Register(6);
    Register R05 = Register(7);
    Register R06 = Register(8);
    Register R07 = Register(9);
    Register R08 = Register(10);
    Register R09 = Register(11);
    Register RSP = Register(32);

    bool finished = false;
};


#endif //DCAEMULATOR_CPU_H
