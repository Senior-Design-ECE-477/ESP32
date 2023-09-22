To connect to WiFi, first enter your  `username` and `password` to the WiFi network in Wifi.h.

After this, in the main function, call these commands in order:
```
nvs_flash_init();   // Initialize the nonvolatile flash

initialize_wifi();  // Initialize the WiFi

esp_wifi_connect();  // Connect to the WiFi
```
If you are looking to reconnect the WiFi if it is disconnected or a weak signal, do the following as well:

```                                                        
wifi_ap_record_t wifi_info;

connected = esp_wifi_sta_get_ap_info(&wifi_info);

if(connected == ESP_OK) {
    if(wifi_info.rssi < -90) {
            
        ESP_LOGI("WEAK WIFI", "Weak Wi-Fi signal. Reconnecting...");
                 
        esp_wifi_disconnect();
                
        vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for disconnection
                
        esp_wifi_connect();
                
        } 
            
    } else {
        
        esp_wifi_connect();
            
    }
}
``` 
