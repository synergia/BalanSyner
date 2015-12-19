/*
 * Logic.c
 *
 *  Created on: Nov 22, 2015
 *      Author: Kuba
 */

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "Logic.h"

#include "../Drivers/Battery/Battery.h"
#include "../Drivers/BT/BT.h"
#include "../Drivers/Clock/clock.h"
#include "../Drivers/LEDs/LED.h"
#include "../Drivers/Motors/Motors.h"
#include "../Drivers/MPU/MPU.h"
#include "../Drivers/ProximitySensor/Sharp.h"
#include "../Drivers/Wifi/Wifi.h"

#include "Communicator.h"
#include "../Framework/PID/PID_Usr.h"

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private typedefs------------------------------//

//-----------------------Private variables-----------------------------//
RobotStates_T kRobotStates = {
   .BatteryDischarged = true,
   .RobotStanding = false,
   .ConnectionEstablished = false
};

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

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

void MainTask8ms()
{
   float PWM;
   /*! Measure angle of the robot */
   oMpuKalman.ApplyFilter();

   /*! Stop motors when robot falls */
   if( oMpuKalman.AngleFiltered < 45.0f && oMpuKalman.AngleFiltered > -45.0f )
   {
      /*! Apply PID filter to motors to get required angle (output of omega regulator) */
      oPID_Angle.ApplyPid( &oPID_Angle.Parameters, oMpuKalman.AngleFiltered );

      PWM = oPID_Angle.Parameters.OutSignal;
      oBattery.AdjustPwm( &PWM );

      if     ( 0 < PWM && PWM <  100 ) PWM =  ( PWM / 10 ) * ( PWM / 10 );
      else if( 0 > PWM && PWM > -100 ) PWM = -( PWM / 10 ) * ( PWM / 10 );
      /*if( oPID_Angle.Parameters.e < 2.0 && oPID_Angle.Parameters.e > -2.0 )
      {
         if(PWM >  110) PWM =  110;
         if(PWM < -110) PWM = -110;
      }*/
      /*if( 0 < oMpuKalman.AngleFiltered )
      {
         PWM -= ( oMpuKalman.AngleFiltered ) * ( oMpuKalman.AngleFiltered ) * 3;// - MinPwmToReact;
      }
      else
      {
         PWM += ( oMpuKalman.AngleFiltered ) * ( oMpuKalman.AngleFiltered ) * 3;// + MinPwmToReact;
      }*/


      if( 1000 < PWM )
      {
         PWM = 1000;
      }
      else if ( -1000 > PWM )
      {
         PWM = -1000;
      }

      oMotor.SetSpeed( SelectMotorLeft, PWM + oPID_Rotation.Parameters.OutSignal );
      oMotor.SetSpeed( SelectMotorRight, PWM - oPID_Rotation.Parameters.OutSignal );
   }
   else
   {
      oMotor.SetSpeed( SelectMotorLeft, 0.0f );
      oMotor.SetSpeed( SelectMotorRight, 0.0f );
   }

   /*!
    * Set servo cam vertical
    */
   if( -20.0f < oMpuKalman.AngleFiltered && 30.0f > oMpuKalman.AngleFiltered)
   {
      oServos.SetAngle( SelectServoCamVer, oMpuKalman.AngleFiltered );
   }
   else
      oServos.SetAngle( SelectServoCamVer, 0.0f );
}

void MainTask16ms()
{
#if 0
   static uint8_t Selector = 0;
   switch ( Selector++ )
   {
      case 0:
         priv_SendC( oPID_Rotation.Parameters.OutSignal, 2 );
         break;
      case 1:
         priv_SendC( oPID_Rotation.Parameters.e_sum, 4 );
         break;
      case 3:
         priv_SendC( oPID_Omega.Parameters.OutSignal, 12);
         break;
      default:
         break;
   }
   if( Selector > 1 ) Selector = 0;
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
   priv_SendC( oPID_Omega.Parameters.e_sum, 15);
         break;
      case 3:
   priv_SendC( oPID_Angle.Parameters.Kd, 8);
         break;
      case 4:
   priv_SendC( oEncoder_Right.Parameters.Omega, 4);
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
   priv_SendC( oPID_Omega.Parameters.OutSignal+AngleOffset, 12);
         break;
      case 84:
   priv_SendC( oPID_Omega.Parameters.OutSignal, 13);
         break;
      case 83:
   priv_SendC( oPID_Angle.Parameters.OutSignal, 14);
         break;
      case 9:
   priv_SendC( oPID_Angle.Parameters.Ki, 7);
         break;
      case 10:
   priv_SendC( oPID_Angle.Parameters.e_sum, 20);
         break;
      default:
         break;
   }
   if( Selector > 10 ) Selector  = 0;
#endif
}

void MainTask32ms()
{
   LED1_Toggle;

#if 1
   /*! Calculate mean omega of the robot */
   float OmegaMean = ( oEncoder_Left.Perform( &oEncoder_Left.Parameters )
                     + oEncoder_Right.Perform( &oEncoder_Right.Parameters )
                     ) / 2;

   float OmegaDiff = ( oEncoder_Left.GetOmega( &oEncoder_Left.Parameters )
                     - oEncoder_Right.GetOmega( &oEncoder_Right.Parameters )
                     );

   /*! Apply PID filter to motors to get required omega */
   oPID_Omega.ApplyPid( &oPID_Omega.Parameters, OmegaMean );
   oPID_Rotation.ApplyPid( &oPID_Rotation.Parameters, OmegaDiff );
   oPID_Angle.SetDstValue( &oPID_Angle.Parameters, oPID_Omega.Parameters.OutSignal + AngleOffset) ;
#endif
}

void MainTask128ms()
{
   LED2_Toggle;
   LEDEYE_Toggle;
   /*! Check if any command from USART or buttons came and save buffer to struct. ADCx2. */
   Communicator_CheckInputs();
   oBattery.Perform();
   oSharp.Perform();
   //oPID_Omega.SetDstValue( &oPID_Omega.Parameters, oSharp.Omega );
}
