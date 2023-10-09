#ifndef _AWS_HTTP_H_
#define _AWS_HTTP_H_

#include <stdio.h>
#include <math.h>
#include "esp_http_client.h"
#include "esp_http_server.h"
#include "esp_log.h"

#include "regex.h"
#include "secret/credentials.h"
#include "secret/certificates.h"

#define MAX_HTTP_RESPONSE_SIZE 128

int giveAccess(char *str);

char *aws_verify_user(int id);

#endif
