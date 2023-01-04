//
// Created by Daniel Hammerl on 10.11.22.
//

#include "Register.h"

Register::Register(std::string &name) : name(name) {

}

uint16_t Register::getValue() const {
    return value;
}

void Register::setValue(uint16_t newValue) {
    this->value = newValue;
}

Register::Register(const char *name) : name(name) {

}

std::string Register::getName() const {
    return this->name;
}
