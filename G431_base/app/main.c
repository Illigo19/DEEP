/**
 ******************************************************************************
 * @file 	main.c
 * @author 	jjo
 * @date 	Mar 29, 2024
 * @brief	Fichier principal de votre projet sur carte Nucléo STM32G431KB
 ******************************************************************************
 */

#include "stm32g4_sys.h"

#include <capteurs.h>
#include "config.h"
#include "stm32g4_sys.h"
#include "stm32g4_systick.h"
#include "stm32g4_uart.h"
#include "stm32g4_utils.h"
#include "stm32g4_gpio.h"
#include "./MotorDC/stm32g4_motorDC.h"
#include "./NFC03A1/stm32g4_nfc03a1.h"
#include "./tft_ili9341/stm32g4_ili9341.h"
#include "servo.h"
#include "motor.h"
#include "flash.h"
#include "clock.h"
#include "nfc.h"
#include "ecran.h"

#include <stdio.h>
#include <inttypes.h>

#define POSITION_OUVERT	200  ///< Position d’ouverture du servo-moteur
#define POSITION_FERME 	100  ///< Position de fermeture du servo-moteur

static volatile uint32_t t = 600000;  ///< Compteur pour minuterie logicielle

/**
 * @enum state_e
 * @brief États principaux de l'automate
 */
typedef enum {
	INIT = 0,              ///< Initialisation
	ATTENTE_CARTE,         ///< Attente d’une carte NFC
	DISTRIBUTION_BALLE,    ///< Distribution d’une balle
	ATTENTE_BALLE,         ///< Attente que la balle soit retirée
	DISTRIBUTION_CARTE     ///< Retour de la carte
} state_e;

/**
 * @enum bool_e
 * @brief Type booléen personnalisé (équivalent à bool)
 */
typedef enum {
	FALSE = 0,  ///< Faux
	TRUE        ///< Vrai
} bool_e;

/**
 * @brief Fonction appelée périodiquement via le systick
 *
 * Gère une minuterie logicielle et déclenche l’ajout d’une décennie
 * quand elle expire.
 */
void process_ms(void)
{
	if(t)
	{
		t--;
	}
	else
	{
		t = 600000;
		addDecade();
	}
}


/**
 * @brief Point d'entrée principal de l'application embarquée
 *
 * Gère un automate d’état permettant d’interagir avec des cartes NFC,
 * un servo-moteur, un moteur DC, un capteur de balle et un écran TFT.
 *
 * @return int Ne retourne jamais normalement (boucle infinie)
 */
int main(void)
{
	static state_e state = INIT ;
	static state_e previous_state  = INIT ;
	static bool_e prev_carte_attente = FALSE;
	static bool_e prev_carte_distribution = FALSE;
	static int curr_carte;
	bool_e entrance;

	// Initialisations matérielles
	HAL_Init();
	BSP_GPIO_enable();
	BSP_UART_init(UART2_ID,115200);
	BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);
	BSP_systick_add_callback_function(&process_ms);

	while (1)
	{
		// Détection d’un changement d’état
		entrance = (previous_state != state)?TRUE:FALSE;
		previous_state = state;

		switch(state)
		{
			case(INIT):
				SERVO_init();
				CAPTEUR_init();
				motor_init();
				nfc_init();
				ILI9341_Init();
				ecranBienvenue();
				printf("%d", state);
				setClock();
				state = ATTENTE_CARTE;
				break;

			case ATTENTE_CARTE:
			{
				uint32_t UID_hi, UID_lo;
			    bool_e curr_carte = MOUSTACHE_carte_presente();

			    if (entrance){
			        printf("%d", state);
			        ecranAttenteCarte();
			    }

			    if (!prev_carte_attente && curr_carte)
			    {
			        motor_insertCarte();
			        do {
			            waitTag();
			        } while (!receiveTag());
			        motor_stopMotor();

					getTag(&UID_hi, &UID_lo);
					uint8_t time = timeToHex();
					FLASH_write_UID(UID_hi, UID_lo, time);

			        state = DISTRIBUTION_BALLE;
			        ecranPartie();
			    }
			    else{
			    	state = ATTENTE_CARTE;
			    }

			    prev_carte_attente = curr_carte;
			}
			break;

			case(DISTRIBUTION_BALLE):
				if(entrance){
					printf("%d", state);
					ecranBalleRecup();
					SERVO_set_position(POSITION_OUVERT);
				}

				if(!MOUSTACHE_balle_presente())
				{
					state = ATTENTE_BALLE;
				}else{
					state = DISTRIBUTION_BALLE;
				}
				break;

			case(ATTENTE_BALLE):
				if(entrance){
					printf("%d", state);
					ecranAttenteBalle();
					ecranEnService();
					SERVO_set_position(POSITION_FERME);
				}

				if(!MOUSTACHE_balle_presente())
				{
					state = ATTENTE_BALLE;
				}else{
					state = DISTRIBUTION_CARTE;
				}
				break;

			case(DISTRIBUTION_CARTE):
				curr_carte = MOUSTACHE_carte_presente();

				if(entrance){
					printf("%d", state);
					ecranCarteRecup();
					motor_retourCarte();
				}

				if(prev_carte_distribution && !curr_carte){
					motor_stopMotor();
					state = ATTENTE_CARTE;
				}
				else{
					state = DISTRIBUTION_CARTE;
				}
				prev_carte_distribution = curr_carte;
				break;
		}
	}
}
