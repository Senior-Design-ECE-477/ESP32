
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "screen/screen_controller.h"
#include "utils/pwm_controller.h"
#include "utils/ntp_time.h"
#include "utils/wifi.h"
#include "ui/ui.h"

/**********************
 *   APPLICATION MAIN
 **********************/

void app_main()
{
    /* If you want to use a task to create the graphic, you NEED to create a Pinned task
     * Otherwise there can be problem such as memory corruption and so on.
     * NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0 */

    /**
     * Setup and Start LCD
     */
    // Start LCD
    xTaskCreatePinnedToCore(runScreenGUI, "gui", 4096 * 2, NULL, 0, NULL, 1);
    pwmControllerInit();    // Setup pwm
    pwmControllerSet(0.05); // Start with dimmed pwm

    /**
     * Setup and Start Wifi, along with Time
     */
    initialize_wifi();  // Setup wifi
    nvs_flash_init();   // Setup non-volatile flash
    esp_wifi_connect(); // Connect to wifi
    initialize_sntp();  // Setup time server
    update_time();      // Get time
    wifi_ap_record_t wifi_info;

    connected = esp_wifi_sta_get_ap_info(&wifi_info);

    if (connected == ESP_OK)
    {
        if (wifi_info.rssi < -90)
        {

            ESP_LOGI("WEAK WIFI", "Weak Wi-Fi signal. Reconnecting...");

            esp_wifi_disconnect();

            vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for disconnection

            esp_wifi_connect();
        }
    }
    else
    {

        esp_wifi_connect();
    }
}
