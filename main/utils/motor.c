#include "motor.h"

/* 
Will spin the motor in an unlocking fashion when called
*/
void motor_unlock(){
    gpio_set_direction(MOTOR_GPIO_IN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_GPIO_IN2, GPIO_MODE_OUTPUT);

   // gpio_set_pull_mode(MOTOR_GPIO, GPIO_PULLDOWN_ONLY);
    gpio_set_level(MOTOR_GPIO_IN2, 1); //SDA GOES INTO PH
    gpio_set_level(MOTOR_GPIO_IN1, 1); //SCL GOES INTO ENABLE
}

/* 
Will stop the spinning of the motor in any direction
*/
void motor_lock(){
    gpio_set_direction(MOTOR_GPIO_IN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_GPIO_IN2, GPIO_MODE_OUTPUT);

   // gpio_set_pull_mode(MOTOR_GPIO, GPIO_PULLDOWN_ONLY);
    gpio_set_level(MOTOR_GPIO_IN2, 0); //SDA GOES INTO PH
    gpio_set_level(MOTOR_GPIO_IN1, 1); //SCL GOES INTO ENABLE
}


/* 
Will spin the motor in a locking fashion when called
*/
void motor_off(){
    gpio_set_direction(MOTOR_GPIO_IN1, GPIO_MODE_OUTPUT);
    gpio_set_level(MOTOR_GPIO_IN1, 0); //SCL GOES INTO ENABLE
}
