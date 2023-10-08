/**
 * @file realtime.h
 * All realtime or multi-component project-specific functions header file
 */
#ifndef _REALTIME_H
#define _REALTIME_H

/////////////////
//-- Include --//
/////////////////
#include <time.h>
#include "esp_log.h"
#include "nvs_flash.h"

#include "screen/screen_controller.h"
#include "utils/pwm_controller.h"
#include "utils/ntp_time.h"
#include "aws/aws_http.h"
#include "utils/wifi.h"
#include "ui/ui.h"

////////////////////////////////////
//-- Public function prototypes --//
////////////////////////////////////

/**
 * @brief This function will initialize the whole CAFS system including Wifi, Time, PWM, etc.
 */
void sys_initialize();

/**
 * @brief This is an event triggered by an interrupt when the user wakes the system
 * by either entering a passcode or using a fingerprint. It will run the sys_checkAccess
 * function when an entry request is submitted.
 */
void sys_entryEventISR();

/**
 * @brief Update current wifi state. Set wifi indicator and check signal, if the
 * signal is low, attempt to reconnect.
 */
void sys_updateWifiState();

/**
 * @brief This function will connect to AWS and check if the current user is allowed
 * entry or not. This includes checking the passcode if given, checking the fingerprint,
 * and checking the user’s permissions.
 * @param value Can be ID of fingerprint or the passcode as an integer
 */
void sys_checkAccess(int value);

/**
 * @brief Set the system to sleep mode
 */
void sys_systemSleep();

/**
 * @brief Wake the system if in sleep mode
 */
void sys_systemWake();

/**
 * @brief Wifi function to be used as the loop in a thread for wifi and time updates.
 * @param pvParamter: task parameter
 */
void sys_runWifiTask(void *pvParameter);

#endif /* _REALTIME_H */