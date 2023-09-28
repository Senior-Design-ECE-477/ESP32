# Cloud Authenticated Fingerprint Scanner (CAFS) based on the ESP32

All code in this Repository is to be flashed onto the microcontroller for working access.

The WiFi folder contains code that will be used to connect the ESP32 to a WiFi network to enable IoT access.
The TimeServer folder contains code used to get the time off a server.
The esp32ToAwsHttp folder contains code to send messages from ESP32 to AWS IoT.

## Installation

### Prequisites

### Clone

#### Add Submodule: lvgl

#### Add Submodule: lvgl_esp32_drivers

### Build

## LCD Screen

> Coming Soon!

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
