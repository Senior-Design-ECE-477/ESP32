#include "sen14585_helper.h"


/*----------------------------------------------------------------
* This function sends the first input parameter's command through UART to the fingerprint scanner
* and inputs the response from the communication into the second input parameter. It will then
* return ESP_OK if the communication was successful, or ESP_FAIL if the communication failed.
* 
* @param cmd - command to send through UART
* @param data - array of data received from fingerprint scanner
* @return esp_err_t - ESP_OK on success, ESP_FAIL on failure
*/
esp_err_t send_uart_command(uint8_t* cmd, uint8_t* data){
    int len = -1;
    int retLen = -1;
    int attempt = 0;
    
    // ESP_LOGI("IN SEND UART COMMAND", "Entered");
    // Send the command throught UART to the fingerprint scanner
    len = uart_write_bytes(UART_PORT_NUM, cmd, 12);

    // len is the number of bytes sent to the output buffer
    if (len <= 0) {
        return ESP_FAIL;
    }
    
    // Waits for the written data to be sent throught UART
    if(uart_wait_tx_done(UART_PORT_NUM, 100) != ESP_OK) {
        return ESP_FAIL;
    }

    // Reads data in from the UART, attempting up to 70 times before failing, with a 10ms delay between attempts
    while(retLen < 1 && attempt < 70){
        uart_get_buffered_data_len(UART_PORT_NUM, (size_t*)&retLen);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        attempt++;
    }

    if(attempt == 70){
        printf("FAILED TO RECEIVE PACKETS\n");
        return ESP_FAIL;
    }

    // Reads the data from the incoming UART buffer and puts into the data buffer, max of 100 millisecond wait
    uart_read_bytes(UART_PORT_NUM, data, retLen, 100);
    
    return ESP_OK;
}

/*----------------------------------------------------------------
* This function gets the value in the parameter section of the UART communication, array indices 4-7,
* and converts it to big endian format from little endian.
* 
* @param data - array of data to get value from 
* @return the value calculated as an int
*/
int get_value_from_cmd(uint8_t* data){
    int value;
    // ESP_LOGI("GET VAL FROM CMD", "Entered");
    //Parameter is in indices 4-7
    value = data[4];
    value += (data[5] << 8);
    value += (data[6] << 16);
    value += (data[7] << 24);
    // ESP_LOGI("GET VAL FROM CMD", "Added, now returning");
    return value;
}

/*----------------------------------------------------------------
* This function is to prepare a command for sending through UART communication. We first pass in the
* base command wanting to be used, as well as the input ID number or value we want to set in the parameter,
* before then converting the command parameter and checksum to the appropriate value.
* 
* @param data - array of bytes of the command to be altered before sending through UART
* @param value - the value to be set in the parameter
*/
void get_cmd_from_value(uint8_t* data, int value){
    //Set the parameter values from 4-7
    data[4] = value & 0xFF;
    data[5] = (value >> 8) & 0xFF;
    data[6] = (value >> 16) & 0xFF;
    data[7] = (value >> 24) & 0xFF;

    //Set the checksum in 10-11
    int checksum = data[0] + data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7] + data[8] + data[9];
    data[10] = checksum & 0xFF;
    data[11] = (checksum >> 8) & 0xFF;    
}




/*----------------------------------------------------------------
* This function is to send a command to the scanner to capture a fingerprint, and will return true if 
* the fingerprint is valid, false otherwise
* 
* @param cmd - command to send through UART
* @param data - array of data received from fingerprint scanner
* @return true if successful, false if bad print or error
*/
bool captureFinger(uint8_t* cmd, uint8_t* data){
    send_uart_command(cmd, data);

    if(data[8] == 0x30) return true;

    return false;
}

/*----------------------------------------------------------------
* This function is to send a command to the scanner to see if a finger is pressed on the scanner, and will return true
* else, false
* 
* @param cmd - command to send through UART
* @param data - array of data received from fingerprint scanner
* @return true if finger on, false otherwise
*/
bool isPressed(uint8_t* cmd, uint8_t* data) {
    send_uart_command(cmd, data);

    if(data[8] == 0x30){
        if(data[4] == 0x12 && data[5] == 0x10){
            return false;
        }
        return true;  
    }
    return false;
}

/*----------------------------------------------------------------
* This function is to send the enroll1, enroll2, and enroll3 commands with proper error checking,
* and will return ESP_OK if successful
* 
* @param cmd - command to send through UART
* @param data - array of data received from fingerprint scanner
* @return ESP_OK if successful, ESP_FAIL if bad print or error
*/
esp_err_t enroll(uint8_t* cmd, uint8_t* data){
    if(send_uart_command(cmd, data) != ESP_OK) return ESP_FAIL;

    if(data[8] != 0x30) {
        if(data[4] == 0x0D && data[5] == 0x10) { // Failed enrollment... instant quit
            return ESP_FAIL;
        } else if (data[4] == 0x0C && data[5] == 0x10) { // bad fingerprint... retry up to 3 times
            return ESP_FAIL;
        }
    } 
    return ESP_OK;
}

