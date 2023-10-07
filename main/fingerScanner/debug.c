#include "debug.h"

void debug_print(char* commandResponse, uint8_t* response){
    #ifdef DEBUG
    printf(commandResponse);
    printf(": ");
    for(int i = 0; i < 12; i++) {
        printf("%x ", response[i]);
    }
    printf("\n");
    #endif
}