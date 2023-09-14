#ifndef SPIMACROS_H
#define SPIMACROS_H

/***********************
 *  Pin Definitions   *
***********************/

#ifndef SCREEN_CS_PIN
#define SCREEN_CS_PIN 26
#endif

#ifndef SCREEN_DC_RS_PIN
#define SCREEN_DC_RS_PIN 4
#endif

#ifndef SCREEN_MOSI_PIN
#define SCREEN_MOSI_PIN 19
#endif

#ifndef SCREEN_SCK_PIN
#define SCREEN_SCK_PIN 5
#endif

#ifndef SCREEN_LED_PIN
#define SCREEN_LED_PIN 33
#endif

#ifndef SCREEN_MISO_PIN
#define SCREEN_MISO_PIN 21
#endif

/***********************
 *  Screen Resolution  *
***********************/

#ifndef SCREEN_HOR_RES
#define SCREEN_HOR_RES 240
#endif

#ifndef SCREEN_VER_RES
#define SCREEN_VER_RES 320
#endif

/***********************
 *       Methods       *
***********************/

void delay_micro_sec(int us);

void delay_milli_sec(int ms);

void set_x_pin_to(int pin, int value);

void spi_cs_pin_set(int val);

void spi_write_screen_data(uint8_t data);

void spi_write_screen_memory(uint8_t *adr, uint16_t n);

#endif /* SPIMACROS_H */