/**
 * @file capteurs.h
 * @brief Interface de gestion des capteurs moustaches et du bouton.
 *
 * Ce module permet d'initialiser les capteurs connectés aux broches GPIO,
 * et de vérifier la présence d'une carte, d'une balle, ou d'un appui bouton.
 *
 * @author chinabni
 * @date 2 avril 2025
 */
#ifndef CAPTEURS_H_
#define CAPTEURS_H_

#include "stm32g4xx_hal.h"
#include "config.h"


/**
 * @brief Initialise les broches GPIO utilisées par les capteurs.
 *
 * Configure les broches en mode entrée sans pull-up/pull-down.
 * Broches utilisées :
 * - GPIOB PIN 7 : Capteur carte
 * - GPIOA PIN 15 : Capteur balle
 * - GPIOA PIN 1 : bouton secours

 */
void CAPTEUR_init(void);

/**
 * @brief Vérifie si une carte est détectée par le capteur.
 *
 * Lit l’état de la broche GPIOB PIN 7.
 *
 * @retval 1 Carte présente (capteur activé)
 * @retval 0 Carte absente
 */
int MOUSTACHE_carte_presente(void);

/**
 * @brief Vérifie si une balle est détectée par le capteur.
 *
 * Lit l’état de la broche GPIOA PIN 15.
 *
 * @retval 1 Balle présente (capteur activé)
 * @retval 0 Balle absente
 */
int MOUSTACHE_balle_presente(void);

/**
 * @brief Vérifie si le bouton est pressé.
 *
 * Lit l’état de la broche GPIOA PIN 1.
 *
 * @retval 1 Bouton pressé
 * @retval 0 Bouton non pressé
 */
int BOUTON_pressed(void);

#endif /* CAPTEURS_H_ */
