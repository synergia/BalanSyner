/*
 * Motors.c
 *
 *  Created on: Oct 25, 2015
 *      Author: Kuba
 */

//-----------------------Includes-------------------------------------//
#include "Motors.h"
#include "../PinDefines.h"
#include "../StmPeriphInit/RCC.h"
#include "../StmPeriphInit/Timers.h"
#include "../StmPeriphInit/GPIO.h"
#include "../StmPeriphInit/NVIC.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//
#define ANGLE_TO_PWM_VALUE(ANGLE)	( 2*(ANGLE)+540 )

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
static void priv_MotorSetSpeed(MotorSelector_T Motor, uint16_t Value, uint8_t Direction);
static void priv_ServoSetAngle(ServoSelector_T Servo, float Angle);

inline static void priv_SetAngleArmLeft(uint16_t Angle);
inline static void priv_SetAngleArmRight(uint16_t Angle);
inline static void priv_SetAngleCamHor(uint16_t Angle);
inline static void priv_SetAngleCamVer(uint16_t Angle);

//-----------------------Private functions-----------------------------//
inline static void priv_SetAngleArmLeft(uint16_t Angle)
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
void InitializeEncoders()
{
	/*! Physical initialization */
	InitializeRCC(DriverSelectEncoders);
	InitializeNVIC(DriverSelectEncoders);
	InitializeTimers(TIM_ENC1);
	InitializeTimers(TIM_ENC2);
	InitializeGPIO(DriverSelectEncoders);

	/*! Software */
	EncodersStruct.GetOmega = GetCounter;
	EncodersStruct.SetOmega = SetCounter;
}

void InitializeMotors()
{
	/*! Physical initialization */
	InitializeRCC(DriverSelectMotors);
	InitializeTimers(TIM_MOTORS);
	InitializeGPIO(DriverSelectMotors);

	/*! Software */
	MotorStruct.SetSpeed = priv_MotorSetSpeed;
}

void InitializeServosArm()
{
	/*! Physical initialization */
	InitializeRCC(DriverSelectServosArm);
	InitializeTimers(TIM_SERVOS);
	InitializeGPIO(DriverSelectServosArm);
}

void InitializeServosCam()
{
	/*! Physical initialization */
	InitializeRCC(DriverSelectServosCam);
	InitializeTimers(TIM_SERVOS);
	InitializeGPIO(DriverSelectServosCam);
}

/*!
 * Value may vary between 0 and 1000.
 */
void priv_MotorSetSpeed(MotorSelector_T MotorSelector, uint16_t Value, uint8_t Direction)
{
	//todo: handle direction
	if(Value<=1000 && Value>=0)
	{
		switch (MotorSelector)
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
void priv_ServoSetAngle(ServoSelector_T ServoSelector, float Angle)
{
	if( -90>Angle ) Angle = -90;
	if(	 90<Angle ) Angle = 90;

	Angle = (uint16_t) 2*(Angle)+540;

	switch (ServoSelector)
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
