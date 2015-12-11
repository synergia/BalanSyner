/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO(R)
**
**  Distribution: The file is distributed “as is,” without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. This file may only be built (assembled or compiled and linked)
**  using the Atollic TrueSTUDIO(R) product. The use of this file together
**  with other tools than Atollic TrueSTUDIO(R) is not permitted.
**
*****************************************************************************
*/

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "main.h"

#include "../StmPeriphInit/SysTick.h"

#include "../Drivers/Clock/clock.h"
#include "../Drivers/LEDs/LED.h"
#include "../Drivers/BT/BT.h"
#include "../Drivers/Wifi/Wifi.h"
#include "../Drivers/MPU/MPU.h"
#include "../Drivers/Motors/Motors.h"

#include "Logic.h"
#include "../Framework/PID/PID_Usr.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
int main(void);

//-----------------------Private functions-----------------------------//
int main(void)
{
   uint16_t i;
   for( i = 0; i < 64000; i++) asm("nop");

   InitializeClock();
   InitializeSysTick();

#ifdef _USE_DISPLAY
   InitializeDisplay();
#endif

#ifdef _USE_MOTORS
   InitializeMotors();
#endif

#ifdef _USE_ENCODERS
   InitializeEncoders();
#endif

#ifdef _USE_SERVOS
   InitializeServos();
#endif

#ifdef _USE_LED_NUCLEO
   InitializeLedNucleo();
#endif

#ifdef _USE_LED_14
   InitializeLed14();
#endif

#ifdef _USE_LED_EYE
   InitializeLedEye();
#endif

#ifdef _USE_BT
   InitializeBT();
#endif

#ifdef _USE_WIFI
   InitializeWifi();
#endif

#ifdef _USE_MPU
   InitializeMPU();
#endif

#if 0
   if(//MPU error))
   {
      //sth bad had happened...
   }
#endif


   oMotor.SetSpeed( SelectMotorLeft, 0.0f );
   oServosArm.SetAngle( SelectServoArmLeft, 0.0f );
   oServosArm.SetAngle( SelectServoArmRight, 30.0f );
   while (1)
   {

   }
   return 0;
}

//-----------------------Public functions------------------------------//
void priv_SendC( float Value, uint8_t Address )
{
   uint8_t Command[] = { 0xFF, 0xFF, Address, 0, 0, 0, 0, 1 };

   uint32_t transport_bits = *( ( uint32_t* ) &Value );
   *(uint32_t *) &Command[3] = transport_bits;

   uint8_t i = 0;
   while ( 8 > i )
   {
      oBluetooth.PushFifo( &oBluetooth.oBtTxFifo, *( Command + i++ ) );
   }
   oBluetooth.SendFifo();
}
volatile float PWM;
void MainTask8ms()
{
   /*! Measure angle of the robot */
   oMpuKalman.ApplyFilter();

   /*! Stop motors when robot falls */
   if( oMpuKalman.AngleFiltered < 50.0f && oMpuKalman.AngleFiltered > -50.0f )
   {
      /*! Apply PID filter to motors to get required angle (output of omega regulator) */
      oPID_Angle.ApplyPid( &oPID_Angle.Parameters, oMpuKalman.AngleFiltered );

      PWM = oPID_Angle.Parameters.OutSignal;
      if     ( 0 < PWM && PWM <  64 ) PWM =  (PWM/10)*(PWM/10);
      else if( 0 > PWM && PWM > -64 ) PWM = -(PWM/10)*(PWM/10);
      if( 0 < oMpuKalman.AngleFiltered )
      {
         PWM -= ( oMpuKalman.AngleFiltered ) * ( oMpuKalman.AngleFiltered ) * 0.5;// - MinPwmToReact;
      }
      else
      {
         PWM += ( oMpuKalman.AngleFiltered ) * ( oMpuKalman.AngleFiltered ) * 0.5;// + MinPwmToReact;
      }

      if( 1000 < PWM )
      {
         PWM = 1000;
      }
      else if ( -1000 > PWM )
      {
         PWM = -1000;
      }


      oMotor.SetSpeed( SelectMotorLeft, PWM );
      oMotor.SetSpeed( SelectMotorRight, PWM );
   }
   else
   {
      oMotor.SetSpeed( SelectMotorLeft, 0.0f );
      oMotor.SetSpeed( SelectMotorRight, 0.0f );
   }
}

void MainTask16ms()
{

#if 0
   static uint8_t Selector = 0;
   switch ( Selector++ )
   {
      case 0:
   priv_SendC( oPID_Omega.Parameters.e_sum, 2);
         break;
      case 1:
   priv_SendC( oPID_Omega.Parameters.e, 3);
         break;
      case 2:
         priv_SendC( oPID_Omega.Parameters.OutSignal + AngleOffset, 12);
         break;
      default:
         break;
   }
   if( Selector > 2 ) Selector  = 0;
#endif

#if 1
   static uint8_t Selector = 0;
   switch ( Selector++ )
   {
      case 0:
   priv_SendC( oMpuKalman.AngleFiltered, 2);
         break;
      case 1:
   priv_SendC( oPID_Angle.Parameters.Kp, 6);
         break;
      case 2:
   priv_SendC( oPID_Angle.Parameters.Ki, 7);
         break;
      case 3:
   priv_SendC( oPID_Angle.Parameters.Kd, 8);
         break;
      case 4:
   priv_SendC( oEncoderLeft.Parameters.Omega, 4);
         break;
      case 5:
   priv_SendC( oPID_Omega.Parameters.Kp, 9);
         break;
      case 6:
   priv_SendC( oPID_Omega.Parameters.Ki, 18);
         break;
      case 7:
   priv_SendC( oPID_Omega.Parameters.Kd, 11);
         break;
      case 8:
   priv_SendC( oPID_Omega.Parameters.OutSignal + AngleOffset, 12);
         break;
      case 9:
   priv_SendC( oPID_Omega.Parameters.OutSignal, 13);
         break;
      case 10:
   priv_SendC( oPID_Angle.Parameters.OutSignal, 14);
         break;
      case 11:
   priv_SendC( oPID_Omega.Parameters.e_sum, 15);
         break;
      case 12:
   priv_SendC( PWM, 16);
         break;
      case 13:
   priv_SendC( oEncoderLeft.Parameters.Distance, 17);
         break;
      default:
         break;
   }
   if( Selector > 13 ) Selector  = 0;
#endif
}

void MainTask32ms()
{
   LED1_Toggle;

#if 1
   /*! Calculate mean omega of the robot */
   float OmegaMean = ( oEncoderLeft.Perform( &oEncoderLeft.Parameters )
                     + oEncoderRight.Perform( &oEncoderRight.Parameters )
                     ) / 2;

   /*! Apply PID filter to motors to get required omega */
   oPID_Omega.ApplyPid( &oPID_Omega.Parameters, OmegaMean );
   oPID_Angle.SetDstValue( &oPID_Angle.Parameters, oPID_Omega.Parameters.OutSignal + AngleOffset );
#endif

#if 0
   static float f=0.0f;
   static uint8_t up = 1;
   if(up)
   {
      f += 1;
      if(f>=180) up=0;
   }
   else{
      f -= 1;
      if(f<=-180) up=1;
   }
   oServosArm.SetAngle(SelectServoArmLeft, f);
#endif
}

void MainTask128ms()
{
   LED2_Toggle;
   /*! Check if any command from USART or buttons came and save buffer to struct. ADCx2. */
   Logic_CheckInputs();
}
