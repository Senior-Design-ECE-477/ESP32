#ifndef __SEN14585_HELPER_H__
#define __SEN14585_HELPER_H__

#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "esp_err.h"
#include "debug.h"



#define UART_PORT_NUM 1

esp_err_t send_uart_command(uint8_t* cmd, uint8_t* data);
int get_parameter_value(uint8_t* data);


#endif

