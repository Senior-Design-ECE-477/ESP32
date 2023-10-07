#include "sen14585_helper.h"

esp_err_t send_uart_command(uint8_t* cmd, uint8_t* data){
    int len = -1;
    int retLen = -1;
    int attempt = 0;

    len = uart_write_bytes(UART_PORT_NUM, cmd, 12);

    if (len > 0) {
        debug_print("Sent", cmd);
    } else {
        return ESP_FAIL;
    }
    
    if(uart_wait_tx_done(UART_PORT_NUM, 100) != ESP_OK) {
        return ESP_FAIL;
    }

    // Read data from the UART
    while(retLen < 1 && attempt < 70){
        uart_get_buffered_data_len(UART_PORT_NUM, (size_t*)&retLen);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        attempt++;
    }

    if(attempt == 70){
        printf("FAILED TO RECEIVE PACKETS\n");
        return ESP_FAIL;
    }

    uart_read_bytes(UART_PORT_NUM, data, retLen, 1000);
    
    return ESP_OK;
}

int get_parameter_value(uint8_t* data){
    return 0;
}