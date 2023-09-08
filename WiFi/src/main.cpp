#include "main.h"

Main App;

const char* WIFI_SSID = "URHome";//"Campus Edge";//"Tommy";
const char* WIFI_PASSPHRASE = "twyg9htk3xR75m64";//"8884pavlov";//"abcdefgh";
const char* ntpServer = "north-america.pool.ntp.org";
const long  gmtOffset_sec = -3600;
const int   daylightOffset_sec = -3600;
char currTime[100];

void Main::checkWifi(void)
{
    wifiState = Wifi.GetState();
    switch (wifiState)
    {
    case WIFI::Wifi::state_e::READY_TO_CONNECT:
        std::cout << "Wifi Status: READY_TO_CONNECT\n";
        Wifi.Begin();
        break;
    case WIFI::Wifi::state_e::DISCONNECTED:
        std::cout << "Wifi Status: DISCONNECTED\n";
        Wifi.Begin();
        break;
    case WIFI::Wifi::state_e::CONNECTING:
        std::cout << "Wifi Status: CONNECTING\n";
        break;
    case WIFI::Wifi::state_e::WAITING_FOR_IP:
        std::cout << "Wifi Status: WAITING_FOR_IP\n";
        break;
    case WIFI::Wifi::state_e::ERROR:
        std::cout << "Wifi Status: ERROR\n";
        break;
    case WIFI::Wifi::state_e::CONNECTED:
        std::cout << "Wifi Status: CONNECTED\n";
        break;
    case WIFI::Wifi::state_e::NOT_INITIALIZED:
        std::cout << "Wifi Status: NOT_INITIALIZED\n";
        break;
    case WIFI::Wifi::state_e::INITIALIZED:
        std::cout << "Wifi Status: INITIALIZED\n";
        break;
    }
}

void Main::setup(void)
{
    esp_event_loop_create_default();
    nvs_flash_init();

    Wifi.SetCredentials(WIFI_SSID, WIFI_PASSPHRASE);
    Wifi.Init();
}

void Main::updateTime() {
	time_t now;
	struct tm ti;
    static const char *DAY_OF_WEEK[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    static const char *MONTH[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	
    time(&now);
	localtime_r(&now, &ti);

	std::cout << " " << ti.tm_hour << " " << ti.tm_min << " " << ti.tm_sec << " " << DAY_OF_WEEK[ti.tm_wday] << " " << ti.tm_mday << " " << MONTH[ti.tm_mon] << " " << ti.tm_year + 1900 << std::endl;
}

void Main::initialize_sntp(void)
{
    ESP_LOGI("SNTP", "Initializing SNTP");
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, ntpServer);
    esp_sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    esp_sntp_init();
    setenv("TZ", "EST5EDT", 1);
    tzset();

}

extern "C" void app_main(void)
{
    bool led_state = false;
    App.setup();
    App.initialize_sntp();
    configure_led();

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        App.checkWifi();
        App.updateTime();
        blink_led(led_state);
        led_state = !led_state;

        sleep(1);
    }
}
