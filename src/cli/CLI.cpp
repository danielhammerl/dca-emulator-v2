//
// Created by Daniel Hammerl on 09.11.22.
//

#include "CLI.h"
#include <iostream>
#include "../GlobalState.h"
#include "map"


bool CLI::init(int argc, char *argv[]) {
#ifdef NDEBUG
    if (argc == 1) {
        std::cerr << "ERROR: no path to executable is provided" << std::endl;
        return false;
    }

    this->pathToExecutable = argv[1];
#else
    this->pathToExecutable = "./test-executable.dbin";
#endif

    auto commands = initCommands();

    for (int additionalParamIndex = 1; additionalParamIndex < argc; additionalParamIndex++) {
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
            {"--debug", [] {
                GlobalState::debugMode = true;
            }},
            {
                    "--performance-data", [] {
                GlobalState::showPerformanceData = true;
            }}
    };
    return commands;
}
