#include "esp_log.h"                    // Logging ESP debugging
#include "driver/gpio.h"                // For powering the motor
#include "freertos/FreeRTOS.h"
<<<<<<< HEAD

#define MOTOR_GPIO_IN1 20 //SCL
#define MOTOR_GPIO_IN2 22 //SDA

=======
#include "pinout.h"
>>>>>>> 508bfaf (new stuff)

void motor_unlock();
void motor_lock();
void motor_off();
