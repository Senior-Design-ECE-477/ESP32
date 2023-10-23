/**
 * @file system.c
 * All system or multi-component project-specific functions C implementation file
 */

/////////////////
//-- Include --//
/////////////////
#include "cafs.h"

///////////////////
//-- Varaibles --//
///////////////////
static const char *TAG = "cafs";
SemaphoreHandle_t xGuiSemaphore;

/////////////////////////////////////
//-- Private function prototypes --//
/////////////////////////////////////

/**
 * @brief This function is run when access is granted to the user.
 * Status and user data on AWS will be updated, the lock unlocked, and
 * the screen shows the welcome animation.
 * @param username The name of the user that was granted access
 */
static void _accessGranted(char *username);
/**
 * @brief This function is run when access is not granted to the user.
 * User data on AWS will be updated and the screen shows the shake animation.
 */
static void _accessDenied();

/**
 * @brief This function is a ticker function for lvgl
 */
static void _ticker(void *arg);

//////////////////////////
//-- Public functions --//
//////////////////////////

void cafs_init()
{
    nvs_flash_init();        // Setup non-volatile flash
    initialize_wifi();       // Setup wifi
    initialize_sntp();       // Setup time server
    pwm_ControllerInit();    // Setup pwm
    pwm_ControllerSet(0.95); // Start with dimmed pwm
    init_uart();
    // esp_rom_gpio_pad_select_gpio(13);
    // gpio_set_direction(13, GPIO_MODE_OUTPUT);
    // gpio_set_level(13, 1);
    // esp_rom_gpio_pad_select_gpio(14);
    // gpio_set_direction(14, GPIO_MODE_INPUT);
    // esp_rom_gpio_pad_select_gpio(32);
    gpio_set_direction(FINGER_TOUCHIC_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(FINGER_TOUCHIC_PIN, GPIO_PULLDOWN_ONLY);
    gpio_set_direction(FINGER_ENROLL_PIN, GPIO_MODE_INPUT);

    esp_sleep_enable_ext0_wakeup(FINGER_TOUCHIC_PIN, 1);
}

void cafs_entryEventISR() {}
// Sleep modes:
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html
void cafs_systemSleep() { pwm_ControllerSet(0.05); }
void cafs_systemWake() { pwm_ControllerSet(1); }

void cafs_updateWifiState()
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

void cafs_checkAccess(int value)
{
    regex_t regex;
    int return_value;

    if(value == -1) {
        ESP_LOGE(TAG, "Invalid ID");
        return;
    }

    char *api_result = aws_verify_user(value);
    return_value = regcomp(&regex, "UNLOCKED", 0);
    return_value = regexec(&regex, api_result, 0, NULL, 0);
    regfree(&regex);

    if (return_value == 0)
    {
        _accessGranted("Setul");
    }
    else
    {
        _accessDenied();
    }
}

void cafs_runMainTask(void *pvParameter)
{
    ESP_LOGI(TAG, "Main task started");
    uint8_t count = 0; // Max number of 256
    int id = 3;
<<<<<<< HEAD

    while (1)
    {
=======
    int sleepTimer = 0;
    while (1)
    {
        
>>>>>>> 508bfaf (new stuff)
        vTaskDelay(pdMS_TO_TICKS(20)); // Delay between checks
        if (count >= 250)              // Every 20ms * 250 = 5000ms
        {
            cafs_updateWifiState();            // Update wifi info
            struct tm time_now = getTime();    // Get datetime
            ui_UpdateDateTime(time_now, true); // Update datetime on UI
            count = 0;
<<<<<<< HEAD
=======
            sleepTimer ++;

            if(sleepTimer >= 2){
                ESP_LOGI(TAG, "Going to sleep");
                pwm_ControllerSet(0.05);
                vTaskDelay(pdMS_TO_TICKS(200));
                esp_light_sleep_start();     
                sleepTimer = 0;
            }
            pwm_ControllerSet(0.95);
            // static const char *DAY_OF_WEEK[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
            // static const char *MONTH[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
            
            // printf("%d %d %d ", time_now.tm_hour, time_now.tm_min, time_now.tm_sec);
            // printf(DAY_OF_WEEK[time_now.tm_wday]);
            // printf(" %d ", time_now.tm_mday);
            // printf(MONTH[time_now.tm_mon]);
            // printf(" %d\n", time_now.tm_year + 1900);
>>>>>>> 508bfaf (new stuff)
        }
        else
        {
            count++;
        }
<<<<<<< HEAD
        // Setul's test setup
        if (gpio_get_level(34) == 1)
        {
=======
        
        // if (gpio_get_level(FINGER_ENROLL_PIN) == 1)
        // {
            // led_light_on();
            // vTaskDelay(100 / portTICK_PERIOD_MS);
            // printf("Fingerprint ID: %d\n", enroll_finger());
            // led_light_off();
        // }
        if(gpio_get_level(FINGER_TOUCHIC_PIN) == 1){
>>>>>>> 508bfaf (new stuff)
            led_light_on();
            id = identify_finger();
            printf("ID:  %d\n", id);
            led_light_off();
            cafs_checkAccess(id);
        }
<<<<<<< HEAD
        if(gpio_get_level(38) == 0){
            led_light_on();
            vTaskDelay(100 / portTICK_PERIOD_MS);
            printf("Fingerprint ID: %d\n", enroll_finger());
            led_light_off();
        }
=======
    
>>>>>>> 508bfaf (new stuff)
        // if (gpio_get_level(32) == 1)
        // {
        //     ui_ShowKeypad_Animation(0);
        //     vTaskDelay(pdMS_TO_TICKS(2000));
        //     ui_KeypadToWelcome_Animation(10);
        // }
    }
<<<<<<< HEAD

    vTaskDelete(NULL);
=======
    //vTaskDelete(NULL);
>>>>>>> 508bfaf (new stuff)
}

void cafs_runScreenGUI(void *pvParameter)
{
    (void)pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    ESP_LOGI(TAG, "LCD task started");

    lv_init();

    /* Initialize SPI or I2C bus used by the drivers */
    lvgl_driver_init();

    lv_color_t *buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1 != NULL);

    /* Use double buffered when not working with monochrome displays */
    // #ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    lv_color_t *buf2 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf2 != NULL);
    // #else
    //     static lv_color_t *buf2 = NULL;
    // #endif

    static lv_disp_buf_t disp_buf;

    uint32_t size_in_px = DISP_BUF_SIZE;

    // #if defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_IL3820 || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_JD79653A || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_UC8151D || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_SSD1306

    //     /* Actual size in pixels, not bytes. */
    //     size_in_px *= 8;
    // #endif

    /* Initialize the working buffer depending on the selected display.
     * NOTE: buf2 == NULL when using monochrome displays. */
    lv_disp_buf_init(&disp_buf, buf1, buf2, size_in_px);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;

#if defined CONFIG_DISPLAY_ORIENTATION_PORTRAIT || defined CONFIG_DISPLAY_ORIENTATION_PORTRAIT_INVERTED
    disp_drv.rotated = 1;
#endif

    /* When using a monochrome display we need to register the callbacks:
     * - rounder_cb
     * - set_px_cb */
    // #ifdef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    //     disp_drv.rounder_cb = disp_driver_rounder;
    //     disp_drv.set_px_cb = disp_driver_set_px;
    // #endif

    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    //     /* Register an input device when enabled on the menuconfig */
    // #if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
    //     lv_indev_drv_t indev_drv;
    //     lv_indev_drv_init(&indev_drv);
    //     indev_drv.read_cb = touch_driver_read;
    //     indev_drv.type = LV_INDEV_TYPE_POINTER;
    //     lv_indev_drv_register(&indev_drv);
    // #endif

    ESP_LOGI(TAG, "Drivers and buffers initialized");
    /* Create and start a periodic timer interrupt to call lv_tick_inc */
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &_ticker,
        .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));
    ESP_LOGI(TAG, "Timer initialized");

    /* Create the UI */
    ui_init();
    // lv_demo_widgets();
    ESP_LOGI(TAG, "UI initialized");

    // Start loop
    ESP_LOGI(TAG, "Starting screen loop");
    while (1)
    {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Try to take the semaphore, call lvgl related function on success */
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
        {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
        }
    }

    /* A task should NEVER return */
    free(buf1);
    // #ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    free(buf2);
    // #endif
    vTaskDelete(NULL);
}

///////////////////////////
//-- Private functions --//
///////////////////////////

void _accessGranted(char *username)
{
    ui_Unlock();
    ui_setName(username);
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

void _ticker(void *arg)
{
    (void)arg;
    lv_tick_inc(LV_TICK_PERIOD_MS);
}
