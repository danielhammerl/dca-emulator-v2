//
// Created by Daniel Hammerl on 09.11.22.
//

#include "DcaEmulator.h"
#include "types/InstructionSet.h"
#include "GlobalState.h"
#include "memory/Memory.h"
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

    return true;
}

bool DcaEmulator::run() {
    return cpu->run();
}

DcaEmulator::~DcaEmulator() {
    delete cli;
    delete memory;
    delete cpu;
}

bool DcaEmulator::readInputFile(const std::string &pathToExec) {
    struct stat results{};

    if (stat(pathToExec.c_str(), &results) != 0) {
        std::cerr << "ERROR: Could not find input file" << std::endl;
        return false;
    }

    auto fileSize = results.st_size;
    char buffer[fileSize];

    std::ifstream inputFile(pathToExec.c_str(), std::ios::in | std::ios::binary);
    inputFile.read(buffer, fileSize);

    if (!inputFile) {
        std::cerr << "ERROR: Cannot read input file" << std::endl;
        return false;
    }

    memory = new Memory(buffer, (int) fileSize);

    cpu = new CPU(memory, fileSize);
    return true;
}

