//
// Created by Daniel Hammerl on 10.11.22.
//

#ifndef DCAEMULATOR_MEMORY_H
#define DCAEMULATOR_MEMORY_H

#include <cstdint>
#include "../constants.h"

class Memory {
public:
    explicit Memory(const char *defaultData, int defaultDataLength);

    void setByte(uint16_t index, uint8_t data);

    void setHalfWord(uint16_t index, uint16_t value);

    [[nodiscard]] const uint8_t &getByte(uint16_t index);

    [[nodiscard]] const uint16_t getHalfWord(uint16_t index);

private:
    uint8_t memoryData[dca::Memory::MEMORY_MAX_LENGTH];
};


#endif //DCAEMULATOR_MEMORY_H
