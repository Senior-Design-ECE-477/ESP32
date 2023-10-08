/**
 * @file pwm_controller.h
 * LED PWM controller header file
 */
#ifndef _PWM_CONTROLLER_H
#define _PWM_CONTROLLER_H

/////////////////
//-- Include --//
/////////////////
#include <math.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "esp_log.h"

////////////////
//-- Define --//
////////////////
/**
 * 5 Bit duty resolution with 100,000 Hz frequency
 * chosen for no flickering and low eye strain
 **/
#define LED_PWM_CHANNEL LEDC_CHANNEL_1
#define LED_PWM_TIMER LEDC_TIMER_1
#define LED_PWM_BIT_NUM LEDC_TIMER_5_BIT
#define LED_PWM_FREQUENCY 100000

#define LED_PWM_PIN GPIO_NUM_21

////////////////////////////////////
//-- Public function prototypes --//
////////////////////////////////////

/**
 * @brief This function initializes the LEDC channel to a specified pin number
 * and configuration. Then the LEDC timer is configured and initialized.
 */
void pwm_ControllerInit(void);

/**
 * @brief This function takes in a value from 0 to 1, a percentage in decimal form.
 * This value is used to calculate the value that duty should be set to by
 * multiplying by the max duty that is calculated. The duty is then set to the
 * calculated value.
 */
void pwm_ControllerSet(float left_duty_fraction);

#endif /* _PWM_CONTROLLER_H */