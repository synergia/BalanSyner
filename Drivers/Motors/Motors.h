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
}EncoderStruct_T;

typedef struct
{
	void (*SetSpeed)( MotorSelector_T Motor, uint16_t Value, uint8_t Direction );
}MotorsStruct_T;
//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//
EncoderStruct_T EncodersStruct;
MotorsStruct_T MotorStruct;

//-----------------------Public prototypes----------------------------//
void InitializeEncoders();
void InitializeMotors();
void InitializeServosArm();
void InitializeServosCam();

#endif /* MOTORS_H_ */
