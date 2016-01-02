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
   RobotStateUser_LiesDown,
   RobotStateUser_StandsUp,
   RobotStateUser_Balancing
}RobotStateUser_T;

/*! States that depends on measurements from MPU */
typedef enum
{
   SequenceBalancing_Wait1600ms,
   SequenceBalancing_StandsUp,
   SequenceBalancing_Balances
}SequenceBalancing_T;

typedef enum
{
   SequenceLyingDown_SpreadArms,
   SequenceLyingDown_TiltBack,
   SequenceLyingDown_MotorsOff,
   SequenceLyingDown_ArmsDown,
   SequenceLyingDown_ArmsUp,
}SequenceLyingDown_T;

typedef struct
{
   bool BatteryDischarged;       /*! true if battery voltage is above set point */
   bool ConnectionEstablished;   /*! true if received message is last checking input iteration */
   bool IsPlatformInRange;         /*! true if angle is in safe range */

   /*! Only available when StateActual == Balancing */
   bool IsMoving;                  /*! true if OmegaDst or rotation differ from 0 */
   bool IsInStandingRange;
   bool IsBalancing;
   bool IsLying;

   uint8_t StateUserRequested;   /*! Type of RobotStateUser_T */

   uint8_t SequenceBalancing;
   uint8_t SequenceLyingDown;

}RobotProperties_T;

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//

//-----------------------Public functions------------------------------//

#endif /* RobotStates_H_ */
