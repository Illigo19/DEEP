/**
 *******************************************************************************
 * @file 	main.c
 * @author 	jjo
 * @date 	Mar 29, 2024
 * @brief	Fichier principal de votre projet sur carte Nucléo STM32G431KB
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
#include "./NFC03A1/stm32g4_nfc03a1.h"

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

void process_ms(void)
{
	if(t)
	{
		t--;
	}
	else
	{
		t = 600000;
	}
}




/**
  * @brief  Point d'entrée de votre application
  */
int main(void)
{

 	HAL_Init();

	BSP_GPIO_enable();
	BSP_UART_init(UART2_ID,115200);
	BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);
	BSP_systick_add_callback_function(&process_ms);
	SERVO_init();
	CAPTEUR_init();
	motor_init();
	nfc_init();





	while (1)
	{
		do {
		    waitTag();
		} while (!receiveTag());

		 printf("%" PRIX64 ,getTag());
	}
}
