#include "wifi.h"
static const char *TAG = "wifi";

static void _wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
static void _read_wifi_err(esp_err_t error);

/*----------------------------------------------------------------
Original Code Source: https://github.com/SIMS-IOT-Devices/FreeRTOS-ESP-IDF-AWS-IOT-Core/tree/main
Modifications made by Thomas Wygal

The purpose of this is to print out the current state of the WiFi
to the terminal for debugging purposes.
*/
void _wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_START:
        ESP_LOGI(TAG, "EVENT: WiFi connecting");
        break;
    case WIFI_EVENT_STA_CONNECTED:
        ESP_LOGI(TAG, "EVENT: WiFi connected");
        break;
    case WIFI_EVENT_STA_DISCONNECTED:
        ESP_LOGW(TAG, "EVENT: WiFi lost connection");
        break;
    case IP_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "EVENT: WiFi got IP");
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
void wifi_init()
{
    // Initialize TCP/IP, Event loop, and WiFi as a Station
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_interface_t interface = ESP_IF_WIFI_STA;

    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_initiation));

    // Set-up the event handlers
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, _wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, _wifi_event_handler, NULL));

    // Configure the WiFi
    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASSWORD,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(interface, &wifi_configuration));
    // ESP_ERROR_CHECK(esp_wifi_set_protocol(interface, WIFI_PROTOCOL_11G));         // Only use fastest wifi protocol
    // ESP_ERROR_CHECK(esp_wifi_set_bandwidth(interface, WIFI_BW_HT40));             // HT40 or HT20 or options... sets MHz but doesn't affect speed
    ESP_ERROR_CHECK(esp_wifi_config_80211_tx_rate(interface, WIFI_PHY_RATE_54M)); // Speeds up wifi to up to 54Mbps

    // Start and connect the ESP32 to the WiFi
    ESP_ERROR_CHECK(esp_wifi_start());
    // Connection happens in Wifi task
    // esp_wifi_connect();
}

void _read_wifi_err(esp_err_t error)
{
    switch (error)
    {
    case ESP_OK:
        ESP_LOGI(TAG, "Connection result: (ESP_OK) succeed");
        break;
    case ESP_ERR_WIFI_NOT_INIT:
        ESP_LOGE(TAG, "Connection result: (ESP_ERR_WIFI_NOT_INIT) WiFi is not initialized by esp_wifi_init");
        break;
    case ESP_ERR_WIFI_NOT_STARTED:
        ESP_LOGE(TAG, "Connection result: (ESP_ERR_WIFI_NOT_STARTED) WiFi is not started by esp_wifi_start");
        break;
    case ESP_ERR_WIFI_CONN:
        ESP_LOGE(TAG, "Connection result: (ESP_ERR_WIFI_CONN) WiFi internal error, station or soft-AP control block wrong");
        break;
    case ESP_ERR_WIFI_SSID:
        ESP_LOGE(TAG, "Connection result: (ESP_ERR_WIFI_SSID) SSID of AP which station connects is invalid");
        break;
    case ESP_ERR_WIFI_MODE:
        ESP_LOGE(TAG, "Connection result: (ESP_ERR_WIFI_MODE) Wifi not set to correct mode");
        break;
    default:
        ESP_LOGE(TAG, "Connection result: (OTHER - %d) Error: %s", error, esp_err_to_name(error));
        break;
    }
}

wifi_ap_record_t wifi_connect()
{
    wifi_ap_record_t wifi_info;
    esp_err_t connected = esp_wifi_sta_get_ap_info(&wifi_info);

    if (connected == ESP_OK)
    {
        // Very low signal, attempt to reconnect
        if (wifi_info.rssi < -90)
        {
            ESP_LOGW(TAG, "Connected but no wifi signal. RSSI: %d. Disconnecting", wifi_info.rssi);
            esp_wifi_disconnect();           // Disconnect
            vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for disconnection
            ESP_LOGI(TAG, "Reconnecting");
            esp_err_t wifi_result = esp_wifi_connect(); // Reconnect
            _read_wifi_err(wifi_result);
            esp_wifi_sta_get_ap_info(&wifi_info);
        }
        else
        {
            ESP_LOGI(TAG, "Connected, RSSI: %d", wifi_info.rssi);
        }
    }
    else
    {
        ESP_LOGW(TAG, "Wifi is not connected, attempting to connect.");
        esp_err_t wifi_result = esp_wifi_connect();
        _read_wifi_err(wifi_result);
        esp_wifi_sta_get_ap_info(&wifi_info);
    }

    return wifi_info;
}
