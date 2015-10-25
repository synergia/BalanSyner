/*
 * Motors.c
 *
 *  Created on: Oct 25, 2015
 *      Author: Kuba
 */

//-----------------------Includes-------------------------------------//
#include "Motors.h"
#include "../PinDefines.h"
#include "../HAL/RCC.h"
#include "../HAL/Timers.h"
#include "../HAL/GPIO.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void InitializeMotors()
{
	InitializeRCC(SelectMotors);
	InitializeTimers(TIM_MOTORS);
	InitializeGPIO(SelectMotors);
}

void InitializeServosArm()
{
	InitializeRCC(SelectServosArm);
	InitializeTimers(TIM_SERVOS);
	InitializeGPIO(SelectServosArm);
}

void InitializeServosCam()
{
	InitializeRCC(SelectServosCam);
	InitializeTimers(TIM_SERVOS);
	InitializeGPIO(SelectServosCam);
}

/*!
 * Value may vary between 0 and 1000.
 */
void SetSpeed(PwmSelector PwmX, uint16_t Value)
{
	if(Value<=1000 && Value>=0)
	{
		switch (PwmX)
		{
		case SelectMotorLeft:
			TIM_MOTORS->MOT1_PWM_CHANNEL = Value;
			break;
		case SelectMotorRight:
			TIM_MOTORS->MOT2_PWM_CHANNEL = Value;
			break;
		default:
			break;
		}
	}

}
