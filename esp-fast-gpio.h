// esp-fast-gpio
// faster gpio pin operations on esp32 family

#pragma once
#include <inttypes.h>
#include <hal/gpio_hal.h>
#include <driver/gpio.h>

namespace EspFastGpio {

    extern gpio_hal_context_t _gpio_hal;
    extern gpio_dev_t *dev;

    extern volatile uint32_t* gpio_low_set_reg;
    extern volatile uint32_t* gpio_low_clear_reg;
    extern volatile uint32_t* gpio_low_enable_set_reg;
    extern volatile uint32_t* gpio_low_enable_clear_reg;
    extern volatile uint32_t* gpio_low_in;
    extern uint32_t gpio_masks[32];

    void init();
    
    inline void setInput(int pin) {
        *gpio_low_enable_clear_reg = gpio_masks[pin];
    }

    inline void setOutput(int pin) {
        *gpio_low_enable_set_reg = gpio_masks[pin];
    }

    inline void setHigh(int pin) {
        *gpio_low_set_reg = gpio_masks[pin];
    }

    inline void setLow(int pin) {
        *gpio_low_clear_reg = gpio_masks[pin];
    }

    inline uint32_t get(int pin) {
        return (*gpio_low_in >> pin) & 0x1;
    }
}