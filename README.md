# Cloud Authenticated Fingerprint Scanner (CAFS) based on the ESP32

All code in this Repository is to be flashed onto the microcontroller for working access.

Folder Heirarchy

main\
├─── aws\
│ └─── aws_http\
├─── screen\
│ └─── screen_controller\
├─── ui\
│ ├─── animations\
│ ├─── images\
│ ├─── screens\
│ └─── ui\
├─── utils\
│ ├─── wifi\
│ ├─── pwm_controller\
│ └─── ntp_time\
└─── main

## Installation

### Prequisites

- VSCode
- Espressif IDF extension for VSCode
- An ESP32 Microcontroller
- Git

### Clone

Clone this repository into your workspace.

- Open a Terminal window
- Run the follwing command

```
git clone https://
```

#### Add Submodule: lvgl

This project depends upon lvgl v7.11.0 (git@b55ee6a).

To add this library as a submodule:

- Open a Terminal window
- Run the follwing command

```shell
git submodule add -f https://github.com/lvgl/lvgl.git components/lvgl
```

Then go into the components/lvgl folder

```shell
cd ./components/lvgl
```

Finally, set git to use the correct version of lvgl with

```shell
git checkout b55ee6a
```

#### Add Submodule: lvgl_esp32_drivers

This project depends upon lvgl_esp32_drivers (git@9fed1cc).

To add this library as a submodule:

- Open a Terminal window
- Run the follwing command

```shell
git submodule add -f https://github.com/lvgl/lvgl_esp32_drivers.git components/lvgl_esp32_drivers
```

Then go into the components/lvgl_esp32_drivers folder

```shell
cd ./components/lvgl_esp32_drivers
```

Set git to use the correct version of lvgl_esp32_drivers with

```shell
git checkout 9fed1cc
```

Now move the ili9341.c file found in the same directory as this README, into `components/lvgl_esp32_driver/lvgl_tft`, replacing the file that is already there. This file has the follwing updates made to it to fix build errors.

```C
gpio_pad_select_gpio(...);   ->   esp_rom_gpio_pad_select_gpio(...);

portTICK_RATE_MS   ->   portTICK_PERIOD_MS
```

### Config

Open the `menuconfig` by clicking the settings icon by build.\
Scroll down to lvgl configuration and set driver to ILI9341.\
Also set pin configuration here.\

A sample sdkconfig file is provided for ESP32 Feather V2.

### Build

Open this folder in VSCode and enable the Espressif IDF extension.

Connect your microcontroller and select the port. Then, within the ESP IDF Explorer tab, click `Connect your board first`.

Once the microcontroller is connected to the extension, you can build then upload the code.

## LCD Screen

Start the screen by running `runScreenGUI()` in a seperate thread by calling `xTaskCreatePinnedToCore`. Now any of these functions will works:

`ui_init` Initialize the UI.\
`ui_Unlock` Unlock the lock indicator icon.\
`ui_Lock` Lock the lock indicator icon.\
`ui_TimeAndIconsToTop_Animation` Run the animation move the lock icon and time label up to the top of the screen.\
`ui_Welcome_Animation` Run the animation to go to welcome screen, and then back to normal.\
`ui_ShowKeypad_Animation` Run the animation to show the keypad screen.\
`ui_ShakeKeypad_Animation` Run the animation to shake the keypad rapidly.\
`ui_ShakeLock_Animation` Run the animation to shake the lock icon rapidly.\

Full example going through all the animations:

```C

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "screen/screen_controller.h"
#include "utils/pwm_controller.h"
#include "ui/ui.h"

/**********************
 *   APPLICATION MAIN
 **********************/

void app_main()
{
    // Start LCD and backlight PWM
    xTaskCreatePinnedToCore(runScreenGUI, "gui", 4096 * 2, NULL, 0, NULL, 1);
    pwmControllerInit();
    pwmControllerSet(0.05); // PWM signal for dimmed mode
    vTaskDelay(pdMS_TO_TICKS(5000));
    pwmControllerSet(1); // PWM signal for bright mode
    ui_ShakeLock_Animation(0);
    vTaskDelay(pdMS_TO_TICKS(1000));
    ui_Unlock();
    ui_Welcome_Animation(500);
    vTaskDelay(pdMS_TO_TICKS(6000));
    ui_Lock();
    ui_ShowKeypad_Animation(0);
    ui_ShakeKeypad_Animation(1000);
}

```

## PWM for the LCD Screen's LED Backlight

The PWM Controller file has definitions for pin (default 21:MISO), frequency (100KHz), duty resolution bits (5-bit), LEDC timer (1), and LEDC channel (1).\
Use `pwmControllerInit()` to initialize LEDC and configure the duty resolution.\
Use `pwmControllerSet(float percent_fraction)` to set the duty cycle. The function takes a float in the interval [0, 1]. 0 is off while 1 is max duty.

## Time

To connect to the NTP Server, you first must be connected to WiFi. (Follow the README.md in WiFi folder). To connect to a specific time server and change the timezone, go into ntp_server.h and change the defined NTPSERVER.

After this, in the main function, initialize the sntp by calling the following function:

```
initialize_sntp(); // Initialize the Time Server
```

Once the Microcontroller is connected to WiFi, you can simply call the following function:

```
update_time();
```

In order to retrieve the current time.

## Wifi

To connect to WiFi, first enter your `username` and `password` to the WiFi network in Wifi.h.

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

## AWS

To send an HTTP message to AWS, you first must be connected to WiFi (Follow the README.md in WiFi folder). You will then need to set up
everything on AWS following instructions below (may be outdated or missing some information)

First, go to IoT Core, and on the side bar, under Manage>All devices, click `Things`. You will then click Create Things,
Create single thing, Enter your things name, Auto-generate a new certificate, give it a policy, and create the thing. When you have
created the thing, download all certificates, and copy the contents of AmazonRootCA1.pem to certificates.h under `cert_start`, making
each line in quotes, with a new line character at the end, and \ (Ex: "...\n" \ ). Do the same with certificate.pem.crt for `certificate_start`, and private.pem.key
for `private_start`. You can comment out the `ACCESS_KEY_USER` and `ACCESS_KEY_PASS`.

When creating a policy, go to IoT Core, under Manage>Security, click `Policies`. You will then enter a policy name, as well as actions.
The policies used for this microcontroller were iot:Connect, iot:Subscribe, iot:Receive, and iot:Publish.

You can then go to IoT Core, under Test, click `MQTT test client`. You will then Subscribe to a topic by entering a name and clicking
subscribe. Then, you can get the endpoint of the test client by clicking the Connection Details dropdown and copying it to HTTPURL in
aws_http.h. You will also need to add `:<port>/topics/<your topic name>?qos=1` to the end of the defined constant. The port can be 8443,
and topic name is what you just entered.

You do not need `esp_http_client_set_header(client, "x-api-key", '...');` for the mqtt connection, so comment that line out.

After this, in the main function, you can simply just call `post_rest_function();`.
