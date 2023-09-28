
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

    // Start LCD and backlight PWM
    xTaskCreatePinnedToCore(runScreenGUI, "gui", 4096 * 2, NULL, 0, NULL, 1);
    pwmControllerInit();
    pwmControllerSet(0.05); // PWM signal for dimmed mode
    vTaskDelay(pdMS_TO_TICKS(5000));
    pwmControllerSet(1); // PWM signal for bright mode
    ui_ShakeLock_Animation(0);
    vTaskDelay(pdMS_TO_TICKS(1000));
    ui_Unlock();
    ui_Welcome_Animation(500);
    vTaskDelay(pdMS_TO_TICKS(6000));
    ui_Lock();
    ui_ShowKeypad_Animation(0);
    ui_ShakeKeypad_Animation(1000);
}
