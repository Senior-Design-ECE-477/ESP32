#ifndef SPIMACROS_H
#define SPIMACROS_H

void delay_micro_sec(int us);

void delay_milli_sec(int ms);

void set_x_pin_to(int pin, int value);

void spi_cs_pin_set(int val);

void spi_write_screen_data(uint8_t data);

void spi_write_screen_memory(uint8_t *adr, uint16_t n);

#endif /* SPIMACROS_H */