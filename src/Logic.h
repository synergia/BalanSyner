/*
 * Logic.h
 *
 *  Created on: Nov 22, 2015
 *      Author: Kuba
 */

#ifndef LOGIC_H_
#define LOGIC_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private typedefs------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void Logic_CheckInputs();

void priv_WriteKalmanQAngle(uint8_t *Command);
void priv_ReadKalmanQAngle();

#endif /* LOGIC_H_ */
