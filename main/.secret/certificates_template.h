#ifndef _CERTS_H__
#define _CERTS_H__

/**
 * Replace the default rsa key and access key user/pass with your own 
 * 
 * Rename this file to certificates.h
*/

#define cert_start "-----BEGIN CERTIFICATE-----\n" \
"...\n" \
"-----END CERTIFICATE-----\n"

#define certificate_start "-----BEGIN CERTIFICATE-----\n" \
"...\n" \
"-----END CERTIFICATE-----\n"

#define private_start "-----BEGIN RSA PRIVATE KEY-----\n" \
"...\n" \
"-----END RSA PRIVATE KEY-----\n" \

#define ACCESS_KEY_USER // YOUR ACCESS KEY
#define ACCESS_KEY_PASS // YOUR ACCESS KEY PASSWORD

#endif