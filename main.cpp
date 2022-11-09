#include "src/DcaEmulator.h"

int main(int argc, char *argv[]) {

    auto *emulator = new DcaEmulator(argc, argv);

    return emulator->init() && emulator->run() ? 0 : 1;
}
