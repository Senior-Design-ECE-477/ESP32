#include <math.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "pwm_controller.h"

#define LED_PWM_CHANNEL LEDC_CHANNEL_1
#define LED_PWM_TIMER LEDC_TIMER_1
#define LED_PWM_BIT_NUM LEDC_TIMER_5_BIT
#define LED_PWM_PIN GPIO_NUM_21

void pwmControllerInit(void)
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
        .freq_hz = 100000,
    };

    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
}

void pwmControllerSet(float percent_fraction)
{
    uint32_t max_duty = (1 << LED_PWM_BIT_NUM) - 1;
    uint32_t duty_cycle = lroundf(percent_fraction * (float)max_duty);

    ESP_ERROR_CHECK(ledc_set_duty(LEDC_HIGH_SPEED_MODE, LED_PWM_CHANNEL, duty_cycle));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_HIGH_SPEED_MODE, LED_PWM_CHANNEL));
}