//
// Created by Daniel Hammerl on 09.11.22.
//

#include "DcaEmulator.h"
#include <iostream>

DcaEmulator::DcaEmulator(int argc, char *argv[]) : argc(argc), argv(argv) {

    cli = new CLI();
}

bool DcaEmulator::init() {
    std::cout << "DCA Emulator is warming up!" << std::endl;

    if(!cli->init(this->argc, this->argv)) {
        return false;
    }
}

bool DcaEmulator::run() {
    return true;
}

DcaEmulator::~DcaEmulator() {
    delete cli;
}

