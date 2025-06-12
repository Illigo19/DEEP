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

/// Représente le temps encodé sous forme d'un entier (base : 1 unité = 10 minutes).
static volatile uint32_t u32_time;

/**
 * @brief Vérifie si une chaîne est au format horaire "hh:mm".
 *
 * @param str Chaîne de caractères à vérifier.
 * @return true si la chaîne respecte le format, false sinon.
 */
bool is_valid_time_format(const char *str);

/**
 * @brief Convertit une heure et une dizaine de minutes en format interne.
 *
 * @param heure Heure (0 à 23).
 * @param minute Dizaine de minutes (0 à 5, pour 0 à 50 minutes).
 */
void clockToTime(uint8_t heure, uint8_t minute);

/**
 * @brief Incrémente l’horloge interne de 10 minutes.
 *
 * Cette fonction augmente la variable `u32_time` d'une unité.
 */
void addDecade(){
	u32_time++;
}

/**
 * @brief Lit une heure depuis l'UART et la configure comme nouvelle heure.
 *
 * Cette fonction attend que l'utilisateur saisisse une heure au format "hh:mm"
 * via l’UART2. Si le format est correct, l'heure est convertie et stockée.
 *
 * @return 1 si l'heure a été correctement définie, 0 en cas d'erreur de format.
 */
int setClock(){
	int index = 0;
	char buffer[6];
	uint8_t heure;
	uint8_t d_minute;

	printf("set clock ...");

	while (1) {
		if (BSP_UART_data_ready(UART2_ID)) {
			char c = BSP_UART_getc(UART2_ID);
			if (c == '\n' || c == '\r') {
				buffer[index] = '\0';
				index = 0;
				break;
			} else {
				if (index < BUFFER_SIZE - 1) {
					buffer[index++] = c;
				}
			}
		}
	}

	if (is_valid_time_format(buffer)) {
		char h_str[3];
		strncpy(h_str, buffer, 2);
		h_str[2] = '\0';
		heure = atoi(h_str);

		d_minute = buffer[3] - '0';

		printf("Heure = %d\n", heure);
		printf("Minute = %d\n", d_minute);
	} else {
		printf("ERROR");
		return 0;
	}

	clockToTime(heure, d_minute);
	return 1;
}

/**
 * @brief Convertit l'heure interne en format codé hexadécimal.
 *
 * Le format retourné encode :
 * - les 5 bits de poids fort : l’heure (0 à 23),
 * - les 3 bits de poids faible : la dizaine de minutes (0 à 5).
 *
 * @return L’heure encodée sur 8 bits.
 */
uint8_t timeToHex(){
	uint8_t heure, dizaine_minutes, ret;

	heure = u32_time / 6;
	dizaine_minutes = u32_time % 6;

	heure = (heure % 24) & 0x1F; // Limite à 5 bits
	ret = (heure << 3) | (dizaine_minutes & 0x07);

	return ret;
}

/**
 * @brief Vérifie si la chaîne est un horaire valide au format "hh:mm".
 *
 * La chaîne doit avoir exactement 5 caractères, avec un ':' à la 3e position
 * et uniquement des chiffres ailleurs.
 *
 * @param str Chaîne à tester.
 * @return true si valide, false sinon.
 */
bool is_valid_time_format(const char *str) {
	if (strlen(str) != 5) return false;
	if (str[2] != ':') return false;
	for (int i = 0; i < 5; ++i) {
		if (i == 2) continue;
		if (str[i] < '0' || str[i] > '9') return false;
	}
	return true;
}

/**
 * @brief Définit l'heure interne à partir d'une heure et dizaine de minutes.
 *
 * Calcule la valeur interne à partir de l’heure (0 à 23) et
 * de la dizaine de minutes (0 à 5).
 *
 * @param heure Heure (0 à 23).
 * @param minute Dizaine de minutes (0 à 5).
 */
void clockToTime(uint8_t heure, uint8_t minute){
	u32_time = ((heure * 6) + minute);
}
