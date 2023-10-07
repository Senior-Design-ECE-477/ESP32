#ifndef _AWS_HTTP_H_
#define _AWS_HTTP_H_

#include <stdio.h>
#include "esp_http_client.h"
#include "esp_http_server.h"
#include "esp_log.h"

#include "utils/motor.h"
#include "regex.h"
#include "secret/credentials.h"
#include "secret/certificates.h"

int giveAccess(char *str);

esp_err_t client_event_post_handler(esp_http_client_event_handle_t evt);
void post_rest_function();

#endif
