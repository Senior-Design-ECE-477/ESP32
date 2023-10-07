/**
 * @file screen_controller.h
 * ScreenController header file
 */
#ifndef _SCREEN_CONTROLLER_H
#define _SCREEN_CONTROLLER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "driver/gpio.h"
#include "esp_log.h"

/* lvgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "lvgl_helpers.h"

#include "ui/ui.h"

#define LV_TICK_PERIOD_MS 1

/**
 * @brief Start LVGL, init drivers, and init UI. Then start the loop for the screen.
 * @param pvParamter: task parameter
 */
void runScreenGUI(void *pvParameter);

#endif /* _SCREEN_CONTROLLER_H */