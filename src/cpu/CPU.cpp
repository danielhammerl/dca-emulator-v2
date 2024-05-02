//
// Created by Daniel Hammerl on 10.11.22.
//

#include "CPU.h"
#include "../types/InstructionSet.h"
#include "../GlobalState.h"
#include <iostream>
#include <chrono>
#include <sstream>
#include "../gpu/EmptyGpu.h"

CPU::CPU(Memory *memory, unsigned long instructionsCount) : memory(memory) {
    registerInstructions();
    registerMap.at(dca::Register::RSP).setValue(instructionsCount);
    if (!GlobalState::noGpu) {
        gpu = new GPU(memory);
    } else {
        gpu = new EmptyGpu(memory);
    }
}


bool CPU::run() {
    auto startTime = std::chrono::high_resolution_clock::now();
    while (!finished) {
        auto currentInstructionIndex = registerMap.at(dca::Register::RPC).getValue();
        InstructionSet currentInstruction = {
                memory->getByte(currentInstructionIndex),
                memory->getHalfWord(currentInstructionIndex + 1),
                memory->getHalfWord(currentInstructionIndex + 3),
        };

        instructionDefinition.at(currentInstruction.opcode)(currentInstruction.operand1, currentInstruction.operand2,
                                                            currentInstructionIndex);
        gpu->tick();
        instructionCounter++;
    }

    auto endTime = std::chrono::high_resolution_clock::now();

    std::cout << "Program finished!" << std::endl;
    std::cout << "Return value is " << memory->getHalfWord(dca::Memory::MEMORY_MAX_LENGTH - 2) << std::endl;

    if (GlobalState::debugRegisterValues) {
        for (auto &it: registerMap) {
            std::cout << "Register " << it.second.getName() << " has value " << it.second.getValue() << std::endl;
        }
    }

    if (GlobalState::showPerformanceData) {
        std::chrono::duration<double, std::milli> durationInMs = endTime - startTime;
        std::cout << "Ran " << instructionCounter << " instructions in " << durationInMs.count() << "ms" << std::endl;
        std::cout << "This is equal to round about " << calculateClockRate(instructionCounter, durationInMs)
                  << std::endl;
    }

    return true;
}

