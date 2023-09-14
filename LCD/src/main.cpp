/**
 * @file main.cpp
 * Main file, runs setup and then runs app
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define LV_LVGL_H_INCLUDE_SIMPLE
#include "screen.h"

/***********************
 *  Pin Definitions   *
***********************/
#define POWER_LED_PIN 13
#define SCREEN_CS_PIN 26
// #define SCREEN_RESET_PIN 12
#define SCREEN_DC_RS_PIN 4
#define SCREEN_MOSI_PIN 19
#define SCREEN_SCK_PIN 5
#define SCREEN_LED_PIN 33
#define SCREEN_MISO_PIN 21

/***********************
 * Screen Definitions *
***********************/
#define SCREEN_HOR_RES 240
#define SCREEN_VER_RES 320
#define SCREEN_FPS 24
#define SCREEN_CMD_BITS 8
#define SCREEN_PARAM_BITS 8

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
     * Start the wifi loop code on CPU core 0
     */
    
    /**
     * @brief Screen
     * Start the screen loop code on CPU core 1
    */  
    // Turn on the lcd backlight (LED pin)
    esp_rom_gpio_pad_select_gpio(SCREEN_LED_PIN);
    gpio_set_direction((gpio_num_t)SCREEN_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)SCREEN_LED_PIN, 1);
    // Start GUI
    xTaskCreatePinnedToCore(screen.start, "gui", 4096 * 2, NULL, 0, NULL, 1);

}