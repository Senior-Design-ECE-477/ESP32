/**
 * @file main.cpp
 * Main file, runs setup and then runs app
 */

// Example using LVGL in ESP-IDF project
// Tested on TTGO T-Display ESP32

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define LV_LVGL_H_INCLUDE_SIMPLE
#include "screen.h"

#define POWER_LED_PIN 13
#define SCREEN_RST_PIN 15
#define SCREEN_CS_PIN 4
#define SCREEN_DC_PIN 21
// MOSI_PIN 
// MISO_PIN
// SCK_PIN


ScreenController screen;


extern "C" void app_main() {
    
    /**
     * @brief Power LED
    */
    esp_rom_gpio_pad_select_gpio(POWER_LED_PIN);
    gpio_set_direction((gpio_num_t)POWER_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)POWER_LED_PIN, 1);

    /**
     * @brief Wifi
     * Start the wifi/cloud loop code on CPU core 0
    */

    /**
     * @brief Screen
     * Start the screen loop code on CPU core 1
    */
    xTaskCreatePinnedToCore(screen.start, "gui", 4096 * 2, NULL, 0, NULL, 1);

}