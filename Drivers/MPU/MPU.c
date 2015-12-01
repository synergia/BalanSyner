
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "_LibMPU6050.h"
#include "MPU.h"
#include "GPIO.h"
#include "I2C.h"
#include "RCC.h"
#include "../Framework/Kalman/KalmanFilter.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
static void priv_MpuGetFilteredData();
static void priv_MpuGetRawData();

static float priv_ReadKalmanQAngle();
static float priv_ReadKalmanRMeasure();
static void priv_WriteKalmanQAngle( float Value );
static void priv_WriteKalmanQAngleDef();
static void priv_WriteKalmanRMeasure( float Value );
static void priv_WriteKalmanRMeasureDef();

//-----------------------Private functions-----------------------------//
/*!
 *  Saves measured data into MpuMeasuredData struct and prepares data for Kalman filtering in MpuKalmanData struct
 */
static void priv_MpuGetFilteredData()
{
   priv_MpuGetRawData();
   oMpuKalman.AngleFiltered = KalmanGetValue( oMpuKalman.AngleRaw, oMpuKalman.GyroRaw );
}

static void priv_MpuGetRawData()
{
   MPU6050_Get_AccAngleXZ_Data( &oMpuKalman.AngleRaw );
   MPU6050_Get_GyroY_Data( &oMpuKalman.GyroRaw ); //Gyro [deg/second]
}

static float priv_ReadKalmanQAngle()
{
   return KalmanGetQAngle();
}

static float priv_ReadKalmanRMeasure()
{
   return KalmanGetRMeasure();
}

static void priv_WriteKalmanQAngle( float Value )
{
   KalmanSetQAngle( Value );
}

static void priv_WriteKalmanRMeasure( float Value )
{
   KalmanSetRMeasure( Value );
}

static void priv_WriteKalmanQAngleDef()
{
   KalmanSetQAngleDef();
}

static void priv_WriteKalmanRMeasureDef()
{
   KalmanSetRMeasureDef();
}

//-----------------------Public functions------------------------------//
MPU6050_errorstatus InitializeMPU()
{
   MPU6050_errorstatus errorstatus;
   InitializeRCC( DriverSelectMpu );
   InitializeI2C();
   InitializeGPIO( DriverSelectMpu );
   errorstatus = MPU6050_Initialization();

   KalmanInitialize();

   oMpuKalman.ApplyFilter = priv_MpuGetFilteredData;

   oMpuKalman.GetKalmanQAngle = priv_ReadKalmanQAngle;
   oMpuKalman.GetKalmanRMeasure = priv_ReadKalmanRMeasure;
   oMpuKalman.SetKalmanQAngle = priv_WriteKalmanQAngle;
   oMpuKalman.SetKalmanQAngleDef = priv_WriteKalmanQAngleDef;
   oMpuKalman.SetKalmanRMeasure = priv_WriteKalmanRMeasure;
   oMpuKalman.SetKalmanRMeasureDef = priv_WriteKalmanRMeasureDef;

   return errorstatus;
}
