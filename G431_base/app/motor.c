/*
 * motor.c
 *
 *  Created on: Apr 9, 2025
 *      Author: chinabni
 */

#include "config.h"
#include "./MotorDC/stm32g4_motorDC.h"

#define DUTY 500

static motor_id_e left_motor_id;

void motor_init()
{
	left_motor_id = BSP_MOTOR_add(GPIOA, GPIO_PIN_0, GPIOB, GPIO_PIN_0);
}



void motor_retourCarte()
{
	BSP_MOTOR_set_duty(left_motor_id, -DUTY);
}

void motor_insertCarte()
{
	//BSP_MOTOR_set_duty(left_motor_id, DUTY);
	BSP_MOTOR_set_duty(left_motor_id, DUTY);
}

void motor_stopMotor()
{
	BSP_MOTOR_set_duty(left_motor_id, 0);
}
