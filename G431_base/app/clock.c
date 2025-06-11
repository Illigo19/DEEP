/*
 * clock.c
 *
 *  Created on: May 28, 2025
 *      Author: chinabni
 */
#include "stm32g4_uart.h"
#include "clock.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define BUFFER_SIZE 6

static volatile uint32_t u32_time;

bool is_valid_time_format(const char *str);
void clockToTime(uint8_t heure, uint8_t minute);

void addDecade(){
	u32_time++;
}

int setClock(){
	 int index = 0;
	 char buffer[6];
	 uint8_t heure;
	 uint8_t d_minute;
	 printf("set clock ...");
	 while (1) {
		 if(BSP_UART_data_ready(UART2_ID)) {
		     char c = BSP_UART_getc(UART2_ID);
		     if (c == '\n' || c == '\r') {
		         buffer[index] = '\0';
		         index = 0;
		         break;
		     }
		     else {
		         if (index < BUFFER_SIZE - 1) {
		             buffer[index++] = c;
		         }
		     }
		 }
	 }
	 if(is_valid_time_format(buffer)){
		 char h_str[3];
		 strncpy(h_str, buffer, 2);
		 h_str[2] = '\0';
		 heure = atoi(h_str);

		 d_minute = buffer[3] - '0';

		 printf("Heure = %d\n", heure);
		 printf("Minute = %d\n", d_minute);
	 }else{
		 printf("ERROR");
		 return 0;
	 }
	 clockToTime(heure, d_minute);
	 return 1;

}

uint8_t timeToHex(){
	uint8_t heure, dizaine_minutes,ret;
	heure = u32_time / 6;
	dizaine_minutes = u32_time % 6;
	heure = (heure % 24) & 0x1F;
	ret =  ( heure<<3 ) | (dizaine_minutes & 0x07);
	return ret;

}

bool is_valid_time_format(const char *str) {
    if (strlen(str) != 5) return false;
    if (str[2] != ':') return false;
    for (int i = 0; i < 5; ++i) {
        if (i == 2) continue;
        if (str[i] < '0' || str[i] > '9') return false;
    }
    return true;
}

void clockToTime(uint8_t heure, uint8_t minute){
	u32_time = ((heure * 6) + minute);
}


