//
// Created by Daniel Hammerl on 15.11.22.
//

#ifndef DCAEMULATOR_CONSTANTS_H
#define DCAEMULATOR_CONSTANTS_H

#include <cstdint>
#include "base.h"

namespace dca {
    namespace Register {
        const uint16_t RPC = 1, R00 = 2, R01 = 3, R02 = 4, R03 = 5, R04 = 6, R05 = 7,
                R06 = 8, R07 = 9, R08 = 10, R09 = 11, R10 = 12, RSP = 32;
    }

    namespace Instructions {
        const uint8_t LOAD = 1, STORE = 2, SET = 3, LOADH = 4, STOREH = 5, ADD = 6,
                SUB = 7, CJUMP = 8, MOV = 9, CJUMPI = 10;
    }

    namespace Gpu {
        const int GPU_MEMORY_ADDRESS_OFFSET = 65280;

        namespace Instructions {
            const uint8_t NOOP = 0, CLEAR = 1, BUFFER = 2, DRAW = 3;
        }
    }

    namespace Memory {
        const int MEMORY_MAX_LENGTH = 65536;
    }
}
#endif //DCAEMULATOR_CONSTANTS_H
