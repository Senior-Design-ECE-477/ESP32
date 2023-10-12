#include "sen14585.h"

uint8_t data[12];

// Initialization UART commands
uint8_t init_cmd[] =                {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01};
uint8_t change_baud_cmd[]=          {0x55, 0xAA, 0x01, 0x00, 0x00, 0xC2, 0x01, 0x00, 0x04, 0x00, 0xC7, 0x01};
uint8_t light_on_cmd[]=             {0x55, 0xAA, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x12, 0x00, 0x13, 0x01};
uint8_t light_off_cmd[]=            {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x12, 0x01};
// Fingerprint Enroll UART commands
uint8_t enroll_start_cmd[] =        {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00}; // 4-7 and 10-11 need to be changed
uint8_t enroll1_cmd[] =             {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x23, 0x01};
uint8_t enroll2_cmd[] =             {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x24, 0x01};
uint8_t enroll3_cmd[] =             {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x25, 0x01};

//Utility UART commands
uint8_t get_enroll_count_cmd[] =    {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x01};
uint8_t check_enrolled_cmd[] =      {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00}; // 4-7 and 10-11 need to be changed
uint8_t is_press_finger_cmd[] =     {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x26, 0x01};
uint8_t capture_finger_enroll_cmd[]={0x55, 0xAA, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x60, 0x00, 0x61, 0x01}; // param4 is nonzero for enrollment
uint8_t capture_finger_verify_cmd[]={0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x60, 0x01}; // its 0 here for faster results
uint8_t delete_id_cmd[] =           {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00}; // 4-7 and 10-11 need to be changed
uint8_t delete_all_cmd[] =          {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x00, 0x41, 0x01};
uint8_t verify_cmd[] =              {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00}; // 4-7 and 10-11 need to be changed
uint8_t identify_cmd[] =            {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x00, 0x51, 0x01};
uint8_t enter_standby_cmd[] =       {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF9, 0x00, 0xF9, 0x01};
uint8_t exit_cmd[] =                {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00};
uint8_t close_cmd[] =               {0x55, 0xAA, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x01};