void CPU::registerInstructions() {

    instructionDefinition[dca::Instructions::LOAD] = [&](uint16_t operand1, uint16_t operand2,
                                                         u_int16_t currentInstructionIndex) {
#ifdef MODE_DEBUG
        if (GlobalState::debugMode) {
            std::cout << "Run instruction LOAD with " << (int) operand1 << " and " << (int) operand2 << std::endl;
        }
#endif

        auto memoryAddress = registerMap.at(operand1).getValue();
        auto valueInMemory = memory->getByte(memoryAddress);
        registerMap.at(operand2).setValue(valueInMemory);
        loadNextInstruction(currentInstructionIndex);
    };

    instructionDefinition[dca::Instructions::STORE] = [&](uint16_t operand1, uint16_t operand2,
                                                          uint16_t currentInstructionIndex) {
#ifdef MODE_DEBUG
        if (GlobalState::debugMode) {
            std::cout << "Run instruction STORE with " << (int) operand1 << " and " << (int) operand2 << std::endl;
        }
#endif

        auto value = registerMap.at(operand1).getValue();
        uint8_t data = value & 0xff; // get lower byte
        auto memoryAddress = registerMap.at(operand2).getValue();
        memory->setByte(memoryAddress, data);
        loadNextInstruction(currentInstructionIndex);
    };

    instructionDefinition[dca::Instructions::SET] = [&](uint16_t operand1, uint16_t operand2,
                                                        uint16_t currentInstructionIndex) {
#ifdef MODE_DEBUG
        if (GlobalState::debugMode) {
            std::cout << "Run instruction SET with " << (int) operand1 << " and " << (int) operand2 << std::endl;
        }
#endif

        registerMap.at(operand1).setValue(operand2);
        loadNextInstruction(currentInstructionIndex);
    };

    instructionDefinition[dca::Instructions::LOADH] = [&](uint16_t operand1, uint16_t operand2,
                                                          uint16_t currentInstructionIndex) {
#ifdef MODE_DEBUG
        if (GlobalState::debugMode) {
            std::cout << "Run instruction LOADH with " << (int) operand1 << " and " << (int) operand2 << std::endl;
        }
#endif

        auto memoryAddress = registerMap.at(operand1).getValue();
        auto valueInMemory = memory->getHalfWord(memoryAddress);
        registerMap.at(operand2).setValue(valueInMemory);
        loadNextInstruction(currentInstructionIndex);
    };

    instructionDefinition[dca::Instructions::STOREH] = [&](uint16_t operand1, uint16_t operand2,
                                                           uint16_t currentInstructionIndex) {
#ifdef MODE_DEBUG
        if (GlobalState::debugMode) {
            std::cout << "Run instruction STOREH with " << (int) operand1 << " and " << (int) operand2 << std::endl;
        }
#endif

        uint16_t data = registerMap.at(operand1).getValue();
        auto memoryAddress = registerMap.at(operand2).getValue();
        memory->setHalfWord((int) memoryAddress, (int) data);
        loadNextInstruction(currentInstructionIndex);
    };

    instructionDefinition[dca::Instructions::ADD] = [&](uint16_t operand1, uint16_t operand2,
                                                        uint16_t currentInstructionIndex) {
#ifdef MODE_DEBUG
        if (GlobalState::debugMode) {
            std::cout << "Run instruction ADD with " << (int) operand1 << " and " << (int) operand2 << std::endl;
        }
#endif

        uint16_t result = registerMap.at(operand1).getValue() + registerMap.at(operand2).getValue();
        registerMap.at(operand1).setValue(result);
        loadNextInstruction(currentInstructionIndex);
    };

    instructionDefinition[dca::Instructions::SUB] = [&](uint16_t operand1, uint16_t operand2,
                                                        uint16_t currentInstructionIndex) {
#ifdef MODE_DEBUG
        if (GlobalState::debugMode) {
            std::cout << "Run instruction SUB with " << (int) operand1 << " and " << (int) operand2 << std::endl;
        }
#endif

        uint16_t result = registerMap.at(operand1).getValue() - registerMap.at(operand2).getValue();
        registerMap.at(operand1).setValue(result);
        loadNextInstruction(currentInstructionIndex);
    };

    instructionDefinition[dca::Instructions::CJUMP] = [&](uint16_t operand1, uint16_t operand2,
                                                          uint16_t currentInstructionIndex) {
#ifdef MODE_DEBUG
        if (GlobalState::debugMode) {
            std::cout << "Run instruction CJUMP with " << (int) operand1 << " and " << (int) operand2 << std::endl;
        }
#endif

        bool doJump = registerMap.at(operand2).getValue() == 0;

        if (doJump) {
            registerMap.at(dca::Register::RPC).setValue(registerMap.at(operand1).getValue());
        } else {
            loadNextInstruction(currentInstructionIndex);
        }
    };

    instructionDefinition[dca::Instructions::MOV] = [&](uint16_t operand1, uint16_t operand2,
                                                        uint16_t currentInstructionIndex) {
#ifdef MODE_DEBUG
        if (GlobalState::debugMode) {
            std::cout << "Run instruction MOV with " << (int) operand1 << " and " << (int) operand2 << std::endl;
        }
#endif

        auto value = registerMap.at(operand1).getValue();
        registerMap.at(operand2).setValue(value);
        loadNextInstruction(currentInstructionIndex);
    };

    instructionDefinition[dca::Instructions::CJUMPI] = [&](uint16_t operand1, uint16_t operand2,
                                                           uint16_t currentInstructionIndex) {
#ifdef MODE_DEBUG
        if (GlobalState::debugMode) {
            std::cout << "Run instruction CJUMPI with " << (int) operand1 << " and " << (int) operand2 << std::endl;
        }
#endif

        bool doJump = registerMap.at(operand2).getValue() != 0;

        if (doJump) {
            registerMap.at(dca::Register::RPC).setValue(registerMap.at(operand1).getValue());
        } else {
            loadNextInstruction(currentInstructionIndex);
        }
    };
}

void CPU::loadNextInstruction(uint16_t currentInstructionIndex) {
    if(currentInstructionIndex + INSTRUCTION_SIZE == registerMap.at(dca::Register::RSP).getValue()) {
        finished = true;
    }
    registerMap.at(dca::Register::RPC).setValue(currentInstructionIndex + INSTRUCTION_SIZE);
}

std::string
CPU::calculateClockRate(unsigned long long instCounter, std::chrono::duration<double, std::milli> durationInMs) {
    double duration = durationInMs.count();
    auto instructionsPerMs = (double) instCounter / duration;
    auto instructionsPerS = instructionsPerMs * 1000;

    int counter = 0;
    while (instructionsPerS >= 1000) {
        instructionsPerS = instructionsPerS / 1000;
        counter++;
    }

    const std::string suffixes[4] = {"Hz", "KHz", "MHz", "GHz"};

    std::stringstream stream;
    stream << instructionsPerS;
    stream << " ";
    stream << suffixes[counter];

    return stream.str();
}

CPU::~CPU() {
    if (!GlobalState::noGpu) {
        delete gpu;
    }
}
