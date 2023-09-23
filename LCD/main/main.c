
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "screen/screen_controller.h"
#include "screen/pwm_controller.h"

/**********************
 *   APPLICATION MAIN
 **********************/

void app_main()
{
    // esp_rom_gpio_pad_select_gpio(LEFT_PWM_PIN);
    // gpio_set_direction(LED_PWM_PIN, GPIO_MODE_OUTPUT);

    /* If you want to use a task to create the graphic, you NEED to create a Pinned task
     * Otherwise there can be problem such as memory corruption and so on.
     * NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0 */

    // gpio_set_level(LED_PWM_PIN, 1);
    xTaskCreatePinnedToCore(runScreenGUI, "gui", 4096 * 2, NULL, 0, NULL, 1);
    pwmControllerInit();
    pwmControllerSet(0.05); // PWM signal for dimmed mode
    // pwmControllerSet(1);    // PWM signal for bright mode
}
