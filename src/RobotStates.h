/*
 * RobotStates.h
 *
 *  Created on: Nov 22, 2015
 *      Author: Kuba
 */

#ifndef RobotStates_H_
#define RobotStates_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include <stdbool.h>

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public typedefs------------------------------//
/*! States that can only be changed by user, using command */
typedef enum
{
   StateRequested_LiesDown,
   StateRequested_StandsUp,
   StateRequested_Balancing
}StateRequested_T;

/*! States that can be reached by robot */
typedef enum
{
   RobotStates_WaitForStanding,
   RobotStates_StandsUp,
   RobotStates_Balances,
   RobotStates_LiesDown,
   RobotStates_ArmsBackDown
}RobotStates_T;

typedef struct
{
   bool BatteryDischarged;       /*! true if battery voltage is above set point */
   bool ConnectionEstablished;   /*! true if received message is last checking input iteration */
   bool IsPlatformInRange;       /*! true if angle is in safe range */

   /*! Only available when StateActual == Balancing */
   bool IsMoving;                  /*! true if OmegaDst or rotation differ from 0 */
   bool IsInStandingRange;
   bool IsBalancing;
   bool IsLying;

   uint16_t Timer_StandingUp;
   uint16_t Timer_BalToStand;
   StateRequested_T StateRequested;   /*! Type of StateRequested_T */
   RobotStates_T StateActive;

}RobotProperties_T;

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//

//-----------------------Public functions------------------------------//

#endif /* RobotStates_H_ */
