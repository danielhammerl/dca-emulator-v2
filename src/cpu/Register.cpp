//
// Created by Daniel Hammerl on 10.11.22.
//

#include "Register.h"

Register::Register(uint16_t code) : code(code) {

}

const uint16_t Register::getCode() const {
    return this->code;
}

const uint16_t Register::getValue() const {
    return value;
}

void Register::setValue(uint16_t newValue) {
    this->value = newValue;
}
