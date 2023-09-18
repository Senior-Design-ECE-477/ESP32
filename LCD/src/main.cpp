/**
 * @file main.cpp
 * Main file, runs setup and then runs app
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define LV_LVGL_H_INCLUDE_SIMPLE
#include "screen_controller.h"
extern "C" {
    #include "spi_controller.h"
}

/***********************
 *  Pin Definitions   *
***********************/
#define POWER_LED_PIN GPIO_NUM_13
#define SCREEN_CS_PIN GPIO_NUM_26
#define SCREEN_RESET_PIN GPIO_NUM_12
#define SCREEN_DC_RS_PIN GPIO_NUM_4
#define SCREEN_MOSI_PIN GPIO_NUM_19
#define SCREEN_SCK_PIN GPIO_NUM_5
#define SCREEN_LED_PIN GPIO_NUM_33
#define SCREEN_MISO_PIN GPIO_NUM_21

/***********************
 * Screen Definitions *
***********************/
#define SCREEN_HOR_RES 240
#define SCREEN_VER_RES 320
#define SCREEN_FPS 24
#define SCREEN_CMD_BITS 8
#define SCREEN_PARAM_BITS 8

extern "C" void app_main() {
    /**
     * @brief Setup GPIO Pins
     * Set function (i.e. set to be gpio pin)
     * Set direction (i.e. set to output mode)
    */
    esp_rom_gpio_pad_select_gpio(POWER_LED_PIN);
    esp_rom_gpio_pad_select_gpio(SCREEN_CS_PIN);
    esp_rom_gpio_pad_select_gpio(SCREEN_RESET_PIN);
    esp_rom_gpio_pad_select_gpio(SCREEN_DC_RS_PIN);
    esp_rom_gpio_pad_select_gpio(SCREEN_LED_PIN);
    gpio_set_direction(POWER_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(SCREEN_CS_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(SCREEN_RESET_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(SCREEN_DC_RS_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(SCREEN_LED_PIN, GPIO_MODE_OUTPUT);

    /**
     * @brief Power LED
    */
    
    gpio_set_level(POWER_LED_PIN, 1);

    /**
     * @brief Wifi
     * Start the wifi loop code on CPU core 0
     */
    
    /**
     * @brief Screen
     * Start the screen loop code on CPU core 1
    */  
    // Turn on the lcd backlight (LED pin)
    // esp_rom_gpio_pad_select_gpio(SCREEN_LED_PIN);
    gpio_set_level(SCREEN_LED_PIN, 1);

    start_spi_bus_3_vspi();  // written in spi_controller.c
    // Start GUI
    ScreenController screen; // written in screen_controller.cpp
    xTaskCreatePinnedToCore(screen.start, "gui", 4096 * 2, NULL, 0, NULL, 1);

}