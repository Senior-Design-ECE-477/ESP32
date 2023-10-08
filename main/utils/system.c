/**
 * @file system.c
 * All system or multi-component project-specific functions C implementation file
 */

/////////////////
//-- Include --//
/////////////////
#include "system.h"

///////////////////
//-- Varaibles --//
///////////////////
static const char *TAG = "system";

/////////////////////////////////////
//-- Private function prototypes --//
/////////////////////////////////////

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

//////////////////////////
//-- Public functions --//
//////////////////////////

void sys_initialize()
{
    nvs_flash_init();        // Setup non-volatile flash
    initialize_wifi();       // Setup wifi
    initialize_sntp();       // Setup time server
    pwm_ControllerInit();    // Setup pwm
    pwm_ControllerSet(0.05); // Start with dimmed pwm
}

void sys_entryEventISR() {}
void sys_runWifiTask(void *pvParameter)
{
    ESP_LOGI(TAG, "Wifi task started");
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));   // Delay between checks
        sys_updateWifiState();             // Update wifi info
        struct tm time_now = getTime();    // Get datetime
        ui_UpdateDateTime(time_now, true); // Update datetime on UI
    }

    vTaskDelete(NULL);
}
// Sleep modes:
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html
void sys_systemSleep() { pwm_ControllerSet(0.05); }
void sys_systemWake() { pwm_ControllerSet(1); }

void sys_updateWifiState()
{
    wifi_ap_record_t wifi_info = wifi_connect();
    // Low signal, one bar
    if ((wifi_info.rssi < -75) & (wifi_info.rssi > -91))
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

void sys_checkAccess(int value)
{
    regex_t regex;
    int return_value;

    char *api_result = aws_verify_user(value);

    return_value = regcomp(&regex, "UNLOCKED", 0);
    return_value = regexec(&regex, api_result, 0, NULL, 0);
    regfree(&regex);

    if (return_value == 0)
    {
        _accessGranted();
    }
    else
    {
        _accessDenied();
    }
}

///////////////////////////
//-- Private functions --//
///////////////////////////

void _accessGranted()
{
    ui_Unlock();
    ui_Welcome_Animation(500);

    // if motor not unlocked...
    ESP_LOGI("MOTOR", "UNLOCK");
    motor_unlock();
    vTaskDelay(pdMS_TO_TICKS(3000));
    motor_off();
    ESP_LOGI("MOTOR", "OFF");
}

void _accessDenied()
{
    ui_Lock();
    ui_ShakeLock_Animation(0);

    // if motor not locked...
    ESP_LOGI("MOTOR", "LOCKING");
    motor_lock();
    vTaskDelay(pdMS_TO_TICKS(3000));
    ESP_LOGI("MOTOR", "OFF");
    motor_off();
}
