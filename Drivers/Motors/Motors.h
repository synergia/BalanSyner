/*
 * Motors.h
 *
 *  Created on: Oct 25, 2015
 *      Author: Kuba
 */

#ifndef MOTORS_H_
#define MOTORS_H_

//-----------------------Includes-------------------------------------//
#include "../PinDefines.h"
#include "../Framework/PID/PID.h"

//-----------------------Public defines-------------------------------//
#define SpeedMeanLength    5u
#define RotationMeanLength 5u

#if ( 2 > SpeedMeanLength )
   #error "SpeedMeanLength must be greater than 2"
#endif

#if ( 2 > RotationMeanLength )
   #error "RotationMeanLength must be greater than 2"
#endif
//-----------------------Public macros--------------------------------//

//-----------------------Public typedefs------------------------------//
typedef enum
{
   DirectionCW,
   DirectionCCW
}MotorDirection_T;

typedef enum
{
   SelectServoArmLeft,
   SelectServoArmRight,
   SelectServoCamHor,
   SelectServoCamVer,
}ServoSelector_T;

typedef struct
{
   float Dt;
   float OmegaLeft;
   float OmegaRight;
   float DistanceLeft;
   float DistanceRight;
   TIM_TypeDef * TIMxLeft;     /*!< which timer */
   TIM_TypeDef * TIMxRight;    /*!< which timer */

   void ( *Perform )( void );
   float ( *GetDistanceLeft )( void );
   float ( *GetDistanceRight )( void );
   float ( *GetOmegaLeft )( void );
   float ( *GetOmegaRight )( void );
   void ( *SetCounter )( TIM_TypeDef *TIMx, uint32_t NewValue );
}Encoders_C;

typedef struct
{
   /*! This table is used to calculate mean values */
   float TableMean_SpeedDst[SpeedMeanLength];
   float TableMean_RotationDst[RotationMeanLength];

   /*! Calculate mean value and returns it */
   float ( *GetNewRotationDst )( float Value );
   float ( *GetNewSpeedDst )( float Value );

   /*! Sets PWM */
   void ( *SetSpeedLeft )( float Value );
   void ( *SetSpeedRight )( float Value );
}Motors_C;

typedef struct
{
   /*! Sets servo do desired angle */
   void ( *SetAngleArmLeft )( float Angle );
   void ( *SetAngleArmRight )( float Angle );
   void ( *SetAngleCamHor )( float Angle );
   void ( *SetAngleCamVer )( float Angle );
}Servos_C;

//-----------------------Public variables-----------------------------//
extern Encoders_C oEncoders;
extern Motors_C oMotors;
extern Servos_C oServos;

PID_Struct_C oPID_Omega;
PID_Struct_C oPID_Rotation;
PID_Struct_C oPID_Angle;         /*! Gains used when robot is not moving */
PID_Struct_C oPID_AngleMoving;   /*! Gains used when robot is moving */

//-----------------------Public prototypes----------------------------//
void InitializeEncoders();
void InitializeMotors();
void InitializeServos();
void InitializePIDs();

#endif /* MOTORS_H_ */
