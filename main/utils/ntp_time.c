#include "ntp_time.h"

/*----------------------------------------------------------------
This function is to get the current time using the NTP server, getting
the current time, and converting it to the local time before printing it out
*/
struct tm time_get_now()
{
    time_t now;
    struct tm ti;

    time(&now);
    localtime_r(&now, &ti);

    return ti;
}

/*----------------------------------------------------------------
This function is to initialize the Simple Network Time Protocol (SNTP)

This uses the esp_sntp.h library to initialize a connection to the NTP server,
setting the server, timezone, operating mode, and the sync mode.

Information gathered from https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html
*/
void time_init(void)
{
    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, NTPSERVER);
    esp_sntp_init();
    setenv("TZ", TIMEZONE, 1);
    tzset();
}