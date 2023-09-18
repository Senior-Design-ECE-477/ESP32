/**
 * @file spi_controller.h
 * SPIController header file
 */
#ifndef SPI_CONTROLLER_H
#define SPI_CONTROLLER_H

#include <driver/spi_master.h>

/***********************
 *  Pin Definitions   *
***********************/

#ifndef SCREEN_RESET_PIN
#define SCREEN_RESET_PIN 12
#endif

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
 *Functions and Classes*
***********************/



void delay_micro_sec(int us);
void delay_milli_sec(int ms);

void set_this_pin_to(int pin, int value);

void write_data_to_spi(uint8_t data);
void write_buffer_to_spi(uint8_t *adr, uint16_t n);

void start_spi_bus_3_vspi(void);
// void stop();

void set_cs_pin_to(int value); // Unused, using set_this_pin_to() instead
void set_dc_pin_to(int value); // Unused, using set_this_pin_to() instead

extern spi_device_handle_t spi_lcd_device_handle;

#endif /* SPI_CONTROLLER_H */