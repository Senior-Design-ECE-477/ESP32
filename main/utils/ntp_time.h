#include <stdio.h>
#include "esp_netif.h"
#include "esp_sntp.h"
#include "esp_netif_sntp.h"

#define NTPSERVER "north-america.pool.ntp.org"
#define TIMEZONE "EST5EDT"

struct tm getTime();
void initialize_sntp(void);
