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
#define ANGLE_TO_PWM_VALUE(ANGLE)	( 2*(ANGLE)+540 )

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
inline inline static void priv_SetAngleArmLeft(uint16_t Angle);
inline static void priv_SetAngleArmRight(uint16_t Angle);
inline static void priv_SetAngleCamHor(uint16_t Angle);
inline static void priv_SetAngleCamVer(uint16_t Angle);

//-----------------------Private functions-----------------------------//
inline inline static void priv_SetAngleArmLeft(uint16_t Angle)
{
	TIM_SERVOS->SERVO_ARM_L_PWM_CHANNEL = Angle;
}

inline static void priv_SetAngleArmRight(uint16_t Angle)
{
	TIM_SERVOS->SERVO_ARM_P_PWM_CHANNEL = Angle;
}

inline static void priv_SetAngleCamHor(uint16_t Angle)
{
	TIM_SERVOS->SERVO_HOR_PWM_CHANNEL = Angle;
}

inline static void priv_SetAngleCamVer(uint16_t Angle)
{
	TIM_SERVOS->SERVO_VER_PWM_CHANNEL = Angle;
}

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
void MotorSetSpeed(MotorSelector Motor, uint16_t Value, uint8_t Direction)
{
	//todo: handle direction
	if(Value<=1000 && Value>=0)
	{
		switch (Motor)
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

/*!
 * Value may vary between -90.0 and +90.0. Resolution 0.5.
 */
void ServoSetAngle(ServoSelector Servo, float Angle)
{
	if( -90>Angle ) Angle = -90;
	if(	 90<Angle ) Angle = 90;

	Angle = (uint16_t) 2*(Angle)+540;

	switch (Servo)
	{
	case SelectServoArmLeft:
		priv_SetAngleArmLeft(Angle);
		break;
	case SelectServoArmRight:
		priv_SetAngleArmRight(Angle);
		break;
	case SelectServoCamHor:
		priv_SetAngleCamHor(Angle);
		break;
	case SelectServoCamVer:
		priv_SetAngleCamVer(Angle);
		break;
	default:
		break;
	}
}
