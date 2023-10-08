
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "screen/screen_controller.h"
#include "utils/system.h"

/**********************
 *   APPLICATION MAIN
 **********************/

void app_main()
{
    /* If you want to use a task to create the graphic, you NEED to create a Pinned task
     * Otherwise there can be problem such as memory corruption and so on.
     * NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0 */

    /**
     * Initialize
     */
    sys_initialize();

    /**
     * Start tasks
     */
    xTaskCreatePinnedToCore(sys_runWifiTask, "wifi", 4096 * 2, NULL, 0, NULL, 0);
    xTaskCreatePinnedToCore(sc_runScreenGUI, "gui", 4096 * 2, NULL, 0, NULL, 1);
}
