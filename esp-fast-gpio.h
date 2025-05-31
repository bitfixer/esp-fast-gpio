// esp-fast-gpio
// faster gpio pin operations on esp32 family

#pragma once
#include <inttypes.h>
#include <hal/gpio_hal.h>
#include <driver/gpio.h>

extern gpio_hal_context_t _gpio_hal;
extern gpio_dev_t *dev;

extern volatile uint32_t* gpio_low_set_reg;
extern volatile uint32_t* gpio_low_clear_reg;
extern volatile uint32_t* gpio_low_enable_set_reg;
extern volatile uint32_t* gpio_low_enable_clear_reg;
extern volatile uint32_t* gpio_low_in;

extern volatile uint32_t* gpio_high_set_reg;
extern volatile uint32_t* gpio_high_clear_reg;
extern volatile uint32_t* gpio_high_enable_set_reg;
extern volatile uint32_t* gpio_high_enable_clear_reg;
extern volatile uint32_t* gpio_high_in;

extern uint32_t gpio_masks[32];

#define fast_gpio_set_input(pin) \
    (*gpio_low_enable_clear_reg = gpio_masks[(pin)])

#define fast_gpio_set_input_mask(mask) \
    (*gpio_low_enable_clear_reg = (mask))

#define fast_gpio_set_input_mask_high(mask) \
    (*gpio_high_enable_clear_reg = (mask))

#define fast_gpio_set_input_high(pin) \
    (*gpio_high_enable_clear_reg = gpio_masks[(pin)])

#define fast_gpio_set_output(pin) \
    (*gpio_low_enable_set_reg = gpio_masks[(pin)])

#define fast_gpio_set_output_high(pin) \
    (*gpio_high_enable_set_reg = gpio_masks[(pin)])

#define fast_gpio_set_output_mask(mask) \
    (*gpio_low_enable_set_reg = (mask))

#define fast_gpio_set_output_mask_high(mask) \
    (*gpio_high_enable_set_reg = (mask))

//#ifdef CONFIG_IDF_TARGET_ESP32
#if 1
#define fast_gpio_set_high(pin) \
    (*gpio_low_set_reg = gpio_masks[(pin)])

#define fast_gpio_set_low(pin) \
    (*gpio_low_clear_reg = gpio_masks[(pin)])

#define fast_gpio_get(pin) \
    (((*gpio_low_in) >> (pin)) & 0x1)

#define fast_gpio_get_high(pin) \
    (((*gpio_high_in) >> (pin)) & 0x1)
#else
#define fast_gpio_set_high(pin) \
    gpio_set_level((gpio_num_t)pin, 1)

#define fast_gpio_set_low(pin) \
    gpio_set_level((gpio_num_t)pin, 0)

#define fast_gpio_get(pin) \
    gpio_get_level((gpio_num_t)pin)

#define fast_gpio_get_high(pin) \
    gpio_get_level((gpio_num_t)pin)

#endif



#define fast_gpio_write_byte(byte, offset) {                        \
    *gpio_low_set_reg = ((uint32_t)(byte)) << (offset);            \
    *gpio_low_clear_reg = ((uint32_t)(~(byte))) << (offset);       \
}

#define fast_gpio_write_mask(val, mask) {                           \
    *gpio_low_set_reg = (val);                                     \
    *gpio_low_clear_reg = (~(val)) & (mask);                       \
}

#define fast_gpio_write_mask_high(val, mask) {                      \
    *gpio_high_set_reg = (val);                                    \
    *gpio_high_clear_reg = (~(val)) & (mask);                      \
}

#define fast_gpio_read_byte(offset) \
    ((uint8_t)((*gpio_low_in >> (offset)) & 0xFF))

#define fast_gpio_read_mask() \
    (*gpio_low_in)

#define fast_gpio_read_mask_high() \
    (*gpio_high_in)

namespace EspFastGpio {

    void init();
    
    static inline void setInput(int pin) {
        *gpio_low_enable_clear_reg = gpio_masks[pin];
    }

    static inline void setInputMask(uint32_t mask) {
        *gpio_low_enable_clear_reg = mask;
    }

    static inline void setInputMaskHigh(uint32_t mask) {
        *gpio_high_enable_clear_reg = mask;
    }

    static inline void setInputHigh(int pin) {
        *gpio_high_enable_clear_reg = gpio_masks[pin];
    }

    static inline void setOutput(int pin) {
        *gpio_low_enable_set_reg = gpio_masks[pin];
    }

    static inline void setOutputHigh(int pin) {
        *gpio_high_enable_set_reg = gpio_masks[pin];
    }

    static inline void setOutputMask(uint32_t mask) {
        *gpio_low_enable_set_reg = mask;
    }

    static inline void setOutputMaskHigh(uint32_t mask) {
        *gpio_high_enable_set_reg = mask;
    }

    static inline void setHigh(int pin) {
        *gpio_low_set_reg = gpio_masks[pin];
    }

    static inline void setLow(int pin) {
        *gpio_low_clear_reg = gpio_masks[pin];
    }

    static inline uint32_t get(int pin) {
        return (*gpio_low_in >> pin) & 0x1;
    }

    static inline uint32_t get_high(int pin) {
        return (*gpio_high_in >> pin) & 0x1;
    }

    static inline void writeByte(uint8_t byte, int offset) {
        *gpio_low_set_reg = (uint32_t)byte << offset;
        *gpio_low_clear_reg = (uint32_t)(~byte) << offset;
    }

    static inline void writeMask(uint32_t val, uint32_t mask) {
        *gpio_low_set_reg = val;
        *gpio_low_clear_reg = (~val) & mask;
    }

    static inline void writeMaskHigh(uint32_t val, uint32_t mask) {
        *gpio_high_set_reg = val;
        *gpio_high_clear_reg = (~val) & mask;
    }

    static inline uint8_t readByte(int offset) {
        return (uint8_t)(*gpio_low_in >> offset) & 0xFF;
    }

    static inline uint32_t readMask() {
        return *gpio_low_in;
    }

    static inline uint32_t readMaskHigh() {
        return *gpio_high_in;
    }
}