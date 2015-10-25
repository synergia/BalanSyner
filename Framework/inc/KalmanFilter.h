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
    float RealGyroMeasurement; 	//Measured gyro dgr/s - bias

	float dt; 	//odstêp czasu pomiedzy odczytami.

	/*! Macierz kowariancji szumu przetwarzania */
	float Q_Angle;
	float Q_GyroBias;

    float R_measure; // Measurement noise variance - this is actually the variance of the measurement noise

    float P[2][2]; // Error covariance matrix - This is a 2x2 matrix
}KalmanStruct;

typedef struct
{
	float x[2][1];
	/*!
	 * State matrix x
	 *
	 * 		|	Angle		|
	 *  x = |	GyroBias	|
	 */
}SystemStateStruct;

typedef struct
{
	float F[2][2];
	/*!
	 * StateTransitionModel F
	 *
	 * 		|	1	-dt	|
	 *  F = |	0	1	|
	 */
}StateTransitionModelStruct;

typedef struct
{
	float B[2][1];
	/*!
	 * ControlInputModel B
	 *
	 * 		|	dt	|
	 *  B = |	0	|
	 */
}ControlInputModelStruct;

typedef struct
{
	float Q[2][2];
	/*!
	 * CovarainceMatrix Q
	 *
	 * 		|	Q_Angle			0		|
	 *  Q = |		0		Q_GyroBias	|	*	 dt
	 */
}CovarianceMatrixStruct;

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
void KalmanInitialize();
float KalmanGetValue(float NewAccAngle, float NewGyroRate);

void PredictEstimateState();
void PredictEstimateCovariance();
void InnovationMeasurement();
void InnovationCovariance();
void ComputeCalmanGains();
void UpdatePosterioriState();
void UpdateCovariance();

#endif
