/**
 * @file pwm_controller.h
 * LED PWM controller header file
 */
#ifndef PWM_CONTROLLER_H
#define PWM_CONTROLLER_H

/**
 * @brief
 */
void pwmControllerInit(void);
/**
 * @brief
 */
void pwmControllerSet(float left_duty_fraction);

#endif /* PWM_CONTROLLER_H */