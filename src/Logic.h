/*
 * Logic.h
 *
 *  Created on: Nov 22, 2015
 *      Author: Kuba
 */

#ifndef Logic_H_
#define Logic_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private typedefs------------------------------//
typedef struct
{
   uint8_t  BatteryDischarged;
   uint8_t  RobotStanding;
   uint8_t  ConnectionEstablished;
}RobotStates_T;

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//

#endif /* Logic_H_ */
