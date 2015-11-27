/*
 * Motors.c
 *
 *  Created on: Oct 25, 2015
 *      Author: Kuba
 */

//-----------------------Includes-------------------------------------//
#include "Motors.h"
#include "../PinDefines.h"
#include "../StmPeriphInit/RCC.h"
#include "../StmPeriphInit/Timers.h"
#include "../StmPeriphInit/GPIO.h"
#include "../StmPeriphInit/NVIC.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//
/*!
 * For max speed 500RPM and DT=0.032s and encoder resolution 1200 ticks per shaft revolution,
 * maximum possible ticks per iteration is 96 so any number above that value is safe to use
 * (counter won't over/underflow). Resolution is 9.375 deg/sec.
 */
#define CounterDef         150u
#define TicksPerRevolution 1200u
#define AnglePerTick       0.3f

//-----------------------Private macros--------------------------------//
#define ANGLE_TO_PWM_VALUE(ANGLE)   ( 2u*(ANGLE)+540u )

//-----------------------Private variables-----------------------------//
extern float DT;

//-----------------------Private prototypes----------------------------//
static void priv_MotorSetSpeed(MotorSelector_T Motor, uint16_t Value, uint8_t Direction);
static void priv_ServoSetAngle(ServoSelector_T Servo, float Angle);

static void priv_SetAngleArmLeft(uint16_t Angle);
static void priv_SetAngleArmRight(uint16_t Angle);
static void priv_SetAngleCamHor(uint16_t Angle);
static void priv_SetAngleCamVer(uint16_t Angle);

//-----------------------Private functions-----------------------------//
/*!
 * Value may vary between 0 and 1000.
 */
static void priv_MotorSetSpeed(MotorSelector_T MotorSelector, uint16_t Value, uint8_t Direction)
{
   //todo: handle direction
   if(Value<=1000u && Value>=0u)
   {
      switch (MotorSelector)
      {
      case SelectMotorLeft:
         TIM_MOTORS->MOT1_PWM_CHANNEL = Value;
         break;
      case SelectMotorRight:
         TIM_MOTORS->MOT2_PWM_CHANNEL = Value;
         break;
      default:
         break;
      }
   }
}

/*!
 * Value may vary between -90.0 and +90.0. Resolution 0.5.
 */
static void priv_ServoSetAngle(ServoSelector_T ServoSelector, float Angle)
{
   if( -90>Angle ) Angle = -90;
   if(  90<Angle ) Angle =  90;

   Angle = (uint16_t) 2*(Angle)+540;

   switch (ServoSelector)
   {
   case SelectServoArmLeft:
      priv_SetAngleArmLeft(Angle);
      break;
   case SelectServoArmRight:
      priv_SetAngleArmRight(Angle);
      break;
   case SelectServoCamHor:
      priv_SetAngleCamHor(Angle);
      break;
   case SelectServoCamVer:
      priv_SetAngleCamVer(Angle);
      break;
   default:
      break;
   }
}

static void priv_SetAngleArmLeft(uint16_t Angle)
{
   TIM_SERVOS->SERVO_ARM_L_PWM_CHANNEL = Angle;
}

static void priv_SetAngleArmRight(uint16_t Angle)
{
   TIM_SERVOS->SERVO_ARM_P_PWM_CHANNEL = Angle;
}

static void priv_SetAngleCamHor(uint16_t Angle)
{
   TIM_SERVOS->SERVO_HOR_PWM_CHANNEL = Angle;
}

static void priv_SetAngleCamVer(uint16_t Angle)
{
   TIM_SERVOS->SERVO_VER_PWM_CHANNEL = Angle;
}

float priv_GetOmega( EncoderParameters_T *pkThis )
{
   /*! How many ticks since last iteration */
   int16_t DeltaTicks = GetCounter( pkThis->TIMx ) - CounterDef;

   /*! Calculate angular speed of shaft */
   pkThis->Omega = ( DeltaTicks * AnglePerTick ) / pkThis->Dt; /*!< Shaft Omega [degrees/second] */

   /*! Reset counter so it cannot get out of range */
   SetCounter( pkThis->TIMx, CounterDef );

   return pkThis->Omega;
}

//-----------------------Public functions------------------------------//
void InitializeEncoders()
{
   /*! Physical initialization */
   InitializeRCC( DriverSelectEncoders );
   InitializeTimers( TIM_ENC1 );
   InitializeTimers( TIM_ENC2 );
   InitializeGPIO( DriverSelectEncoders );

   /*! Software */
   oEncoderLeft.Parameters.Dt = DT;
   oEncoderLeft.Parameters.TIMx = TIM_ENC1;
   oEncoderLeft.Parameters.Counter = CounterDef;
   oEncoderLeft.Parameters.Omega = 0u;
   oEncoderLeft.GetOmega = priv_GetOmega;
   oEncoderLeft.SetCounter = SetCounter; /*! Timer function */

   oEncoderRight.Parameters.Dt = DT;
   oEncoderRight.Parameters.TIMx = TIM_ENC2;
   oEncoderRight.Parameters.Counter = CounterDef;
   oEncoderRight.Parameters.Omega = 0u;
   oEncoderRight.GetOmega = priv_GetOmega;
   oEncoderRight.SetCounter = SetCounter; /*! Timer function */
}

void InitializeMotors()
{
   /*! Physical initialization */
   InitializeRCC(DriverSelectMotors);
   InitializeTimers(TIM_MOTORS);
   InitializeGPIO(DriverSelectMotors);

   /*! Software */
   oMotor.SetSpeed = priv_MotorSetSpeed;
}

void InitializeServos()
{
   /*! Physical initialization */
   InitializeRCC(DriverSelectServosArm);
   InitializeTimers(TIM_SERVOS);
   InitializeGPIO(DriverSelectServosArm);

   /*! Physical initialization */
   InitializeRCC(DriverSelectServosCam);
   InitializeTimers(TIM_SERVOS);
   InitializeGPIO(DriverSelectServosCam);

   /*! Software */
   oServosArm.SetAngle = priv_ServoSetAngle;
}
