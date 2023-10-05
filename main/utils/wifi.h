#ifndef _WIFI_H_
#define _WIFI_H_

#include <stdio.h>
#include "esp_wifi.h"
#include "esp_netif.h"

#define SSID // ENTER YOUR WIFI NAME HERE
#define PASS // ENTER YOUR WIFI PASSWORD HERE

void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
void initialize_wifi();

#endif