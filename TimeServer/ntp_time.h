#include <stdio.h>
#include "esp_netif.h"
#include "esp_sntp.h"
#include "esp_netif_sntp.h"

#define NTPSERVER "north-america.pool.ntp.org"
#define TIMEZONE "EST5EDT"

void update_time();
void initialize_sntp(void);
