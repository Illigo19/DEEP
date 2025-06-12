/*
 * motor.c
 *
 *  Created on: Apr 9, 2025
 *      Author: chinabni
 */

#include "config.h"
#include "./MotorDC/stm32g4_motorDC.h"

#define DUTY 500  ///< Valeur du rapport cyclique pour la vitesse du moteur

/// Identifiant du moteur gauche utilisé dans ce module
static motor_id_e left_motor_id;

/**
 * @brief Initialise le moteur gauche en configurant les pins GPIO correspondants.
 *
 * Cette fonction configure le moteur en initialisant l'identifiant associé
 * à partir des ports et pins définis dans la carte.
 */
void motor_init()
{
	left_motor_id = BSP_MOTOR_add(GPIOA, GPIO_PIN_0, GPIOB, GPIO_PIN_0);
}

/**
 * @brief Fait reculer la carte en activant le moteur dans le sens inverse.
 *
 * Le moteur est activé avec un rapport cyclique négatif pour inverser la rotation.
 */
void motor_retourCarte()
{
	BSP_MOTOR_set_duty(left_motor_id, -DUTY);
}

/**
 * @brief Fait avancer la carte en activant le moteur dans le sens direct.
 *
 * Le moteur est activé avec un rapport cyclique positif pour faire avancer la carte.
 */
void motor_insertCarte()
{
	BSP_MOTOR_set_duty(left_motor_id, DUTY);
}

/**
 * @brief Arrête le moteur en mettant le rapport cyclique à zéro.
 *
 * Le moteur cesse de tourner.
 */
void motor_stopMotor()
{
	BSP_MOTOR_set_duty(left_motor_id, 0);
}
