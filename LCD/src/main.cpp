/**
 * @file main.cpp
 * Main file, runs setup and then runs app
 */
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "screen.h"

#define POWER_LED_PIN 13


ScreenController screen;

extern "C" void app_main() {
    // Power LED
    esp_rom_gpio_pad_select_gpio(POWER_LED_PIN);
    gpio_set_direction((gpio_num_t)POWER_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)POWER_LED_PIN, 1);

    // Screen
    screen.home();
}