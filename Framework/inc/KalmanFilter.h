#ifndef KALMANFILTER_H_
#define KALMANFILTER_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"

//-----------------------Public typedefs------------------------------//
typedef struct
{
	/*! Zmienne stanu: x - state matrix */
	float Angle;				//po³ozenie katowe robota
	float GyroBias;				//dryft zyroksopu

	float dt; 	//odstêp czasu pomiedzy odczytami.

	/*! Macierz kowariancji szumu przetwarzania */
	float Q_Angle;
	float Q_GyroBias;

    float R_measure; // Measurement noise variance - this is actually the variance of the measurement noise

    float P[2][2]; // Error covariance matrix - This is a 2x2 matrix
}KalmanStruct;

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void KalmanInitialize();
float KalmanGetValue(float NewAccAngle, float NewGyroRate);

#endif
