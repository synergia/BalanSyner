
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "_LibMPU6050.h"
#include "MPU.h"
#include "GPIO.h"
#include "I2C.h"
#include "RCC.h"
#include "../Framework/inc/KalmanFilter.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
static float priv_MpuGetFilteredData();

//-----------------------Private functions-----------------------------//
/*!
 *  Saves measured data into MpuMeasuredData struct and prepares data for Kalman filtering in MpuKalmanData struct
 */
static float priv_MpuGetFilteredData()
{
	MPU6050_Get_AccAngleYZ_Data( &oMpuKalman.AngleRaw );
	MPU6050_Get_GyroX_Data( &oMpuKalman.GyroRaw ); //Gyro [deg/second]

	return ( oMpuKalman.AngleFiltered = KalmanGetValue(oMpuKalman.AngleRaw, oMpuKalman.GyroRaw) );
}

//-----------------------Public functions------------------------------//
MPU6050_errorstatus InitializeMPU()
{
	MPU6050_errorstatus errorstatus;
	InitializeRCC(DriverSelectMpu);
	InitializeI2C();
	InitializeGPIO(DriverSelectMpu);
	errorstatus = MPU6050_Initialization();

	oMpuKalman.GetFiltedAngle = priv_MpuGetFilteredData;

	return errorstatus;
}
