#ifndef MPU_H_
#define MPU_H_

//-----------------------Includes-------------------------------------//

//-----------------------Public typedefs------------------------------//
typedef struct
{
	float AngleRaw;
	float GyroRaw;

	float AngleFiltered;

	float (*GetFiltedAngle) (void);
}MpuKalmanClass_T;

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//
MpuKalmanClass_T oMpuKalman;

//-----------------------Public prototypes----------------------------//
uint8_t InitializeMPU();

#endif
