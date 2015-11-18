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

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void InitializeEncoders();
void InitializeMotors();
void InitializeServosArm();
void InitializeServosCam();
void MotorSetSpeed(MotorSelector_T Motor, uint16_t Value, uint8_t Direction);
void ServoSetAngle(ServoSelector_T Servo, float Angle);

#endif /* MOTORS_H_ */
