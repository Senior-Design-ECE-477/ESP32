/**
 * @file pwm_controller.h
 * LED PWM controller header file
 */
#ifndef _PWM_CONTROLLER_H
#define _PWM_CONTROLLER_H

/**
 * @brief This function initializes the LEDC channel to a specified pin number
 * and configuration. Then the LEDC timer is configured and initialized.
 */
void pwmControllerInit(void);

/**
 * @brief This function takes in a value from 0 to 1, a percentage in decimal form.
 * This value is used to calculate the value that duty should be set to by
 * multiplying by the max duty that is calculated. The duty is then set to the
 * calculated value.
 */
void pwmControllerSet(float left_duty_fraction);

#endif /* _PWM_CONTROLLER_H */