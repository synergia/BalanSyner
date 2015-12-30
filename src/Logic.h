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
/*! States that are requested from the application */
typedef enum
{
   RobotStateRequested_LiesDown,       /*! definite state, arms are not moving, motors off */
   RobotStateRequested_StandingUp,     /*! temporary state, arms are moving, motors off */
   RobotStateRequested_StandsUp,       /*! definite state, arms are not moving, motors off */
   RobotStateRequested_Balancing,      /*! definite state, arms are not moving, motors on */
   RobotStateRequested_LyingDown,     /*! temporary state, arms are moving, motors off */
}RobotStatesRequested_T;

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
   RobotStateActual_LiesDown,
   RobotStateActual_StandsUp,
   RobotStateActual_Unspecified
}RobotStatesActual_T;

typedef struct
{
   uint8_t BatteryDischarged;       /*! true if battery voltage is above set point */
   uint8_t ConnectionEstablished;   /*! true if received message is last checking input iteration */
   uint8_t PlatformInRange;         /*! true if angle is in safe range */

   /*! Only available when StateActual == Balancing */
   uint8_t Moving;                  /*! true if OmegaDst or rotation differ from 0 */

   uint8_t StateUserRequested;   /*! Type of RobotStateUser_T */
   uint8_t StateRequested;       /*! Type of RobotStateUser_T */
   uint8_t StateActual;          /*! Type of RobotStatesActual_T */
}RobotProperties_T;

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//

#endif /* Logic_H_ */
