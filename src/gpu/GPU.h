//
// Created by Daniel Hammerl on 10.11.22.
//

#ifndef DCAEMULATOR_GPU_H
#define DCAEMULATOR_GPU_H


#include "../memory/Memory.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class GPU {

public:
    explicit GPU(Memory *memory);

    ~GPU();

    void tick();

protected:
    void draw(uint16_t xPos, uint16_t yPos, uint16_t color);

    void clearBuffer();

    void displayBuffer();

private:
    Memory *memory;
    const int VIDEO_BUFFER_SIZE = 150;
    const int GPU_MEMORY_ADDRESS_OFFSET = 65280;

    sf::RenderWindow *window;
    sf::Event *event;
    sf::Image image;

    static uint32_t rgb16To32(uint16_t a) {
        unsigned long r = (a & 0xF800) >> 11;
        unsigned long g = (a & 0x07E0) >> 5;
        unsigned long b = (a & 0x001F);

        r = r * 255 / 31;
        g = g * 255 / 63;
        b = b * 255 / 31;

        return (r << 24) | (g << 16) | (b << 8) | 255;
    }
};


#endif //DCAEMULATOR_GPU_H
