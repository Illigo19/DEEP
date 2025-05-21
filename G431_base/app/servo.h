/**
 * @file servo.h
 * @brief Interface de contrôle d’un servomoteur via PWM avec le timer STM32.
 *
 * Fournit des fonctions pour initialiser le servomoteur, définir sa position
 * et lire la position actuelle. Utilise le timer 4 pour générer le signal PWM.
 *
 * @author charrijo
 * @date 5 novembre 2024
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "config.h"
#include "stm32g4_timer.h"
#include "stm32g4_uart.h"
#include "stm32g4_utils.h"

/**
 * @def PERIOD_TIMER
 * @brief Période du timer en millisecondes pour le signal PWM du servomoteur.
 */
#define PERIOD_TIMER 10

/**
 * @brief Initialise le servomoteur et configure le timer.
 *
 * Configure le timer 4 pour générer un signal PWM sur le canal 1 (broche PA8).
 * La période est fixée à 10 ms. Le rapport cyclique initial correspond à 50 %.
 */
void SERVO_init(void);

/**
 * @brief Définit la position du servomoteur.
 *
 * La position est exprimée en pourcentage (0 à 100), qui est convertie
 * en rapport cyclique pour le signal PWM.
 *
 * @param pos Position souhaitée du servomoteur (0–100).
 */
void SERVO_set_position(uint16_t pos);


/**
 * @brief Récupère la position actuelle enregistrée du servomoteur.
 *
 * @return Position actuelle (0–100).
 */
uint16_t SERVO_get_position(void);

#endif /* SERVO_H_ */
