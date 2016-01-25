#ifndef MPU_H_
#define MPU_H_

//-----------------------Includes-------------------------------------//

//-----------------------Public typedefs------------------------------//
typedef struct
{
   float AngleRaw;
   float GyroRaw;
   float AngleFiltered;

   void ( *ApplyFilter ) ( void );

   float ( *GetKalmanQAngle )( void );
   float ( *GetKalmanRMeasure )( void );
   void ( *SetKalmanQAngleDef )( void );
   void ( *SetKalmanRMeasureDef )( void );
   void ( *SetKalmanQAngle )( float Value );
   void ( *SetKalmanRMeasure )( float Value );
}MpuKalmanClass_T;

//-----------------------Public defines-------------------------------//

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//
MpuKalmanClass_T oMpuKalman;

//-----------------------Public prototypes----------------------------//
uint8_t InitializeMPU();

#endif
