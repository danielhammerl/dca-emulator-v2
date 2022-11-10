//
// Created by Daniel Hammerl on 09.11.22.
//

#ifndef DCAEMULATOR_INSTRUCTIONSET_H
#define DCAEMULATOR_INSTRUCTIONSET_H

#include <cstdint>

const unsigned INSTRUCTION_SIZE = 5;

struct InstructionSet {
    uint8_t opcode;
    uint16_t operand1;
    uint16_t operand2;
};

#endif //DCAEMULATOR_INSTRUCTIONSET_H
