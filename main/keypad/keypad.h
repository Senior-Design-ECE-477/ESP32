#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "../utils/pinout.h"

void gpio_init();
void IRAM_ATTR keypad_isr_handler(void* arg);
void keypad_task(void* arg);
char read_key();

#endif