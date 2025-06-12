/*
 * servo.c
 *
 *  Created on: Nov 5, 2024
 *      Author: charrijo
 */

#include "servo.h"
#define PERIOD_TIMER 10

static uint16_t current_position;

/**
 * @brief Initialise le servomoteur en configurant et démarrant le timer PWM.
 *
 * Configure le timer 4 pour générer un signal PWM avec une période de 10 ms.
 * Active le canal 1 (PA8) avec un rapport cyclique initial de 150 (~50%).
 */
void SERVO_init(void){
	//initialisation et lancement du timer1 à une période de 10 ms
	BSP_TIMER_run_us(TIMER4_ID, PERIOD_TIMER*1000, false);

	//activation du signal PWM sur le canal 1 du timer 1 (broche PA8)
	BSP_TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_1, 150, true, false);
	//rapport cyclique réglé pour une position servo de 50%
}

/**
 * @brief Définit la position du servomoteur.
 *
 * La position est exprimée de 0 à 100 et est appliquée au PWM.
 *
 * @param pos Position souhaitée (0–100).
 */
void SERVO_set_position(uint16_t pos){
	BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, pos);
}

/**
 * @brief Récupère la position actuelle enregistrée du servomoteur.
 *
 * @return Position actuelle (0–100).
 */
uint16_t SERVO_get_position(void){
	return current_position;
}
