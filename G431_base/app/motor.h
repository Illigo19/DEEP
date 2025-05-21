/**
 * @file motor.h
 * @brief Interface pour le contrôle d’un moteur DC via le module MotorDC.
 *
 * Fournit des fonctions pour initialiser le moteur, le faire tourner dans un sens
 * ou dans l’autre, ainsi que pour l’arrêter. Utilise le module BSP MotorDC STM32G4.
 *
 * @author chinabni
 * @date 9 avril 2025
 */
#ifndef MOTOR_H_
#define MOTOR_H_

#include "config.h"
#include "./MotorDC/stm32g4_motorDC.h"

/**
 * @brief Initialise le moteur DC.
 *
 * Configure les broches GPIO nécessaires et ajoute le moteur au BSP.
 * À appeler une seule fois avant toute commande moteur.
 */
void motor_init(void);


/**
 * @brief Fait tourner le moteur dans le sens de retour de la carte.
 *
 * Envoie un duty cycle négatif pour inverser le sens de rotation.
 */
void motor_retourCarte(void);

/**
 * @brief Fait tourner le moteur pour insérer la carte.
 *
 * Envoie un duty cycle positif pour faire avancer le moteur.
 */
void motor_insertCarte(void);

/**
 * @brief Arrête complètement le moteur.
 *
 * Coupe le duty cycle à zéro pour arrêter le mouvement.
 */
void motor_stopMotor(void);

#endif /* MOTOR_H_ */