/*
* This function must be called at the start of the program. It will initialize the fingerprint scanner UART communications,
* and set buffers for TX and RX
*
* @return esp_err_t - will return ESP_OK on success, ESP_FAIL otherwise
*/
esp_err_t init_uart() {
    /* Configure parameters of an UART driver,
    * communication pins and install the driver */
    uart_config_t uart_config = {
    .baud_rate = 9600, //may need to decrease to 9600
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    const int buff_size = (1024 * 2);
    QueueHandle_t uart_queue;

    //Install UART driver, and get the queue.
    uart_driver_install(UART_PORT_NUM, buff_size, buff_size, 10, &uart_queue, 0);
    uart_param_config(UART_PORT_NUM, &uart_config);
    //Set UART pins (using UART0 default pins ie no changes.)

    uart_set_pin(UART_PORT_NUM, 8, 7, -1, -1);

    vTaskDelay(2000 / portTICK_PERIOD_MS);

    send_uart_command(init_cmd, data);
    //send_uart_command(change_baud_cmd, data);
    //uart_set_baudrate(UART_PORT_NUM, 115200);

    return ESP_OK;
}

/*
* This function will turn the LED on
*
* @return esp_err_t - will return ESP_OK on success, ESP_FAIL otherwise
*/
esp_err_t led_light_on(){
    if(send_uart_command(light_on_cmd, data) != ESP_OK) return ESP_FAIL;
    return ESP_OK;
}

/*
* This function will turn the LED off
*
* @return esp_err_t - will return ESP_OK on success, ESP_FAIL otherwise
*/
esp_err_t led_light_off(){
    if(send_uart_command(light_off_cmd, data) != ESP_OK) return ESP_FAIL;
    return ESP_OK;
}

/*
* This function will go through the entire process of enrolling a finger, printing to the terminal when
* it is ready for finger to be placed or removed, as well as the fingerprint ID# being registered
*
* @return int - returns the ID on success, -1 on failure
*/
int enroll_finger() {
    // Get an open fingerprint to enroll... this will be the return value if successful
    int newEnroll = 0;
	int usedid = 1;
	while (usedid == 1)
	{
		usedid = check_if_enrolled(newEnroll);
		if (usedid == 1) newEnroll++;
        if(newEnroll >= 256 || usedid == -1) {
            return -1;
        }
	}

    // Get the command to send to the scanner
    get_cmd_from_value(enroll_start_cmd, newEnroll);

    printf("Start enrollment of fingerprint #%d\n", newEnroll);
    // Send the command to the scanner, and if it fails, return an error
    if(send_uart_command(enroll_start_cmd, data) != ESP_OK) return -1;

    // Make sure the received correctly
    if(data[8] != 0x30) {
        if((data[4] == 0x09 || data[4] == 0x03) && data[5] == 0x10) { // If the Database is full or an invalid position, return fail
            return -1;
        }
    }

    // Wait until finger is pressed
    printf("Press down a finger\n");
    
    while(isPressed(is_press_finger_cmd, data) == false) {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    ESP_LOGI("Enroll Finerprint", "FINGER PRESSED");
    bool goodPrint = captureFinger(capture_finger_enroll_cmd, data);
    

    if(goodPrint != false) {
        printf("Remove finger\n");
        if(enroll(enroll1_cmd, data) != ESP_OK) return -1;

        // Wait until finger is removed
        while(isPressed(is_press_finger_cmd, data) == true) {
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }

        printf("Press the same finger again\n");

        while(isPressed(is_press_finger_cmd, data) == false) {
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }

        goodPrint = captureFinger(capture_finger_enroll_cmd, data);

        if(goodPrint != false) {
            printf("Remove finger\n");
            if(enroll(enroll2_cmd, data) != ESP_OK) return -1;

            // Wait until finger is removed
            while(isPressed(is_press_finger_cmd, data) == true) {
                vTaskDelay(100 / portTICK_PERIOD_MS);
            }
            printf("Press the same finger one more time\n");
            while(isPressed(is_press_finger_cmd, data) == false) {
                vTaskDelay(100 / portTICK_PERIOD_MS);
            }

            goodPrint = captureFinger(capture_finger_enroll_cmd, data);

            if(goodPrint != false) {
                printf("Remove finger\n");
				if(enroll(enroll3_cmd, data) != ESP_OK) return -1;
            } else {
                printf("Failed to capture third finger\n");
            }
        } else {
            printf("Failed to capture second finger\n");
        }
    } else {
        printf("Failed to capture first finger\n");
    }
    return newEnroll;
}

/*
* This function will delete a specific fingerprint ID from the scanner
*
* @param id - the fingerprint ID to delete
* @return esp_err_t - will return ESP_OK on success, ESP_FAIL otherwise
*/
esp_err_t delete_finger(int id){
    get_cmd_from_value(delete_id_cmd, id);
    if(send_uart_command(delete_id_cmd, data) != ESP_OK) return ESP_FAIL;
    
    if(data[8] == 0x30) return ESP_OK; // if it returns a ACK packet
    
    return ESP_FAIL;
}

/*
* This function will delete all stored fingerprints from the scanner
*
* @return esp_err_t - will return ESP_OK on success, ESP_FAIL otherwise
*/
esp_err_t delete_all_finger(){
    
    if(send_uart_command(delete_all_cmd, data) != ESP_OK) return ESP_FAIL;
    
    if(data[8] == 0x30) return ESP_OK; // if it returns a ACK packet
    
    return ESP_FAIL;
}


/*
* This function is identify a finger that has been set on the device. If a registered fingerprint ID matches,
* this will return the ID number, otherwise it will return -1 if not found in 10 seconds
*
* @return int - the fingerprint ID number, or -1 if not found in 10 seconds
*/
int identify_finger() {
    float timer = 0;
    int id = -1;
    while(isPressed(is_press_finger_cmd, data) == false && timer < 10) { //Change max wait time to identify
        vTaskDelay(100 / portTICK_PERIOD_MS);
        timer += 0.1;
    }
    ESP_LOGI("ID Finger", "Finger is pressed");

    captureFinger(capture_finger_verify_cmd, data);
    
    ESP_LOGI("ID Finger", "Finger captured");


    if(send_uart_command(identify_cmd, data) != ESP_OK) return -1;
    ESP_LOGI("ID Finger", "ID command sent");
    id = get_value_from_cmd(data);
    if(id > 255){
        printf("ID IS -1\n");
        return -1;
    }
	return id;
}


/*
* This function is called to enter the fingerprint scanner to standby mode (low power mode).
* First turns the LED off, then puts the device in low power mode
*/
void enter_standby_mode(){
    led_light_off();
    send_uart_command(enter_standby_cmd, data);
}

/*
* This function is called to exit the fingerprint scanner from standby mode (low power mode).
* First sends a 0x00 bit, before delaying the required time and turning the LED back on.
*/
void exit_standby_mode(){
    send_uart_command(exit_cmd, data);
    vTaskDelay(20 / portTICK_PERIOD_MS);
    led_light_on();
}

/*
* This function is called to see how many fingerprints are currently enrolled on the scanner
*
* It will return the number of fingerprints as an integer after going through data processing from little to big endian format
* @return number of fingerprints
* @return -1 if failure
*/
int get_enroll_count(){
    if(send_uart_command(get_enroll_count_cmd, data) != ESP_OK) return -1;

    int numFingers = get_value_from_cmd(data);
    
    return numFingers;
}

/*
* This function is called to see if a fingerprint ID is currently enrolled on the scanner
*
* @return 1 if fingerprint ID is currently enrolled
* @return 0 if fingerprint ID is not currently enrolled
* @return -1 if error
*/
int check_if_enrolled(int id) {
    get_cmd_from_value(check_enrolled_cmd, id);
    if(send_uart_command(check_enrolled_cmd, data) != ESP_OK) return -1;
    if(data[8] == 0x30) return 1;
    if(data[8] == 0x31){
        if(data[4] == 0x04 && data[5] == 0x10){ // 0x1004 (little endian) is NACK_IS_NOT_USED
            return 0;
        } else if (data[4] == 0x03 && data[5] == 0x10){ // 0x1003 (little endian) is NACK_INVALID_POS
            return -1;
        }
    }
    return -1;
}

/*----------------------------------------------------------------
* This function is to close a UART communication with the fingerprint scanner
* 
* @return ESP_OK if successful, ESP_FAIL otherwise
*/
esp_err_t close_uart(){
    if(send_uart_command(close_cmd, data) != ESP_OK) return ESP_FAIL;
    return ESP_OK;
}