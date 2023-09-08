#include <string>
#include <iostream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_sntp.h"
#include "esp_netif.h"
#include "esp_netif_sntp.h"
#include "wifi.h"
#include "driver/gpio.h"
#include "blink.h"

class Main final
{
private:
public:
    void checkWifi(void);
    void setup(void);
    void updateTime();


    void initialize_sntp(void);
    
    WIFI::Wifi::state_e wifiState { WIFI::Wifi::state_e::NOT_INITIALIZED };
    WIFI::Wifi Wifi;
};