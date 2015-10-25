
//-----------------------Includes-------------------------------------//
#include "KalmanFilter.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//
static KalmanStruct KalmanData;

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void KalmanInitialize()
{
    /* We will set the variables like so, these can also be tuned by the user */
    KalmanData.Q_Angle = 0.00653f;		//varaince of gyro measurements
    KalmanData.Q_GyroBias = 0.0007f; 	//MNP
    KalmanData.R_measure = 0.42703f;	//measured: varaince of accelerometer data

    KalmanData.dt = 0.032f;

    KalmanData.Angle = 0.0f; // Reset the angle
    KalmanData.GyroBias = 0.0f; // Reset bias

    KalmanData.P[0][0] = 0.0f; // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
    KalmanData.P[0][1] = 0.0f;
    KalmanData.P[1][0] = 0.0f;
    KalmanData.P[1][1] = 0.0f;
}

float KalmanGetValue(float NewAccAngle, float NewGyroRate)
{
    // See my blog post for more information: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it
	// V1 Modified by Kristian Lauszus
	// V2 Modified by Jakub Trzyna

	// Discrete Kalman filter time update equations - Time Update ("Predict")
    // Update xhat - Project the state ahead
    /* Step 1 */
	KalmanData.Angle += KalmanData.dt * (NewGyroRate - KalmanData.GyroBias);


    // Update estimation error covariance - Project the error covariance ahead
    /* Step 2 */
    KalmanData.P[0][0] +=KalmanData.dt * (KalmanData.dt*KalmanData.P[1][1] - KalmanData.P[0][1] - KalmanData.P[1][0] + KalmanData.Q_Angle);
    KalmanData.P[0][1] -= KalmanData.dt * KalmanData.P[1][1];
    KalmanData.P[1][0] -= KalmanData.dt * KalmanData.P[1][1];
    KalmanData.P[1][1] += KalmanData.dt * KalmanData.Q_GyroBias;


	// Calculate angle and bias - Update estimate with measurement zk (newAngle)
	/* Step 3 */
	float AngleDiff = NewAccAngle - KalmanData.Angle; // Angle difference

    // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
    // Calculate Kalman gain - Compute the Kalman gain
    /* Step 4 */
    float S = KalmanData.P[0][0] + KalmanData.R_measure; // Estimate error

    /* Step 5 */
    float K[2]; // Kalman gain - This is a 2x1 vector
    K[0] = KalmanData.P[0][0] / S;
    K[1] = KalmanData.P[1][0] / S;

    /* Step 6 */
    KalmanData.Angle += K[0] * AngleDiff;
    KalmanData.GyroBias += K[1] * AngleDiff;

    // Calculate estimation error covariance - Update the error covariance
    /* Step 7 */
    KalmanData.P[1][1] -= K[1] * KalmanData.P[0][1];
    KalmanData.P[1][0] -= K[1] * KalmanData.P[0][0];
    KalmanData.P[0][1] -= K[0] * KalmanData.P[0][1];
    KalmanData.P[0][0] -= K[0] * KalmanData.P[0][0];

    return KalmanData.Angle;
}
