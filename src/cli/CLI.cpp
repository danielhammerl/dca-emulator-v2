//
// Created by Daniel Hammerl on 09.11.22.
//

#include "CLI.h"
#include <iostream>
#include "../GlobalState.h"
#include "map"


bool CLI::init(int argc, char *argv[]) {
#ifdef MODE_RELEASE
    if (argc == 1) {
        std::cerr << "ERROR: no path to executable is provided" << std::endl;
        return false;
    }

    this->pathToExecutable = argv[1];
    const int DEBUG_OFFSET = 0;
#else
    this->pathToExecutable = "./test-executable.dbin";
    const int DEBUG_OFFSET = 1;
#endif

    auto commands = initCommands();

    for (int additionalParamIndex = 2 - DEBUG_OFFSET; additionalParamIndex < argc; additionalParamIndex++) {
        auto key = std::string(argv[additionalParamIndex]);
        if (!commands.contains(key)) {
            std::cerr << "ERROR: invalid parameter: " << key << std::endl;
            return false;
        }
        commands.at(key)();
    }

    return true;
}

std::map<std::string, std::function<void()>> CLI::initCommands() {
    auto commands = std::map<std::string, std::function<void()>>{
            {"--debug",            [] {
#ifdef MODE_DEBUG
                GlobalState::debugMode = true;
#else
                std::cout << "Debug mode not possible in release build" << std::endl;
#endif
            }},
            {
             "--performance-data", [] {
                GlobalState::showPerformanceData = true;
            }},
            {
             "--no-gpu", [] {
                GlobalState::noGpu = true;
            }},
            {
             "--debug-register-values", [] {
                GlobalState::debugRegisterValues = true;
            }}
    };
    return commands;
}
