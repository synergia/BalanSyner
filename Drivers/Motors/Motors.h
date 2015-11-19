/*
 * Motors.h
 *
 *  Created on: Oct 25, 2015
 *      Author: Kuba
 */

#ifndef MOTORS_H_
#define MOTORS_H_

//-----------------------Includes-------------------------------------//
#include "../PinDefines.h"

//-----------------------Public typedefs------------------------------//
typedef struct
{
	float EncoderOmegaLeft;
	float EncoderOmegaRight;

	uint32_t (*GetOmega)( TIM_TypeDef * TIMx );
	void (*SetOmega)( TIM_TypeDef * TIMx, uint32_t Value);
}EncoderClass_T;

typedef struct
{
	//TODO void get speed
	void (*SetSpeed)( MotorSelector_T Motor, uint16_t Value, uint8_t Direction );
}MotorsClass_T;

typedef struct
{
	//TODO void get angle
	void (*SetAngle)(ServoSelector_T ServoSelector, float Angle);
}ServosClass_T;

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//
EncoderClass_T oEncoders;
MotorsClass_T oMotor;
ServosClass_T oServosArm;

//-----------------------Public prototypes----------------------------//
void InitializeEncoders();
void InitializeMotors();
void InitializeServos();

#endif /* MOTORS_H_ */
