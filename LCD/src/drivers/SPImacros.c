#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <driver/spi_common.h>
#include <driver/spi_master.h>
#include "SPImacros.h"

void delay_micro_sec(int us)
{
    vTaskDelay(pdMS_TO_TICKS(us / 1000));
}

void delay_milli_sec(int ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

void set_x_pin_to(int pin, int value)
{
    esp_rom_gpio_pad_select_gpio(pin);
    gpio_set_direction((gpio_num_t)pin, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)pin, value);
}

void spi_cs_pin_set(int value)
{
    set_x_pin_to(1, value);
}

void spi_write_screen_data(uint8_t data)
{
    // write data byte to spi bus
    spi_device_handle_t handle;
    spi_host_device_t screen_host = VSPI_HOST;
    spi_bus_config_t buscfg = {
        .mosi_io_num = SCREEN_MOSI_PIN,
        .miso_io_num = SCREEN_MISO_PIN,
        .sclk_io_num = SCREEN_SCK_PIN,
        .quadwp_io_num = -1,                                       // Quad SPI LCD driver is not yet supported
        .quadhd_io_num = -1,                                       // Quad SPI LCD driver is not yet supported
        .max_transfer_sz = SCREEN_HOR_RES * 80 * sizeof(uint16_t), // transfer 80 lines of pixels (assume pixel is RGB565) at most in one SPI transaction
    };
    ESP_ERROR_CHECK(spi_bus_initialize(screen_host, &buscfg, SPI_DMA_CH_AUTO)); // Enable the DMA feature

    // Configuration for the SPI device on the other side of the bus
    spi_device_interface_config_t devcfg = {
        .command_bits = 8,
        .address_bits = 0,
        .dummy_bits = 0,
        .mode = 0,
        .duty_cycle_pos = 128, // 50% duty cycle
        .cs_ena_posttrans = 3,
        .clock_speed_hz = 5000000,
        .spics_io_num = SCREEN_CS_PIN,
        .queue_size = 3, // Keep the CS low 3 cycles after transaction, to stop slave from missing the last bit when CS has less propagation delay than CLK

    };
    ESP_ERROR_CHECK(spi_bus_add_device(screen_host, &devcfg, &handle));
    spi_transaction_t t;
    t.cmd = data;
    spi_device_transmit(handle, &t);
}

void spi_write_screen_memory(uint8_t *adr, uint16_t n)
{

    // for (int i = 0; i < n; i++){
    //     //send 8 bit

    // }
    // write ( n ) number of bytes to spi bus starting from ( adr ) memory address
    spi_device_handle_t handle;
    spi_host_device_t screen_host = VSPI_HOST;
    spi_bus_config_t buscfg = {
        .mosi_io_num = SCREEN_MOSI_PIN,
        .miso_io_num = SCREEN_MISO_PIN,
        .sclk_io_num = SCREEN_SCK_PIN,
        .quadwp_io_num = -1,                                       // Quad SPI LCD driver is not yet supported
        .quadhd_io_num = -1,                                       // Quad SPI LCD driver is not yet supported
        .max_transfer_sz = SCREEN_HOR_RES * 80 * sizeof(uint16_t), // transfer 80 lines of pixels (assume pixel is RGB565) at most in one SPI transaction
    };
    ESP_ERROR_CHECK(spi_bus_initialize(screen_host, &buscfg, SPI_DMA_CH_AUTO)); // Enable the DMA feature

    // Configuration for the SPI device on the other side of the bus
    spi_device_interface_config_t devcfg = {
        .command_bits = 0,
        .address_bits = 8,
        .dummy_bits = 0,
        .mode = 0,
        .duty_cycle_pos = 128, // 50% duty cycle
        .cs_ena_posttrans = 3,
        .clock_speed_hz = 5000000,
        .spics_io_num = SCREEN_CS_PIN,
        .queue_size = 3, // Keep the CS low 3 cycles after transaction, to stop slave from missing the last bit when CS has less propagation delay than CLK

    };
    ESP_ERROR_CHECK(spi_bus_add_device(screen_host, &devcfg, &handle));
    spi_transaction_t t;
    t.addr = adr;
    t.length = n;
    spi_device_transmit(handle, &t);
}
