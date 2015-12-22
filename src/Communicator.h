/*
 * Communicator.h
 *
 *  Created on: Nov 22, 2015
 *      Author: Kuba
 */

#ifndef Communicator_H_
#define Communicator_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"

//-----------------------Public defines-------------------------------//
#define true   1
#define false  0

//-----------------------Public macros--------------------------------//

//-----------------------Public typedefs------------------------------//
typedef enum
{
   ReadKalmanQAngle     = 0u,
   ReadKalmanRMeasure   = 1u,
   ReadFilteredAngle    = 2u,
   ReadRawAngle         = 3u,
   ReadOmegaLeft        = 4u,
   ReadOmegaRight       = 5u,
   ReadPidAngleKp       = 6u,
   ReadPidAngleKi       = 7u,
   ReadPidAngleKd       = 8u,
   ReadPidOmegaKp       = 9u,
   ReadPidOmegaKi       = 18u,
   ReadPidOmegaKd       = 11u,
   ReadPidDstOmega      = 12u,

   WriteKalmanQAngleDef    = 100u,
   WriteKalmanQAngle       = 101u,
   WriteKalmanRMeasureDef  = 102u,
   WriteKalmanRMeasure     = 103u,
   WritePidAngleKp         = 104u,
   WritePidAngleKi         = 105u,
   WritePidAngleKd         = 106u,
   WritePidOmegaKp         = 107u,
   WritePidOmegaKi         = 108u,
   WritePidOmegaKd         = 109u,
   WritePidRotationKp      = 110u,
   WritePidRotationKi      = 111u,
   WritePidRotationKd      = 112u,
   WritePidDstOmega        = 113u,
   WritePidDstRotation     = 114u,
   WriteArmAngle           = 115u,
   WriteSerHor             = 116u,
   WriteSerVer             = 117u,
}Addresses_T;

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//

//-----------------------Public functions-----------------------------//

//-----------------------Public functions------------------------------//
void pub_SendCommandBT( float Value, Addresses_T Address );
uint8_t Communicator_CheckInputs();


#endif /* Communicator_H_ */
