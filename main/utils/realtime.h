/**
 * @file realtime.h
 * All realtime or multi-component project-specific functions header file
 */
#ifndef _REALTIME_H
#define _REALTIME_H

#include <time.h>
#include "esp_log.h"

#include "screen/screen_controller.h"
#include "utils/pwm_controller.h"
#include "utils/ntp_time.h"
#include "utils/wifi.h"
#include "ui/ui.h"

/**
 * @brief This is an event triggered by an interrupt when the user wakes the system
 * by either entering a passcode or using a fingerprint. It will run the checkAccess
 * function when an entry request is submitted.
 */
void entryEventISR();

/**
 * @brief Update current wifi state. Set wifi indicator and check signal, if the
 * signal is low, attempt to reconnect.
 */
void updateWifiState();

/**
 * @brief This function will connect to AWS and check if the current user is allowed
 * entry or not. This includes checking the passcode if given, checking the fingerprint,
 * and checking the user’s permissions.
 */
void checkAccess();

/**
 * @brief Set the system to sleep mode
 */
void systemSleep();

/**
 * @brief Wake the system if in sleep mode
 */
void systemWake();

/**
 * @brief Wifi function to be used as the loop in a thread for wifi and time updates.
 * @param pvParamter: task parameter
 */
void runWifiTask(void *pvParameter);

#endif /* _REALTIME_H */