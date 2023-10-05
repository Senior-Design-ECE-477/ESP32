
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "screen/screen_controller.h"
#include "utils/pwm_controller.h"
#include "utils/ntp_time.h"
#include "utils/wifi.h"
// #include "ui/ui.h"
#include "utils/realtime.h"
#include "nvs_flash.h"

/**********************
 *   APPLICATION MAIN
 **********************/

void app_main()
{
    /* If you want to use a task to create the graphic, you NEED to create a Pinned task
     * Otherwise there can be problem such as memory corruption and so on.
     * NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0 */

    /**
     * Initialize all tools
     */
    nvs_flash_init();       // Setup non-volatile flash
    initialize_wifi();      // Setup wifi
    initialize_sntp();      // Setup time server
    pwmControllerInit();    // Setup pwm
    pwmControllerSet(0.05); // Start with dimmed pwm

    /**
     * Start tasks
     */
    xTaskCreatePinnedToCore(runWifiTask, "wifi", 4096 * 2, NULL, 0, NULL, 0);
    xTaskCreatePinnedToCore(runScreenGUI, "gui", 4096 * 2, NULL, 0, NULL, 1);
}
