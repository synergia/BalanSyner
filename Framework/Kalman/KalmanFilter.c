
//-----------------------Includes-------------------------------------//
#include "KalmanFilter.h"

//-----------------------Private typedefs------------------------------//
typedef struct
{
   /*! Zmienne stanu: x - state matrix */
   float Angle;      //Po³o¿enie k¹towe robota
   float GyroBias;      //Dryft ¿yroksopu

   /*! Odstêp czasu pomiedzy odczytami.*/
   float dt;

   /*! Rónica k¹ta odczytanego z akcelerometru i k¹ta estymowanego w
    *  poprzedniej iteracji filtra
    */
   float AngleDiff;

   /*! Wartosæ S potrzebna do wyznaczenia wzmocnienia Kalmana */
   float S;

   /*! Macierz wzmocnienia Kalmana */
   float K[2];

   /*! Macierz kowariancji szumu przetwarzania */
   float Q_Angle;

    /*! Measurement noise variance - this is actually the variance of accelerometr */
    float R_measure;

    /*! Macierz b³edu kowariancji */
    float P[2][2];
}KalmanStruct;

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//
static KalmanStruct KalmanData;
extern float DT;

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void KalmanInitialize( )
{
   KalmanData.Angle = 0.0f;   // Reset the angle
   KalmanData.GyroBias = 0.0f; // Reset bias

   KalmanData.dt = DT;

   KalmanData.Q_Angle = 0.00653f;      //varaince of gyro measurements
   KalmanData.R_measure = 0.42703f;    //measured: varaince of accelerometer data

   KalmanData.AngleDiff = 0.0f;
   KalmanData.S = 0.0f;
   KalmanData.K[0] = 0.0f;
   KalmanData.K[1] = 0.0f;

   /*!
    * Since we assume that the bias is 0 and we know the starting angle (use setAngle),
    * the error covariance matrix is set like so - see:
    * http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
    */
   KalmanData.P[0][0] = 10.0f;
   KalmanData.P[0][1] = 0.0f;
   KalmanData.P[1][0] = 0.0f;
   KalmanData.P[1][1] = 10.0f;
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
    KalmanData.P[1][1] += KalmanData.dt * KalmanData.Q_Angle;


   // Calculate angle and bias - Update estimate with measurement zk (newAngle)
   /* Step 3 */
   KalmanData.AngleDiff = NewAccAngle - KalmanData.Angle; // Angle difference

    // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
    /* Step 4 */
    KalmanData.S = KalmanData.P[0][0] + KalmanData.R_measure; // Estimate error

    // Calculate Kalman gain - Compute the Kalman gain
    /* Step 5 */
    KalmanData.K[0] = KalmanData.P[0][0] / KalmanData.S;
    KalmanData.K[1] = KalmanData.P[1][0] / KalmanData.S;

    /* Step 6 */
    KalmanData.Angle += KalmanData.K[0] * KalmanData.AngleDiff;
    KalmanData.GyroBias += KalmanData.K[1] * KalmanData.AngleDiff;

    // Calculate estimation error covariance - Update the error covariance
    /* Step 7 */
    KalmanData.P[1][1] -= KalmanData.K[1] * KalmanData.P[0][1];
    KalmanData.P[1][0] -= KalmanData.K[1] * KalmanData.P[0][0];
    KalmanData.P[0][1] -= KalmanData.K[0] * KalmanData.P[0][1];
    KalmanData.P[0][0] -= KalmanData.K[0] * KalmanData.P[0][0];

    return KalmanData.Angle;
}
