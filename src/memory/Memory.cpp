//
// Created by Daniel Hammerl on 10.11.22.
//

#include "Memory.h"
#include <algorithm>

Memory::Memory(char* defaultData, int defaultDataLength) {
    std::fill(std::begin(memoryData), std::end(memoryData), 0);
    for (int x = 0; x < defaultDataLength; x++) {
        memoryData[x] = defaultData[x];
    }
}


void Memory::setByte(unsigned int index, uint8_t data) {
    memoryData[index] = data;
}

void Memory::setHalfWord(unsigned int index, uint16_t value) {
    uint8_t low = *((unsigned char *) &value);
    uint8_t high = *(((unsigned char *) &value) + 1);
    setByte(index, high);
    setByte(index + 1, low);
}

const uint8_t &Memory::getByte(unsigned int index) {
    return memoryData[index];
}

const uint16_t Memory::getHalfWord(unsigned int index) {
    return getByte(index + 1) | getByte(index) << 8;
}
