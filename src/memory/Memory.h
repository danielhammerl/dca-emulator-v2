//
// Created by Daniel Hammerl on 10.11.22.
//

#ifndef DCAEMULATOR_MEMORY_H
#define DCAEMULATOR_MEMORY_H

#include <cstdint>

class Memory {
public:
    explicit Memory(char* defaultData, int defaultDataLength);
    void setByte(unsigned int index, uint8_t data);

    void setHalfWord(unsigned int index, uint16_t value);

    [[nodiscard]] const uint8_t &getByte(unsigned int index);

    [[nodiscard]] const uint16_t getHalfWord(unsigned int index);

private:
    uint8_t memoryData[65536];
};


#endif //DCAEMULATOR_MEMORY_H
