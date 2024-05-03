//
// Created by Daniel Hammerl on 02.05.24.
//

#ifndef DCAEMULATOR_EMPTYGPU_H
#define DCAEMULATOR_EMPTYGPU_H

#include "GPU.h"

class EmptyGpu: public GPU {
public:
    explicit EmptyGpu(Memory *memory) {

    };

    ~EmptyGpu() = default;

    [[maybe_unused]] void tick() {

    };
};


#endif //DCAEMULATOR_EMPTYGPU_H
