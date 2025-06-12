/**
 * @file flash.c
 * @brief Fonctions de gestion de la mémoire FLASH pour stockage UID et curseur.
 *
 * Implémente l’écriture d’un UID accompagné d’une date dans la mémoire FLASH,
 * ainsi que la gestion d’un curseur permettant de suivre l’emplacement d’écriture.
 */

#include "flash.h"
#include <stdio.h>
#include <stdint.h>
#include "stm32g4xx_hal.h"
#include "stm32g4_flash.h"

/**
 * @def FLASH_CURSOR_ADRESS
 * @brief Adresse en mémoire FLASH pour stocker le curseur.
 *
 * Doit être un multiple de 8 pour respecter l’alignement des écritures 64 bits.
 */
#define FLASH_CURSOR_ADRESS 248 //Multiple de 8 inférieur à 256

/**
 * @brief Récupère la valeur actuelle du curseur en mémoire FLASH.
 *
 * Le curseur indique l'adresse à laquelle le prochain UID doit être stocké.
 *
 * @return Valeur du curseur lue depuis la mémoire FLASH (0–255).
 */
uint8_t FLASH_cursor(void);

/**
 * @brief Met à jour la valeur du curseur en mémoire FLASH.
 *
 * Stocke le curseur à l'adresse définie par @ref FLASH_CURSOR_ADRESS.
 *
 * @param u8_cursor Nouvelle valeur du curseur à stocker (0–255).
 */
void FLASH_set_cursor(uint8_t);


void FLASH_write_UID(uint32_t uid_hi, uint32_t uid_lo, uint8_t date)
{
    uint64_t UID64 = ((uint64_t)uid_hi << 32) | uid_lo;
    uint64_t u64_combined = (UID64 << 8) & 0xFFFFFFFFFFFFFF00ULL;
    u64_combined |= (uint64_t)date;

    uint8_t cursor = FLASH_cursor();
    BSP_FLASH_set_doubleword(cursor, u64_combined);
    cursor++;
    FLASH_set_cursor(cursor);
}

uint8_t FLASH_cursor()
{
	uint8_t u8_cursor;
	u8_cursor = ((uint8_t)BSP_FLASH_read_doubleword(FLASH_CURSOR_ADRESS)) & 0xff;
	return u8_cursor;
}

void FLASH_set_cursor(uint8_t u8_cursor)
{
	uint64_t u64_cursor = (uint64_t)u8_cursor & 0xff;
	BSP_FLASH_set_doubleword(FLASH_CURSOR_ADRESS, u64_cursor % FLASH_CURSOR_ADRESS);
}
