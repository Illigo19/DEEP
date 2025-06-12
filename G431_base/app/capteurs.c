/*
 * moustache.c
 *
 *  Created on: Apr 2, 2025
 *      Author: chinabni
 */

#include <capteurs.h>
#include "stm32g4_gpio.h"

/**
 * @brief Initialise les broches GPIO utilisées par les capteurs.
 *
 * Cette fonction configure trois broches en mode entrée sans pull-up/pull-down :
 * - PB7 : pour détecter la présence de la carte.
 * - PA15 : pour détecter la présence d'une balle.
 * - PA1 : pour détecter l'appui sur un bouton.
 */
void CAPTEUR_init()
{
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_7, GPIO_MODE_INPUT, GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);
	BSP_GPIO_pin_config(GPIOA, GPIO_PIN_15, GPIO_MODE_INPUT, GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);
	BSP_GPIO_pin_config(GPIOA, GPIO_PIN_1, GPIO_MODE_INPUT, GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);
}

/**
 * @brief Vérifie si une carte est présente.
 *
 * Lit l'état de la broche PB7. La carte est considérée comme présente
 * si le niveau logique est bas (broche à 0).
 *
 * @return 1 si une carte est présente, 0 sinon.
 */
int MOUSTACHE_carte_presente()
{
	return !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7);
}

/**
 * @brief Vérifie si une balle est présente.
 *
 * Lit l'état de la broche PA15. Une balle est considérée comme présente
 * si le niveau logique est bas (broche à 0).
 *
 * @return 1 si une balle est présente, 0 sinon.
 */
int MOUSTACHE_balle_presente()
{
	return !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);
}

/**
 * @brief Vérifie si le bouton est pressé.
 *
 * Lit l'état de la broche PA1. Le bouton est considéré comme pressé
 * si le niveau logique est bas (broche à 0).
 *
 * @return 1 si le bouton est pressé, 0 sinon.
 */
int BOUTON_pressed()
{
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)){
		return 0;
	}
	else
	{
		return 1;
	}
}
