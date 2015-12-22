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
   uint8_t BatteryDischarged;       /*! true if battery voltage is above set point */
   uint8_t RobotStanding;           /*! true if filtered angle is in standing range */
   uint8_t ConnectionEstablished;   /*! true if received message is last checking input iteration */
   uint8_t PlatformInRange;         /*! true if angle is in safe range */
   uint8_t Moving;                  /*! true if OmegaDst or rotation differ from 0 */
}RobotStates_T;

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//

#endif /* Logic_H_ */
