/**
 * @file screen.cpp
 * ScreenController cpp file
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_freertos_hooks.h>
#include <soc/gpio_sig_map.h>
#include <freertos/semphr.h>
#include <esp_system.h>
#include <driver/gpio.h>
#include <driver/spi_common.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <esp_timer.h>

// LVGL Settings then Include
#define TAG "screen"
#define LV_HOR_RES_MAX 240
#define LV_VER_RES_MAX 320
#define MY_DISP_HOR_RES 240
#define MY_DISP_VER_RES 320
#define LV_LVGL_H_INCLUDE_SIMPLE
#define LV_TICK_PERIOD_MS 1

#define CONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9341
#define CONFIG_LV_DISP_PIN_DC 15
#define CONFIG_LV_DISP_PIN_RST 4
#define CONFIG_LV_DISP_USE_RST 1
#define CONFIG_LV_PREDEFINED_DISPLAY_NONE

#include <lvgl.h>
// #include "lvgl_helpers.h"
#include "lv_port_disp.h"
#include "screen.h"
#include "drivers/ILI9341.h"
#include "ui/ui.h"


// #define 

SemaphoreHandle_t xGuiSemaphore;


ScreenController::ScreenController(){

}

void ScreenController::ticker(void *arg) {
    (void) arg;
    lv_tick_inc(LV_TICK_PERIOD_MS);
}

void ScreenController::start(void *pvParameter){
    (void)pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();





    // lvgl
    lv_init();
    // driver and buffer
    // ili9341_init();
    lv_port_disp_init();
    // lvgl_driver_init();


    // Setup timer system
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &ticker,
        .name = "lvgl_tick_inc",
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));
    ESP_LOGI(TAG, "display init done.");

    // start ui
    ui_init();

    // loop
    while (1)
    {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Try to take the semaphore, call lvgl related function on success */
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
        {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
        }
    }

    /* A task should NEVER return */
    // free(buf1);
    vTaskDelete(NULL);
}

void ScreenController::accepted(int ms){

}

void ScreenController::denied(int ms){

}

void ScreenController::home(){
    
}











// LVGL ScreenController::start

/*

(void) pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    lv_init();

    // Initialize SPI or I2C bus used by the drivers
    lvgl_driver_init();

    lv_coord_t* buf1 = (lv_coord_t *)heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_coord_t), MALLOC_CAP_DMA);
    assert(buf1 != NULL);

    // Use double buffered when not working with monochrome displays
    lv_coord_t* buf2 = (lv_coord_t *)heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_coord_t), MALLOC_CAP_DMA);
    assert(buf2 != NULL);

    static lv_draw_buf_t disp_buf;

    uint32_t size_in_px = DISP_BUF_SIZE;

    // Initialize the working buffer depending on the selected display.
    // NOTE: buf2 == NULL when using monochrome displays.
    lv_draw_buf_init(&disp_buf, *buf1, *buf2, size_in_px);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;

    disp_drv.rotated = 1;


    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);


    // Create and start a periodic timer interrupt to call lv_tick_inc
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    // Create the demo application
    //lv_demo_widgets();

    while (1) {
        // Delay 1 tick (assumes FreeRTOS tick is 10ms
        vTaskDelay(pdMS_TO_TICKS(10));

        // Try to take the semaphore, call lvgl related function on success 
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
       }
    }

    // A task should NEVER return
    free(buf1);
    free(buf2);
    vTaskDelete(NULL);
    
*/

