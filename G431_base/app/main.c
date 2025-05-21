/**
 *******************************************************************************
 * @file 	main.c
 * @author 	jjo
 * @date 	Mar 29, 2024
 * @brief	Fichier principal de votre projet sur carte Nucl√©o STM32G431KB
 *******************************************************************************
 */

#include <capteurs.h>
#include "config.h"
#include "stm32g4_sys.h"

#include "stm32g4_systick.h"

#include "stm32g4_uart.h"
#include "stm32g4_utils.h"
#include "stm32g4_gpio.h"
#include "./MotorDC/stm32g4_motorDC.h"

#include "servo.h"
#include "motor.h"
#include "flash.h"
#include <stdio.h>


#define POSITION_OUVERT	200
#define POSITION_FERME 	100



static volatile uint32_t t = 60000;

void process_ms(void)
{
	if(t)
	{
		t--;
	}
	else
	{
		t = 60000;
	}
}




/**
  * @brief  Point d'entr√©e de votre application
  */
int main(void)
{
	/* Cette ligne doit rester la premi√®re de votre main !
	 * Elle permet d'initialiser toutes les couches basses des drivers (Hardware Abstraction Layer),
	 * condition pr√©alable indispensable √† l'ex√©cution des lignes suivantes.
	 */
 	HAL_Init();
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)){
			HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, false);
		}
		else
		{
			HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, true);
		}

	/* Initialisation des p√©riph√©riques utilis√©s dans votre programme */
	BSP_GPIO_enable();

	BSP_UART_init(UART2_ID,115200);

	/* Indique que les printf sont dirigÈs vers l'UART2 */
	BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	/* On ajoute la fonction process_ms ‡ la liste des fonctions appelÈes automatiquement
		 * chaque ms par la routine d'interruption du pÈriphÈrique Systick */
	BSP_systick_add_callback_function(&process_ms);

	SERVO_init();

	CAPTEUR_init();

	motor_init();

	FLASH_write_UID(0x066a3bb2e07180, 0x12);

	while (1)
	{

		motor_retourCarte();
		HAL_Delay(500);
		motor_insertCarte();
		HAL_Delay(500);
		motor_stopMotor();
		HAL_Delay(500);

	}
}
