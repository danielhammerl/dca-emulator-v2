//
// Created by Daniel Hammerl on 10.11.22.
//

#ifndef DCAEMULATOR_CPU_H
#define DCAEMULATOR_CPU_H


#include "../memory/Memory.h"
#include "Register.h"
#include <map>
#include <string>

class CPU {
public:
    CPU(Memory *memory, unsigned long instructionsCount);

    bool run();

    const uint16_t RPC = 1, R00 = 2, R01 = 3, R02 = 4, R03 = 5, R04 = 6, R05 = 7,
            R06 = 8, R07 = 9, R08 = 10, R09 = 11, RSP = 32;

    const uint8_t LOAD = 1, STORE = 2, SET = 3, LOADH = 4, STOREH = 5, ADD = 6,
            SUB = 7, CJUMP = 8, MOV = 9, CJUMPI = 10;

protected:
    void registerInstructions();

private:
    Memory *memory;


    std::map<uint16_t, Register> registerMap = {
            {RPC, Register("RPC")},
            {R00, Register("R00")},
            {R01, Register("R01")},
            {R02, Register("R02")},
            {R03, Register("R03")},
            {R04, Register("R04")},
            {R05, Register("R05")},
            {R06, Register("R06")},
            {R07, Register("R07")},
            {R08, Register("R08")},
            {R09, Register("R09")},
            {RSP, Register("RSP")},
    };

    void loadNextInstruction();

    bool finished = false;

    std::map<uint8_t, std::function<void(uint16_t operand1, uint16_t operand2)>> instructionDefinition;

    unsigned long long instructionCounter = 0;

    static std::string calculateClockRate(unsigned long long instCounter,
                                   std::chrono::duration<double, std::milli> durationInMs) ;
};


#endif //DCAEMULATOR_CPU_H
