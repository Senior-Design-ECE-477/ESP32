#include "ntp_time.h"

/*----------------------------------------------------------------
This function is to get the current time using the NTP server, getting
the current time, and converting it to the local time before printing it out
*/
void update_time() {
	time_t now;
	struct tm ti;
    static const char *DAY_OF_WEEK[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    static const char *MONTH[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    time(&now);
	localtime_r(&now, &ti);

    if(ti.tm_year + 1900 < 2000){
        printf("Syncing with Server...\n");
    } else {
        printf("%d %d %d ", ti.tm_hour, ti.tm_min, ti.tm_sec);
        printf(DAY_OF_WEEK[ti.tm_wday]);
        printf(" %d ", ti.tm_mday);
        printf(MONTH[ti.tm_mon]);
        printf(" %d\n", ti.tm_year + 1900);
    }
}

/*----------------------------------------------------------------
This function is to initialize the Simple Network Time Protocol (SNTP)

This uses the esp_sntp.h library to initialize a connection to the NTP server,
setting the server, timezone, operating mode, and the sync mode.

Information gathered from https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html
*/
void initialize_sntp(void) {
    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, NTPSERVER);
    esp_sntp_init();
    setenv("TZ", TIMEZONE, 1);
    tzset();
}