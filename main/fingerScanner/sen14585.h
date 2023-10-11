#ifndef __SEN14585_H__
#define __SEN14585_H__

#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "esp_err.h"
#include "sen14585_helper.h"


#define UART_PORT_NUM 1

esp_err_t init_uart();
esp_err_t led_light_on();
esp_err_t led_light_off();
int enroll_finger();
esp_err_t delete_finger(int id);
esp_err_t delete_all_finger();
int identify_finger();
void enter_standby_mode();
void exit_standby_mode();
int get_enroll_count();
int check_if_enrolled(int id);

esp_err_t close_uart();
#endif