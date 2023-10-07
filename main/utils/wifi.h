#ifndef _WIFI_H_
#define _WIFI_H_

#include <stdio.h>
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_log.h"
#include ".secret/credentials.h"

void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
void initialize_wifi();
wifi_ap_record_t wifi_connect();

#endif