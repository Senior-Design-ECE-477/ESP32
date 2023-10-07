#ifndef __SEN14585_H__
#define __SEN14585_H__

#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "esp_err.h"
#include "sen14585_helper.h"
#include "debug.h"


#define UART_PORT_NUM 1

esp_err_t init_uart();
esp_err_t led_light_on();
esp_err_t led_light_off();
esp_err_t enroll_finger();
esp_err_t send_fingerprint_command();



int get_enroll_count();

esp_err_t close_uart();
#endif