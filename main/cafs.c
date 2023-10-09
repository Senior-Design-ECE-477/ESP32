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
SemaphoreHandle_t xInterruptSemaphore;

/////////////////////////////////////
//-- Private function prototypes --//
/////////////////////////////////////

/**
 * @brief Interrupt Service Routine handler function for the even an entry is requested.
 * This function is declared as IRAM_ATTR. This is an event triggered by an interrupt when
 * the user wakes the system by either entering a passcode or using a fingerprint. It will
 * run the cafs_checkAccess function when an entry request is submitted.
 * @param arg
 */
static void IRAM_ATTR _entryEventISR_handler(void *arg);

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

    // Setul's test setup
    // pin 32 is set to button input for ISR
    // pin 14 is for button input for aws call

    // esp_rom_gpio_pad_select_gpio(14);
    // gpio_set_direction(14, GPIO_MODE_INPUT);
    // esp_rom_gpio_pad_select_gpio(32);
    // gpio_set_direction(32, GPIO_MODE_INPUT);

    // gpio_set_intr_type(32, GPIO_INTR_POSEDGE);
    // gpio_install_isr_service(ESP_INTR_FLAG_IRAM);
    // gpio_isr_handler_add(32, _entryEventISR_handler, NULL);
}

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

    char *api_result = aws_verify_user(value);
    ESP_LOGI(TAG, "API RESULT: %s", api_result);

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
    (void)pvParameter;
    xInterruptSemaphore = xSemaphoreCreateBinary();

    ESP_LOGI(TAG, "Main task started");

    uint16_t count = 0;
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(CAFS_DELAY_TICKS * portTICK_PERIOD_MS)); // Delay of 1 tick = 10ms = 1000ms / 10ms = 100 calls/s
        if (count >= 500)                                                 // Every 10ms * 500 = 5000ms
        {
            cafs_updateWifiState();            // Update wifi info
            struct tm time_now = getTime();    // Get datetime
            ui_UpdateDateTime(time_now, true); // Update datetime on UI
            count = 0;
        }
        else
        {
            count++;
        }

        if (pdTRUE == xSemaphoreTake(xInterruptSemaphore, 0))
        {
            // do interuppt stuff
            ESP_LOGW(TAG, "ISR: Method not implemented");
        }

        // Setul's test setup

        // if (gpio_get_level(14) == 1)
        // {
        //     cafs_checkAccess(0);
        // }
    }

    vTaskDelete(NULL);
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
    lv_color_t *buf2 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf2 != NULL);

    static lv_disp_buf_t disp_buf;
    uint32_t size_in_px = DISP_BUF_SIZE;

    /* Initialize the working buffer. */
    lv_disp_buf_init(&disp_buf, buf1, buf2, size_in_px);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;

#if defined CONFIG_DISPLAY_ORIENTATION_PORTRAIT || defined CONFIG_DISPLAY_ORIENTATION_PORTRAIT_INVERTED
    disp_drv.rotated = 1;
#endif

    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

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
    ESP_LOGI(TAG, "UI initialized");

    // Start loop
    ESP_LOGI(TAG, "Starting screen loop");
    while (1)
    {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(portTICK_PERIOD_MS));

        /* Try to take the semaphore, call lvgl related function on success */
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
        {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
        }
    }

    /* A task should NEVER return */
    free(buf1);
    free(buf2);
    vTaskDelete(NULL);
}

///////////////////////////
//-- Private functions --//
///////////////////////////

void _entryEventISR_handler(void *arg)
{
    xSemaphoreGiveFromISR(xInterruptSemaphore, NULL);
}

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
