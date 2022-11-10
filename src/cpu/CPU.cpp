//
// Created by Daniel Hammerl on 10.11.22.
//

#include "CPU.h"
#include "../types/InstructionSet.h"


CPU::CPU(Memory *memory, unsigned long instructionsCount) {
    RSP.setValue(instructionsCount);
}


bool CPU::run() {
    while (!finished) {
        auto currentInstructionIndex = RPC.getValue();
        InstructionSet currentInstruction = {
                memory->getByte(currentInstructionIndex),
                memory->getHalfWord(currentInstructionIndex + 1),
                memory->getHalfWord(currentInstructionIndex + 3),
        };

        // ...

        if (RPC.getValue() == RSP.getValue()) {
            finished = true;
        }
    }
}