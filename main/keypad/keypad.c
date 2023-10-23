#include "keypad.h"

// Define keypad layout and GPIO pins
char keypad[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

// Initialize GPIO
void gpio_init() {
    gpio_config_t io_conf;
    // Set GPIOs as input
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    io_conf.pin_bit_mask = (1ULL << KEYPAD_ROW1_PIN) | (1ULL << KEYPAD_ROW2_PIN) | (1ULL << KEYPAD_ROW3_PIN) | (1ULL << KEYPAD_ROW4_PIN);
    gpio_config(&io_conf);
    
    // Set GPIOs as output
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pin_bit_mask = (1ULL << KEYPAD_COL1_PIN) | (1ULL << KEYPAD_COL2_PIN) | (1ULL << KEYPAD_COL3_PIN);
    gpio_config(&io_conf);
}

// Read a key press with software debouncing
char read_key() {
    static char last_key = '\0';  // Store the last key pressed
    char key = '\0';

    for (int col = 0; col <= 2; col++) {
        gpio_set_level(KEYPAD_COL1_PIN, (col == 0) ? 1 : 0);
        gpio_set_level(KEYPAD_COL2_PIN, (col == 1) ? 1 : 0);
        gpio_set_level(KEYPAD_COL3_PIN, (col == 2) ? 1 : 0);
        vTaskDelay(pdMS_TO_TICKS(10)); // Debounce time
        
        for (int row = 0; row < 4; row++) {
            int currRow = KEYPAD_ROW1_PIN;
            if(row == 1) {
                currRow = KEYPAD_ROW2_PIN;
            } else if(row == 2) {
                currRow = KEYPAD_ROW3_PIN;
            } else if(row == 3) {
                currRow = KEYPAD_ROW4_PIN;
            }
            if (gpio_get_level(currRow)) {
                key = keypad[row][col];
                break; // Exit the loop as soon as a key is detected
            }
        }
        if (key != '\0') {
            // Key press detected
            if (key == last_key) {
                // Ignore repeated keypresses
                return '\0';
            }
            last_key = key;
            return key;
        }
    }
    // No key press detected
    last_key = '\0';
    return '\0';
}