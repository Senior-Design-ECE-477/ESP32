#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <driver/spi_common.h>
// #include <driver/spi_master.h>
#include "spi_controller.h"

spi_device_handle_t spi_lcd_device_handle;

void delay_micro_sec(int us)
{
    vTaskDelay(pdMS_TO_TICKS(us / 1000));
}

void delay_milli_sec(int ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

void set_this_pin_to(int pin, int value)
{
    ESP_ERROR_CHECK(gpio_set_direction((gpio_num_t)pin, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level((gpio_num_t)pin, value));
}

void set_cs_pin_to(int value)
{
    set_this_pin_to(SCREEN_CS_PIN, value);
}

void set_dc_pin_to(int value)
{
    set_this_pin_to(SCREEN_DC_RS_PIN, value);
}

void write_data_to_spi(uint8_t data)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.flags = SPI_TRANS_USE_TXDATA;
    t.length = 8;
    t.tx_data[0] = data;
    // set_dc_pin_to(0); // Taken care of by driver
    ESP_ERROR_CHECK(spi_device_polling_transmit(spi_lcd_device_handle, &t)); // spi_handle defined in spi_cpntroller.h
    // spi_device_transmit(handle, &t);
}

void write_buffer_to_spi(uint8_t *adr, uint16_t n)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8 * n;
    t.tx_buffer = adr;
    // set_dc_pin_to(1); // Taken care of by driver
    ESP_ERROR_CHECK(spi_device_polling_transmit(spi_lcd_device_handle, &t)); // spi_handle defined in spi_cpntroller.h
    // spi_device_transmit(handle, &t);
}

void start_spi_bus_3_vspi(void)
{
    // Setup SPI
    spi_host_device_t screen_host = VSPI_HOST;
    spi_bus_config_t buscfg = {
        .mosi_io_num = SCREEN_MOSI_PIN,
        .miso_io_num = SCREEN_MISO_PIN,
        .sclk_io_num = SCREEN_SCK_PIN,
        .quadwp_io_num = -1,                                                   // Quad SPI LCD driver is not yet supported
        .quadhd_io_num = -1,                                                   // Quad SPI LCD driver is not yet supported
        .max_transfer_sz = SCREEN_HOR_RES * SCREEN_VER_RES * sizeof(uint16_t), // transfer 80 lines of pixels (assume pixel is RGB565) at most in one SPI transaction
    };
    // Configuration for the SPI device on the other side of the bus
    spi_device_interface_config_t devcfg = {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .mode = 0,
        .duty_cycle_pos = 128, // 50% duty cycle
        .cs_ena_posttrans = 3,
        .clock_speed_hz = 8000000,
        .spics_io_num = SCREEN_CS_PIN,
        .queue_size = 3, // Keep the CS low 3 cycles after transaction, to stop slave from missing the last bit when CS has less propagation delay than CLK
    };
    ESP_ERROR_CHECK(spi_bus_initialize(screen_host, &buscfg, SPI_DMA_CH_AUTO));        // Enable the DMA feature
    ESP_ERROR_CHECK(spi_bus_add_device(screen_host, &devcfg, &spi_lcd_device_handle)); // spi_handle defined in spi_cpntroller.h
}