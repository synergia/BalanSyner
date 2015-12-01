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

//-----------------------Public macros--------------------------------//

//-----------------------Public typedefs------------------------------//
typedef enum
{
   SelectMotorLeft,
   SelectMotorRight,
}MotorSelector_T;

typedef enum
{
   DirectionCW,
   DirectionCCW
}MotorDirection_T;

typedef enum
{
   SelectEncoderLeft,
   SelectEncoderRight,
}EncoderSelector_T;

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
   float Omega;
   uint16_t Counter;
   TIM_TypeDef * TIMx;     /*!< which timer */
}EncoderParameters_T;

typedef struct
{
   EncoderParameters_T Parameters;

   float ( *Perform )( EncoderParameters_T *pkThis );
   float ( *GetOmega )( EncoderParameters_T *pkThis );
   void ( *SetCounter )( TIM_TypeDef *TIMx, uint32_t NewValue );
}Encoder_C;

typedef struct
{
   //TODO void get speed
   void ( *SetSpeed )( MotorSelector_T Motor, float Value );
}Motors_C;

typedef struct
{
   //TODO void get angle
   void ( *SetAngle )( ServoSelector_T ServoSelector, float Angle );
}Servos_C;

//-----------------------Public variables-----------------------------//
Encoder_C oEncoderLeft;
Encoder_C oEncoderRight;
Motors_C oMotor;
Servos_C oServosArm;
PID_Struct_C oPID_Omega;
PID_Struct_C oPID_Angle;

//-----------------------Public prototypes----------------------------//
void InitializeEncoders();
void InitializeMotors();
void InitializeServos();
void InitializePIDs();

#endif /* MOTORS_H_ */
