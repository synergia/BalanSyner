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
void InitializeMotors();
void InitializeServos();
void SetSpeed(PwmSelector PwmX, uint16_t Value);

#endif /* MOTORS_H_ */
