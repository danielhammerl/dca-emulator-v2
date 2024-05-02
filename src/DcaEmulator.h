//
// Created by Daniel Hammerl on 09.11.22.
//

#ifndef DCAEMULATOR_DCAEMULATOR_H
#define DCAEMULATOR_DCAEMULATOR_H

#include "cli/CLI.h"
#include "types/InstructionSet.h"
#include "memory/Memory.h"
#include "cpu/CPU.h"
#include <list>
#include "base.h"

class DcaEmulator {
public:
    DcaEmulator() = delete;

    DcaEmulator(int argc, char *argv[]);

    ~DcaEmulator();

    bool init();

    bool run();

protected:

    bool readInputFile(const std::string& pathToExec);

private:
    CLI *cli;

    int argc;
    char **argv;

    std::list<InstructionSet> instructions;
    Memory *memory;
    CPU *cpu;
};


#endif //DCAEMULATOR_DCAEMULATOR_H
