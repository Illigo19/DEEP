/*
 * moustache.c
 *
 *  Created on: Apr 2, 2025
 *      Author: chinabni
 */


#include <capteurs.h>
#include "stm32g4_gpio.h"

void CAPTEUR_init()
{
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_7, GPIO_MODE_INPUT, GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_5, GPIO_MODE_INPUT, GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);
	BSP_GPIO_pin_config(GPIOA, GPIO_PIN_1, GPIO_MODE_INPUT, GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);
}


int MOUSTACHE_carte_presente()
{
	return !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7);
}


int MOUSTACHE_balle_presente()
{
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)){
		return 0;
	}
	else
	{
		return 1;
	}
}


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


