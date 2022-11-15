//
// Created by Daniel Hammerl on 10.11.22.
//

#ifndef DCAEMULATOR_CPU_H
#define DCAEMULATOR_CPU_H


#include "../memory/Memory.h"
#include "Register.h"
#include "../gpu/GPU.h"
#include <map>
#include <string>
#include "../constants.h"

class CPU {
public:
    CPU(Memory *memory, unsigned long instructionsCount);
    ~CPU();

    bool run();

protected:
    void registerInstructions();

private:
    Memory *memory;


    std::map<uint16_t, Register> registerMap = {
            {dca::Register::RPC, Register("RPC")},
            {dca::Register::R00, Register("R00")},
            {dca::Register::R01, Register("R01")},
            {dca::Register::R02, Register("R02")},
            {dca::Register::R03, Register("R03")},
            {dca::Register::R04, Register("R04")},
            {dca::Register::R05, Register("R05")},
            {dca::Register::R06, Register("R06")},
            {dca::Register::R07, Register("R07")},
            {dca::Register::R08, Register("R08")},
            {dca::Register::R09, Register("R09")},
            {dca::Register::R10, Register("R10")},
            {dca::Register::RSP, Register("RSP")},
    };

    void loadNextInstruction();

    bool finished = false;

    std::map<uint8_t, std::function<void(uint16_t operand1, uint16_t operand2)>> instructionDefinition;

    unsigned long long instructionCounter = 0;

    static std::string calculateClockRate(unsigned long long instCounter,
                                          std::chrono::duration<double, std::milli> durationInMs);

    GPU *gpu;
};


#endif //DCAEMULATOR_CPU_H
