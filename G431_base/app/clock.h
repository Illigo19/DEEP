/*
 * clock.h
 *
 *  Created on: May 28, 2025
 *      Author: chinabni
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdint.h>

/**
 * @brief Incrémente l'heure interne de 10 minutes.
 *
 * Cette fonction ajoute une unité à la variable interne représentant l'heure.
 * Chaque unité correspond à une dizaine de minutes.
 */
void addDecade(void);

/**
 * @brief Convertit l'heure interne en format hexadécimal encodé.
 *
 * L'heure est codée sur 8 bits :
 * - 5 bits pour les heures (0 à 23)
 * - 3 bits pour les dizaines de minutes (0 à 5)
 *
 * @return L'heure encodée sous forme d'un octet.
 */
uint8_t timeToHex(void);

/**
 * @brief Définit l'heure interne à partir d'une saisie utilisateur via UART.
 *
 * Attend une entrée au format "hh:mm", la valide, et l'enregistre si correcte.
 *
 * @return 1 si l'heure est correctement définie, 0 sinon.
 */
int setClock(void);

#endif /* CLOCK_H_ */
