//
// Created by Daniel Hammerl on 10.11.22.
//

#ifndef DCAEMULATOR_REGISTER_H
#define DCAEMULATOR_REGISTER_H

#include <cstdint>

class Register {
public:
    Register() = delete;

    explicit Register(uint16_t code);

    [[nodiscard]] const uint16_t getCode() const;

    [[nodiscard]] const uint16_t getValue() const;
    void setValue(uint16_t newValue);

private:
    uint16_t code;
    uint16_t value = 0;
};


#endif //DCAEMULATOR_REGISTER_H
