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

/// Buffer utilisé pour stocker les données du tag NFC.
static char buffer[BUFFER_SIZE] = {0};

/// Indique si un tag NFC complet a été reçu (1 = reçu, 0 = non reçu).
static int b_tagReceive = 0;

/// Valeur entière extraite du tag reçu.
//uint64_t u64_ret;

/**
 * @brief Initialise la communication UART pour le module NFC.
 *
 * Configure l'UART1 à une vitesse de 9600 bauds pour permettre
 * la réception des données en provenance du lecteur NFC.
 */
void nfc_init(){
	BSP_UART_init(UART1_ID,9600);
}

/**
 * @brief Vérifie si un tag NFC a été reçu.
 *
 * Cette fonction retourne l'état de réception d’un tag complet.
 *
 * @return 1 si un tag a été reçu, 0 sinon.
 */
int receiveTag(){
	return b_tagReceive;
}

/**
 * @brief Récupère la valeur du tag NFC sous forme entière.
 *
 * Convertit la chaîne de caractères stockée dans le buffer en un entier non signé 64 bits
 * en interprétant la chaîne comme une valeur hexadécimale.
 *
 * @return La valeur du tag NFC au format `unsigned long long`.
 */
void getTag(uint32_t *hi, uint32_t *lo) {
    uint64_t v = strtoull(buffer, NULL, 16);
    *hi = (uint32_t)(v >> 32);
    *lo = (uint32_t)(v & 0xFFFFFFFFUL);
}

/**
 * @brief Attend la réception d’un tag NFC via l’UART.
 *
 * Cette fonction lit les caractères entrants depuis l’UART1 et les enregistre dans un buffer
 * tant qu'un tag complet (BUFFER_SIZE - 1 caractères valides) n'est pas reçu. Elle ignore les
 * caractères invalides. Lorsqu’un tag complet est reçu, la variable `b_tagReceive` est mise à 1.
 */
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
        } else if((c >= '0') && (c <= 'F')){
            buffer[u8_index] = c;
            u8_index++;
        }
    }
}
