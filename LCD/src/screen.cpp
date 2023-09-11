/**
 * @file screen.cpp
 * ScreenController cpp file
 */

// -- Includes --

// #include <stdbool.h>
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
#include <esp_log.h>
#include <esp_timer.h>

// LVGL Settings then Include
#define TAG "screen"
#define LV_HOR_RES_MAX 320
#define LV_VER_RES_MAX 240
#define LV_LVGL_H_INCLUDE_SIMPLE

#include <lvgl.h>
#include "lv_port_disp.h"
#include "screen.h"
#include "ui/ui.h"

#define LV_TICK_PERIOD_MS 1


void lv_example_anim(void);

ScreenController::ScreenController(){

}

void ScreenController::start(void *pvParameter){
    SemaphoreHandle_t xGuiSemaphore;
    (void)pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    lv_init();

    lv_port_disp_init();


    // Setup timer system
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "lvgl_tick_inc",
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));


    ESP_LOGI(TAG, "display init done.");

    ui_init();

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

void ScreenController::lv_tick_task(void *arg) {
    (void) arg;
    lv_tick_inc(LV_TICK_PERIOD_MS);
}


static void anim_x_cb(void *var, int32_t v)
{
  lv_obj_set_x((_lv_obj_t *)var, v);
}

static void anim_size_cb(void *var, int32_t v)
{
  lv_obj_set_size((_lv_obj_t *)var, v, v);
}

/**
 * Create a playback animation
 */
void lv_example_anim(void)
{
  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, "Hello World!");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *obj = lv_obj_create(lv_scr_act());
  lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_RED), 0);
  lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, 0);

  lv_obj_align(obj, LV_ALIGN_LEFT_MID, 10, 0);

  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, obj);
  lv_anim_set_values(&a, 10, 50);
  lv_anim_set_time(&a, 1000);
  lv_anim_set_playback_delay(&a, 100);
  lv_anim_set_playback_time(&a, 300);
  lv_anim_set_repeat_delay(&a, 500);
  lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
  lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);

  lv_anim_set_exec_cb(&a, anim_size_cb);
  lv_anim_start(&a);
  lv_anim_set_exec_cb(&a, anim_x_cb);
  lv_anim_set_values(&a, 0, 190);
  lv_anim_start(&a);
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

