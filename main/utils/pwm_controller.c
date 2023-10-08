/**
 * @file pwm_controller.c
 * LED PWM controller implementation file
 */

/////////////////
//-- Include --//
/////////////////
#include "pwm_controller.h"

///////////////////
//-- Varaibles --//
///////////////////
static const char *TAG = "pwm";

//////////////////////////
//-- Public functions --//
//////////////////////////

void pwm_ControllerInit(void)
{
    ledc_channel_config_t ledc_channel = {
        .gpio_num = LED_PWM_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LED_PWM_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LED_PWM_TIMER,
        .duty = 0,
    };

    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = LED_PWM_BIT_NUM,
        .timer_num = LED_PWM_TIMER,
        .freq_hz = LED_PWM_FREQUENCY,
    };

    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
}

void pwm_ControllerSet(float percent_fraction)
{
    uint32_t max_duty = (1 << LED_PWM_BIT_NUM) - 1;
    uint32_t duty_cycle = lroundf(percent_fraction * (float)max_duty);

    ESP_ERROR_CHECK(ledc_set_duty(LEDC_HIGH_SPEED_MODE, LED_PWM_CHANNEL, duty_cycle));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_HIGH_SPEED_MODE, LED_PWM_CHANNEL));
    ESP_LOGI(TAG, "PWM Duty set to %.00f percent: %d", percent_fraction * 100.0, (int)duty_cycle);
}