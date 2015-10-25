#ifndef MPU_H_
#define MPU_H_

//-----------------------Includes-------------------------------------//

//-----------------------Public typedefs------------------------------//
typedef struct
{
	float Angle;
	float Gyro;

	float AngleFiltered;
}MpuKalmanDataStruct;

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//
uint8_t InitializeMPU();
void MPU_Perform();

#endif
