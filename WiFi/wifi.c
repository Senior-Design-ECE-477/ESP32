#include "wifi.h"

/*----------------------------------------------------------------
Original Code Source: https://github.com/SIMS-IOT-Devices/FreeRTOS-ESP-IDF-AWS-IOT-Core/tree/main
Modifications made by Thomas Wygal

The purpose of this is to print out the current state of the WiFi
to the terminal for debugging purposes.
*/
void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_START:
        printf("WiFi connecting ... \n");
        break;
    case WIFI_EVENT_STA_CONNECTED:
        printf("WiFi connected ... \n");
        break;
    case WIFI_EVENT_STA_DISCONNECTED:
        printf("WiFi lost connection ... \n");
        break;
    case IP_EVENT_STA_GOT_IP:
        printf("WiFi got IP ... \n\n");
        break;
    default:
        break;
    }
}

/*----------------------------------------------------------------
This function is to initialize the WiFi Networking Functionality as well
as the TCP/IP interface

This uses the esp_netif.h and esp_wifi.h library to initialize the TCP/IP
stack, as well as the WiFi station on the ESP32.

Information gathered from Espressif website from below links:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_netif.html
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/esp_event.html#_CPPv429esp_event_loop_create_default
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html
*/
void initialize_wifi()
{
    // Initialize TCP/IP, Event loop, and WiFi as a Station
    esp_netif_init();
    esp_event_loop_create_default();     
    esp_netif_create_default_wifi_sta(); 
    wifi_interface_t interface = ESP_IF_WIFI_STA;

    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_initiation);

    // Set-up the event handlers 
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    
    // Configure the WiFi
    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = SSID,
            .password = PASS
            }
        };
    esp_wifi_set_config(interface, &wifi_configuration);
    esp_wifi_set_protocol(interface, WIFI_PROTOCOL_11G); // Only use fastest wifi protocol
    //esp_wifi_set_bandwidth(interface, WIFI_BW_HT40); HT40 or HT20 or options... sets MHz but doesn't affect speed
    esp_wifi_config_80211_tx_rate(interface, WIFI_PHY_RATE_54M); //Speeds up wifi to up to 54Mbps
    
    // Start and connect the ESP32 to the WiFi
    esp_wifi_start();
    esp_wifi_connect();
}