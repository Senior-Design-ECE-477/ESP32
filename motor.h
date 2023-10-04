#include "esp_log.h"                    // Logging ESP debugging
#include "driver/gpio.h"                // For powering the motor
#include "freertos/FreeRTOS.h"

#define MOTOR_GPIO_IN1 20 //SCL
#define MOTOR_GPIO_IN2 22 //SDA


void motor_unlock();
void motor_lock();
void motor_off();