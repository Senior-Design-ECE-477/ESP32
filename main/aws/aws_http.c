#include "aws_http.h"

/*
The purpose of this is to check the returned message from AWS to see if the user is authorized.
*/
int giveAccess(char *str)
{
    regex_t regex;
    int return_value;

    return_value = regcomp(&regex, "name", 0);
    return_value = regexec(&regex, str, 0, NULL, 0);

    regfree(&regex);
    return return_value;
}

/*
Original Code Source: https://github.com/SIMS-IOT-Devices/FreeRTOS-ESP-IDF-AWS-IOT-Core/tree/main
Modifications made by Thomas Wygal

The purpose of this is to get the return from AWS and turn the motor on if verified correctly
*/
esp_err_t client_event_post_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        // This callback is invoked as data is received
        printf("HTTP_EVENT_ON_DATA: %.*s\n", evt->data_len, (char *)evt->data);

        // You can process the data here, but it's already a string, so no need to call .read()

        if (giveAccess((char *)evt->data) == 0)
        {
            ESP_LOGI("MOTOR", "UNLOCK");
            motor_unlock();
            sleep(3);
            motor_off();
            ESP_LOGI("MOTOR", "OFF");
            sleep(5);
            ESP_LOGI("MOTOR", "LOCKING");
            motor_lock();
            sleep(3);
            ESP_LOGI("MOTOR", "OFF");
            motor_off();
        }
        break;

    default:
        break;
    }
    return ESP_OK;
}

/*
Original Code Source: https://github.com/SIMS-IOT-Devices/FreeRTOS-ESP-IDF-AWS-IOT-Core/tree/main
Modifications made by Thomas Wygal

This code will send an HTTP GET to AWS API Gateway to be sent through a Lambda function before entering the database
*/
void post_rest_function()
{
    esp_http_client_config_t config_post = {
        .url = VERIFY_USER_ENDPOINT,
        .method = HTTP_METHOD_GET, // HTTP_METHOD_POST,
        .cert_pem = (const char *)cert_start,
        .client_cert_pem = (const char *)certificate_start,
        .client_key_pem = (const char *)private_start,
        .event_handler = client_event_post_handler};
    esp_http_client_handle_t client = esp_http_client_init(&config_post);

    char *post_data = "{\"ID\": 3, \"LockName\": \"main-door\"}";
    esp_http_client_set_post_field(client, post_data, strlen(post_data));
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_header(client, "x-api-key", API_TOKEN);

    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
}
