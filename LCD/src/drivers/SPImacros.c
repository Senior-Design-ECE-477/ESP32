#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <driver/spi_common.h>
#include "SPImacros.h"

void delay_micro_sec(int us)
{
    vTaskDelay(pdMS_TO_TICKS(us / 1000));
}

void delay_milli_sec(int ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

void set_x_pin_to(int pin, int value)
{
    esp_rom_gpio_pad_select_gpio(pin);
    gpio_set_direction((gpio_num_t)pin, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)pin, value);
}

void spi_cs_pin_set(int value)
{
    set_x_pin_to(1, value);
}

void spi_write_screen_data(uint8_t data)
{
    // write data byte to spi bus
}

void spi_write_screen_memory(uint8_t *adr, uint16_t n)
{
    // write ( n ) number of bytes to spi bus starting from ( adr ) memory address
}
