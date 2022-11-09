//
// Created by Daniel Hammerl on 09.11.22.
//

#ifndef DCAEMULATOR_DCAEMULATOR_H
#define DCAEMULATOR_DCAEMULATOR_H

#include "cli/CLI.h"

class DcaEmulator {
public:
    DcaEmulator() = delete;

    DcaEmulator(int argc, char *argv[]);

    ~DcaEmulator();

    bool init();

    bool run();

protected:

private:
    CLI *cli;

    int argc;
    char **argv;
};


#endif //DCAEMULATOR_DCAEMULATOR_H
