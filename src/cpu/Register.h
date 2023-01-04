//
// Created by Daniel Hammerl on 10.11.22.
//

#ifndef DCAEMULATOR_REGISTER_H
#define DCAEMULATOR_REGISTER_H

#include <cstdint>
#include <string>

class Register {
public:
    explicit Register(std::string &name);
    explicit Register(const char* name);

    [[nodiscard]] uint16_t getValue() const;
    void setValue(uint16_t newValue);
    [[nodiscard]] std::string getName() const;

private:
    uint16_t value = 0;
    std::string name;
};


#endif //DCAEMULATOR_REGISTER_H
