
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "MPU.h"
#include "GPIO.h"
#include "I2C.h"
#include "RCC.h"
#include "_LibMPU6050.h"
#include "../Framework/inc/KalmanFilter.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//
/*!
 * here are stored measured gyro and accelerometer data and also computed angle.
 */
MpuKalmanDataStruct MpuKalmanData;

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
MPU6050_errorstatus InitializeMPU()
{
	MPU6050_errorstatus errorstatus;
	InitializeRCC(SelectMpu);
	InitializeI2C();
	InitializeGPIO(SelectMpu);
	errorstatus = MPU6050_Initialization();
	return errorstatus;
}

/*!
 *  Saves measured data into MpuMeasuredData strunt and prepares data for Kalman filtering in MpuKalmanData struct
 */
void MPU_Perform()
{
	MPU6050_Get_AccAngleYZ_Data( &MpuKalmanData.Angle );
	MPU6050_Get_GyroX_Data( &MpuKalmanData.Gyro ); //Gyro [deg/second]

	MpuKalmanData.AngleFiltered = KalmanGetValue(MpuKalmanData.Angle, MpuKalmanData.Gyro);
}
