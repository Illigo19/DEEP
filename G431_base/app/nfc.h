/*
 * nfc.h
 *
 *  Created on: Jun 6, 2025
 *      Author: chinabni
 */

#ifndef NFC_H_
#define NFC_H_

#include <stdio.h>
#include <stdint.h>

/**
 * @brief Initialise la communication UART avec le lecteur NFC.
 *
 * Cette fonction configure l'UART1 pour recevoir les données des tags NFC à 9600 bauds.
 */
void nfc_init(void);

/**
 * @brief Indique si un tag NFC complet a été reçu.
 *
 * @return 1 si un tag a été reçu, 0 sinon.
 */
int receiveTag(void);

/**
 * @brief Récupère la valeur du tag NFC reçu.
 *
 * Convertit les données stockées dans le buffer en un entier 64 bits.
 *
 * @return La valeur du tag sous forme d'entier non signé 64 bits.
 */
uint64_t getTag(void);

/**
 * @brief Attend et traite la réception d’un tag NFC.
 *
 * Cette fonction lit les caractères reçus par l’UART et les enregistre dans un buffer
 * jusqu’à ce qu’un tag complet soit détecté.
 */
void waitTag(void);

#endif /* NFC_H_ */
