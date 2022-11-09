//
// Created by Daniel Hammerl on 09.11.22.
//

#include "DcaEmulator.h"
#include "types/InstructionSet.h"
#include "GlobalState.h"
#include <iostream>
#include <sys/stat.h>
#include <fstream>

DcaEmulator::DcaEmulator(int argc, char *argv[]) : argc(argc), argv(argv) {

    cli = new CLI();
}

bool DcaEmulator::init() {
    std::cout << "DCA Emulator is warming up!" << std::endl;

    if (!cli->init(this->argc, this->argv)) {
        return false;
    }

    if (!readInputFile(cli->getPathToExecutable())) {
        return false;
    }
}

bool DcaEmulator::run() {
    return true;
}

DcaEmulator::~DcaEmulator() {
    delete cli;
}

bool DcaEmulator::readInputFile(std::string pathToExec) {
    struct stat results;

    if (stat(pathToExec.c_str(), &results) != 0) {
        std::cerr << "ERROR: Cannot get file size of input file" << std::endl;
        return false;
    }

    auto fileSize = results.st_size;
    char buffer[fileSize];
    auto instructionCount = fileSize / INSTRUCTION_SIZE;
    InstructionSet instructions[instructionCount];

    std::ifstream inputFile(pathToExec.c_str(), std::ios::in | std::ios::binary);
    inputFile.read(buffer, fileSize);

    for (int x = 0; x < instructionCount; x++) {
        auto offsetInBuffer = x * INSTRUCTION_SIZE;
        instructions[x] = {
                uint8_t(buffer[offsetInBuffer]),
                uint16_t(buffer[offsetInBuffer + 2] | buffer[offsetInBuffer + 1] << 8),
                uint16_t(buffer[offsetInBuffer + 4] | buffer[offsetInBuffer + 3] << 8),
        };
    }

    if (GlobalState::debugMode) {
        std::cout << "Read instructions:" << std::endl;

        for (int x = 0; x < instructionCount; x++) {
            std::cout << "Instruction " << (int) instructions[x].opcode << " with operands " << instructions[x].operand1
                      << " and " << instructions[x].operand2
                      << std::endl;
        }
    }

    if (!inputFile) {
        std::cerr << "ERROR: Cannot read input file" << std::endl;
        return false;
    }


}

