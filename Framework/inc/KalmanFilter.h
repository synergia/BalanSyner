#ifndef KALMANFILTER_H_
#define KALMANFILTER_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"

//-----------------------Public typedefs------------------------------//

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void KalmanInitialize();
float KalmanGetValue(float NewAccAngle, float NewGyroRate);

#endif
