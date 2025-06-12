/**
 *******************************************************************************
 * @file 	main.c
 * @author 	jjo
 * @date 	Mar 29, 2024
 * @brief	Fichier principal de votre projet sur carte Nucléo STM32G431KB
 *******************************************************************************
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
#include <stdio.h>
#include <inttypes.h>


#define POSITION_OUVERT	200
#define POSITION_FERME 	100



static volatile uint32_t t = 600000;

typedef enum{
	INIT = 0,
	ATTENTE_CARTE,
	DISTRIBUTION_BALLE,
	ATTENTE_BALLE,
	DISTRIBUTION_CARTE
}state_e;
typedef enum{
	FALSE = 0,
	TRUE
}bool_e;


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
  * @brief  Point d'entrée de votre application
  */
int main(void)
{
	static state_e state = INIT ;
	static state_e previous_state  = INIT ;
	static bool_e prev_carte_attente = FALSE;
	static bool_e prev_carte_distribution = FALSE;
	static int curr_carte;
	bool_e entrance;
	HAL_Init();
	BSP_GPIO_enable();
	BSP_UART_init(UART2_ID,115200);
	BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);
	BSP_systick_add_callback_function(&process_ms);

	while (1)
	{
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
				printf("%d", state);
				setClock();

				state = ATTENTE_CARTE;
				break;

			case ATTENTE_CARTE:
			{
			    bool_e curr_carte = MOUSTACHE_carte_presente();

			    if (entrance)
			        printf("%d", state);


			    if (!prev_carte_attente && curr_carte)
			    {
			        motor_insertCarte();
			        do {
			            waitTag();
			        } while (!receiveTag());
			        motor_stopMotor();
			        uint64_t UID;
					//UID = getTag();
			        uint8_t time = timeToHex();
			        FLASH_write_UID(UID, time);

			        state = DISTRIBUTION_BALLE;
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
