//
// Created by Daniel Hammerl on 09.11.22.
//

#ifndef DCAEMULATOR_CLI_H
#define DCAEMULATOR_CLI_H

#include <string>
#include "../base.h"
#include <map>

class CLI {
public:
    bool init(int argc, char *argv[]);

    [[nodiscard]] const std::string &getPathToExecutable() const {
        return pathToExecutable;
    }

private:
    std::string pathToExecutable;

    static std::map<std::string, std::function<void()>> initCommands();
};


#endif //DCAEMULATOR_CLI_H
