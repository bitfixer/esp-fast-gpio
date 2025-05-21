#include "esp-fast-gpio.h"

namespace EspFastGpio {

gpio_hal_context_t _gpio_hal = {
    .dev = GPIO_HAL_GET_HW(GPIO_PORT_0)
};

gpio_dev_t* dev = GPIO_HAL_GET_HW(GPIO_PORT_0);

volatile uint32_t* gpio_low_set_reg = &(dev->out_w1ts);
volatile uint32_t* gpio_low_clear_reg = &(dev->out_w1tc);
volatile uint32_t* gpio_low_enable_set_reg = &(dev->enable_w1ts);
volatile uint32_t* gpio_low_enable_clear_reg = &(dev->enable_w1tc);
volatile uint32_t* gpio_low_in = &(dev->in);

uint32_t gpio_masks[32];

void init() {
    // initialize gpio masks
    for (int i = 0; i < 32; i++) {
        gpio_masks[i] = 1<<i;
    }
}

}