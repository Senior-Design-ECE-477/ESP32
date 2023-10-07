/**
 * @file realtime.c
 * All realtime or multi-component project-specific functions C implementation file
 */

#include "realtime.h"
static const char *TAG = "realtime";

/**
 * Private function prototypes
 */

/**
 * @brief This function is run when access is granted to the user.
 * Status and user data on AWS will be updated, the lock unlocked, and
 * the screen shows the welcome animation.
 */
static void _accessGranted();
/**
 * @brief This function is run when access is not granted to the user.
 * User data on AWS will be updated and the screen shows the shake animation.
 */
static void _accessDenied();

/**
 * Public functions
 */

void entryEventISR() {}
void runWifiTask(void *pvParameter)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000)); // Delay between checks
        updateWifiState();               // Update wifi info
        struct tm time_now = getTime();  // Get datetime
        ui_UpdateDateTime(time_now);     // Update datetime on UI
    }

    vTaskDelete(NULL);
}
void systemSleep() { pwmControllerSet(0.05); }
void systemWake() { pwmControllerSet(1); }
void updateWifiState()
{
    wifi_ap_record_t wifi_info = wifi_connect();
    // Low signal, one bar
    if (wifi_info.rssi < -75)
    {
        ui_SetWifiBarNumber(OneBar);
    }
    // Two bars
    else if (wifi_info.rssi < -50)
    {
        ui_SetWifiBarNumber(TwoBars);
    }
    // Three bars
    else if (wifi_info.rssi <= 0)
    {
        ui_SetWifiBarNumber(ThreeBars);
    }
    else
    {
        ui_SetWifiBarNumber(NoBars);
    }
}

void checkAccess()
{
    if (true)
    {
        _accessGranted();
    }
    else
    {
        _accessDenied();
    }
}

/**
 * Private function implementations
 */

static void _accessGranted()
{
    ui_Unlock();
    ui_Welcome_Animation(500);
}
static void _accessDenied()
{
    ui_Lock();
    ui_ShakeLock_Animation(0);
}
