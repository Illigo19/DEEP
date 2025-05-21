/*
 * flash.h
 *
 *  Created on: Apr 11, 2025
 *      Author: chinabni
 */

#ifndef FLASH_H_
#define FLASH_H_

#include <stdio.h>
#include <stdint.h>

/**
 * @brief Écrit un UID accompagné d'une date dans la mémoire FLASH.
 *
 * Combine un identifiant UID 64 bits et une date 8 bits, puis les écrit à
 * l'adresse indiquée par le curseur. Ensuite, le curseur est incrémenté.
 *
 * @param UID Identifiant 64 bits à stocker.
 * @param date Date 8 bits à associer à l'UID (format utilisateur défini).
 */
void FLASH_write_UID(uint64_t UID, uint8_t date);

#endif /* FLASH_H_ */
