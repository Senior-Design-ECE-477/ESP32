#ifndef __SEN14585_HELPER_H__
#define __SEN14585_HELPER_H__

#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "esp_err.h"



#define UART_PORT_NUM 1

esp_err_t send_uart_command(uint8_t* cmd, uint8_t* data);
int get_value_from_cmd(uint8_t* data);
void get_cmd_from_value(uint8_t* data, int value);

bool captureFinger(uint8_t* cmd, uint8_t* data);
bool isPressed(uint8_t* cmd, uint8_t* data);
esp_err_t enroll(uint8_t* cmd, uint8_t* data);

#endif

