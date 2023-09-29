#ifndef _AWS_HTTP_H_
#define _AWS_HTTP_H_

#include <stdio.h>
#include "esp_http_client.h"
#include "esp_http_server.h"
#include "certificates.h"
#include "esp_log.h"
#include "motor.h"
#include "regex.h"

#define HTTPURL //THE MQTT URL ENDPOINT DESCRIBED IN README.md

int giveAccess(char* str);

esp_err_t client_event_post_handler(esp_http_client_event_handle_t evt);
void post_rest_function();

void send_data_to_s3(const char *data);
esp_err_t http_event_handler(esp_http_client_event_t *evt);

#endif