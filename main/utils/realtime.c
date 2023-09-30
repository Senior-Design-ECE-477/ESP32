/**
 * @file realtime.c
 * All realtime or multi-component project-specific functions C implementation file
 */
#include "realtime.h"
#include "screen/screen_controller.h"
#include "utils/pwm_controller.h"
#include "utils/ntp_time.h"
#include "utils/wifi.h"
#include "ui/ui.h"

/**
 * Private functions prototype
 */
/**
 * @brief
 */
static void _accessGranted();
/**
 * @brief
 */
static void _accessDenied();

/**
 * Public functions
 */
void entryEventISR() {}
void runWifiTask()
{
    while (0)
    {
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay between checks
        update_time();                   // Get time
        updateWifiState();               // Update wifi info
    }

    vTaskDelete(NULL);
}
void systemSleep() { pwmControllerSet(0.05); }
void systemWake() { pwmControllerSet(1); }
void updateWifiState() {}
void checkAccess() {}

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
