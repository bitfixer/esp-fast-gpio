#include "esp-fast-gpio.h"
#include <hal/gpio_hal.h>
#include <driver/gpio.h>

namespace EspFastGpio {

static gpio_hal_context_t _gpio_hal = {
    .dev = GPIO_HAL_GET_HW(GPIO_PORT_0)
};

static gpio_dev_t* dev = GPIO_HAL_GET_HW(GPIO_PORT_0);

static volatile uint32_t* gpio_low_set_reg = &(dev->out_w1ts);
static volatile uint32_t* gpio_low_clear_reg = &(dev->out_w1tc);
static volatile uint32_t* gpio_low_enable_set_reg = &(dev->enable_w1ts);
static volatile uint32_t* gpio_low_enable_clear_reg = &(dev->enable_w1tc);
static volatile uint32_t* gpio_low_in = &(dev->in);

static uint32_t gpio_masks[32];

void init() {
    // initialize gpio masks
    for (int i = 0; i < 32; i++) {
        gpio_masks[i] = 1<<i;
    }
}

void setInput(int pin) {
    *gpio_low_enable_clear_reg = gpio_masks[pin];
}

void setOutput(int pin) {
    *gpio_low_enable_set_reg = gpio_masks[pin];
}

void setHigh(int pin) {
    *gpio_low_set_reg = gpio_masks[pin];
}

void setLow(int pin) {
    *gpio_low_clear_reg = gpio_masks[pin];
}

uint32_t get(int pin) {
    return (*gpio_low_in >> pin) & 0x1;
}

}