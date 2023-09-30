/**
 * @file pwm_controller.h
 * LED PWM controller header file
 */
#ifndef _PWM_CONTROLLER_H
#define _PWM_CONTROLLER_H

/**
 * @brief
 */
void pwmControllerInit(void);
/**
 * @brief
 */
void pwmControllerSet(float left_duty_fraction);

#endif /* _PWM_CONTROLLER_H */