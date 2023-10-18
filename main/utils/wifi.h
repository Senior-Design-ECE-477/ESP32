#ifndef _WIFI_H_
#define _WIFI_H_

#include <stdio.h>
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "secret/credentials.h"

void wifi_init();
wifi_ap_record_t wifi_connect();

#endif