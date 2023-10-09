
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "cafs.h"

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
    cafs_init();

    /**
     * Start tasks
     */
    xTaskCreatePinnedToCore(cafs_runMainTask, "maintask", 4096 * 2, NULL, 0, NULL, 0);
    xTaskCreatePinnedToCore(cafs_runScreenGUI, "guitask", 4096 * 2, NULL, 0, NULL, 1);
}
