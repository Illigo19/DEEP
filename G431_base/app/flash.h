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
 * @brief �crit un UID accompagn� d'une date dans la m�moire FLASH.
 *
 * Combine un identifiant UID 64 bits et une date 8 bits, puis les �crit �
 * l'adresse indiqu�e par le curseur. Ensuite, le curseur est incr�ment�.
 *
 * @param UID Identifiant 64 bits � stocker.
 * @param date Date 8 bits � associer � l'UID (format utilisateur d�fini).
 */
void FLASH_write_UID(uint64_t UID, uint8_t date);

#endif /* FLASH_H_ */
