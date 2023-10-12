#include "aws_http.h"
char receive_buffer[MAX_HTTP_RESPONSE_SIZE];

static esp_err_t _client_event_post_handler(esp_http_client_event_handle_t evt);

/*
DEPRECATED: The purpose of this is to check the returned message from AWS to see if the user is authorized.
*/
int giveAccess(char *str)
{
    // DEPRECATED FUNCTION see cafs.c
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
esp_err_t _client_event_post_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        // This callback is invoked as data is received
        // Copy results into buffer that will be returned
        printf("HTTP_EVENT_ON_DATA: %.*s\n", evt->data_len, (char *)evt->data);
        if (!esp_http_client_is_chunked_response(evt->client))
        {
            strncpy(receive_buffer, (char *)evt->data, evt->data_len);
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
char *aws_verify_user(int value)
{
    esp_http_client_config_t config_post = {
        .url = VERIFY_USER_ENDPOINT,
        .method = HTTP_METHOD_GET, // HTTP_METHOD_POST,
        .cert_pem = (const char *)cert_start,
        .client_cert_pem = (const char *)certificate_start,
        .client_key_pem = (const char *)private_start,
        .event_handler = _client_event_post_handler};
    esp_http_client_handle_t client = esp_http_client_init(&config_post);

    // EntryValue can be fingerprint ID or passcode
    
    int num_chars_value = snprintf(NULL, 0, "%d", value) + 1;
    int num_chars = num_chars_value + (42 * sizeof(char));
    char post_data[num_chars];
    snprintf(post_data, num_chars, "{\"EntryValue\": %d, \"LockName\": \"main-door\"}", value);

    esp_http_client_set_post_field(client, post_data, strlen(post_data));
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_header(client, "x-api-key", API_TOKEN);

    esp_http_client_perform(client);
    esp_http_client_cleanup(client);

    return receive_buffer;
}
