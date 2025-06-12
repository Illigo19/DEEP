/*
 * nfc.c
 *
 *  Created on: Jun 6, 2025
 *      Author: chinabni
 */
#include "stm32g4_uart.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma pack(1)
#define BUFFER_SIZE 16
static char buffer[BUFFER_SIZE] = {0};
static int b_tagReceive = 0;
//unsigned long long u64_ret;

void nfc_init(){
	BSP_UART_init(UART1_ID,9600);
}

int receiveTag(){
	return b_tagReceive;
}
/*
unsigned long long getTag(){
	//u64_ret = strtoull(buffer, NULL, 16);
	return u64_ret;
}*/

void waitTag(){
    static uint8_t u8_index = 0;
    if(b_tagReceive){
        b_tagReceive = 0;
        u8_index = 0;
    }

    if(BSP_UART_data_ready(UART1_ID) && (u8_index <= (BUFFER_SIZE - 2))){
        char c = BSP_UART_get_next_byte(UART1_ID);

        if(u8_index == (BUFFER_SIZE - 2)){
            b_tagReceive = 1;
            u8_index = 0;
        } else if((c>='0') && (c<='F')){
            buffer[u8_index] = c;
            u8_index++;
        }
    }
}

