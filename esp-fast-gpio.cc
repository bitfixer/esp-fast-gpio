#include "esp-fast-gpio.h"

gpio_hal_context_t _gpio_hal = {
    .dev = GPIO_HAL_GET_HW(GPIO_PORT_0)
};

gpio_dev_t* dev = GPIO_HAL_GET_HW(GPIO_PORT_0);

volatile uint32_t* gpio_low_set_reg = &(dev->out_w1ts);
volatile uint32_t* gpio_low_clear_reg = &(dev->out_w1tc);
volatile uint32_t* gpio_low_enable_set_reg = &(dev->enable_w1ts);
volatile uint32_t* gpio_low_enable_clear_reg = &(dev->enable_w1tc);
volatile uint32_t* gpio_low_in = &(dev->in);

volatile uint32_t* gpio_high_set_reg = &(dev->out1_w1ts.val);
volatile uint32_t* gpio_high_clear_reg = &(dev->out1_w1tc.val);
volatile uint32_t* gpio_high_enable_set_reg = &(dev->enable1_w1ts.val);
volatile uint32_t* gpio_high_enable_clear_reg = &(dev->enable1_w1tc.val);
volatile uint32_t* gpio_high_in = &(dev->in1.val);

uint32_t gpio_masks[32];

namespace EspFastGpio {

void init() {
    // initialize gpio masks
    for (int i = 0; i < 32; i++) {
        gpio_masks[i] = 1<<i;
    }
}

}