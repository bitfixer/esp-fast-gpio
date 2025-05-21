// esp-fast-gpio
// faster gpio pin operations on esp32 family

#pragma once
#include <inttypes.h>

namespace EspFastGpio {
    void init();
    void setInput(int pin);
    void setOutput(int pin);
    void setHigh(int pin);
    void setLow(int pin);
    uint32_t get(int pin);
}