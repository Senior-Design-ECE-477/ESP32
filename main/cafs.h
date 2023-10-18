/**
 * @file cafs.h
 * All system or multi-component project-specific functions header file
 */
#ifndef _CAFS_H
#define _CAFS_H

/////////////////
//-- Include --//
/////////////////
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_freertos_hooks.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "utils/pwm_controller.h"
#include "utils/ntp_time.h"
#include "aws/aws_http.h"
#include "utils/motor.h"
#include "utils/wifi.h"
#include "ui/ui.h"

/* lvgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "lvgl_helpers.h"

////////////////
//-- Define --//
////////////////
#define LV_TICK_PERIOD_MS 1
#define CAFS_DELAY_TICKS 1 // 1 tick = portTICK_PERIOD_MS = 10ms

////////////////////////////////////
//-- Public function prototypes --//
////////////////////////////////////

/**
 * @brief This function will initialize the whole CAFS system including Wifi, Time, PWM, etc.
 */
void cafs_init();

/**
 * @brief Update current wifi state. Set wifi indicator and check signal, if the
 * signal is low, attempt to reconnect.
 */
void cafs_update_wifi();

/**
 * @brief This function will connect to AWS and check if the current user is allowed
 * entry or not. This includes checking the passcode if given, checking the fingerprint,
 * and checking the user’s permissions.
 * @param value Can be ID of fingerprint or the passcode as an integer
 */
void cafs_check_access(int value);

/**
 * @brief Set the system to sleep mode
 */
void cafs_sleep();

/**
 * @brief Wake the system if in sleep mode
 */
void cafs_wake();

/**
 * @brief Main thread function to be used as the loop in a thread for wifi, keypad, ui, and time updates.
 * @param pvParamter: task parameter
 */
void cafs_main_task(void *pvParameter);

/**
 * @brief Start LVGL, init drivers, and init UI. Then start the loop for the screen.
 * @param pvParamter: task parameter
 */
void cafs_gui_task(void *pvParameter);

#endif /* _REALTIME_H */