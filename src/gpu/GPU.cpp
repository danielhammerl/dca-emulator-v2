//
// Created by Daniel Hammerl on 10.11.22.
//

#include "GPU.h"
#include "../constants.h"

GPU::GPU(Memory *memory) : memory(memory) {

    window = new sf::RenderWindow(sf::VideoMode(VIDEO_BUFFER_SIZE, VIDEO_BUFFER_SIZE, 32), "DCA Emulator v2",
                                  sf::Style::Titlebar);
    event = new sf::Event();

    image.create(VIDEO_BUFFER_SIZE, VIDEO_BUFFER_SIZE);

    window->pollEvent(*event);
}

GPU::~GPU() {
    delete window;
    delete event;
}

void GPU::tick() {
    auto gpuOpcode = memory->getByte(dca::Gpu::GPU_MEMORY_ADDRESS_OFFSET);
    switch (gpuOpcode) {
        case dca::Gpu::Instructions::NOOP:
            break;

        case dca::Gpu::Instructions::CLEAR:
            clearBuffer();
            break;

        case dca::Gpu::Instructions::BUFFER:
            draw(memory->getHalfWord(dca::Gpu::GPU_MEMORY_ADDRESS_OFFSET + 1),
                 memory->getHalfWord(dca::Gpu::GPU_MEMORY_ADDRESS_OFFSET + 3),
                 memory->getHalfWord(dca::Gpu::GPU_MEMORY_ADDRESS_OFFSET + 5));
            break;

        case dca::Gpu::Instructions::DRAW:
            displayBuffer();
            break;

        default:
            break;
    }
}

void GPU::clearBuffer() {
    image.create(VIDEO_BUFFER_SIZE, VIDEO_BUFFER_SIZE);
}

void GPU::displayBuffer() {
    window->clear();

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);

    window->draw(sprite);

    window->display();
}

void GPU::draw(uint16_t xPos, uint16_t yPos, uint16_t color) {
    image.setPixel(xPos, yPos, sf::Color(rgb16To32(color)));
}

