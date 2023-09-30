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
 * Private function prototypes
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
void updateWifiState()
{
    wifi_ap_record_t wifi_info;
    esp_err_t connected = esp_wifi_sta_get_ap_info(&wifi_info);

    if (connected == ESP_OK)
    {
        // Very low signal, attempt to reconnect
        if (wifi_info.rssi < -90)
        {
            ui_SetWifiBarNumber(NoBars);
            esp_wifi_disconnect();           // Disconnect
            vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for disconnection
            esp_wifi_connect();              // Reconnect
        }
        // Low signal, one bar
        else if (wifi_info.rssi < -75)
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
    }
    else
    {
        esp_wifi_connect();
    }
}
void checkAccess() {}

/**
 * Private function implementations
 */
void _accessGranted()
{
    ui_Unlock();
    ui_Welcome_Animation(500);
}
void _accessDenied()
{
    ui_Lock();
    ui_ShakeLock_Animation(0);
}
