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
/*! Create structure with states and initialize to its default values */
RobotStates_T kRobotStates = {
   .BatteryDischarged = true,
   .RobotStanding = false,
   .ConnectionEstablished = false,
   .Moving = false,
   .PlatformInRange = false
};

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void MainTask8ms()
{
   /*! Perform action only if battery in not discharged */
   if( false == kRobotStates.BatteryDischarged )
   {
      float PWM;

      /*! Measure angle of the robot */
      oMpuKalman.ApplyFilter();

      /*! Check robot state */
      kRobotStates.RobotStanding   = ( -45.0f < oMpuKalman.AngleFiltered && 45.0f > oMpuKalman.AngleFiltered );
      kRobotStates.PlatformInRange = ( -20.0f < oMpuKalman.AngleFiltered && 30.0f > oMpuKalman.AngleFiltered );
      kRobotStates.Moving = !( ( 0.0f == oPID_Omega.GetDstValue( &oPID_Omega.Parameters ) )
                            && ( 0.0f == oPID_Rotation.GetDstValue( &oPID_Rotation.Parameters ) )
                             );

      ( true == kRobotStates.Moving ) ? ( LEDEYE_SetOn ) : ( LEDEYE_SetOff );

      /*! Execute standing functionality */
      if( kRobotStates.RobotStanding )
      {
         /*! Apply PID filter to motors to get required angle (output of omega regulator) */
         oPID_Angle.ApplyPid      ( &oPID_Angle.Parameters,       oMpuKalman.AngleFiltered );
         oPID_AngleMoving.ApplyPid( &oPID_AngleMoving.Parameters, oMpuKalman.AngleFiltered );

         ( false == kRobotStates.Moving ) ? ( PWM = oPID_Angle.Parameters.OutSignal )
                                          : ( PWM = oPID_AngleMoving.Parameters.OutSignal );

         oBattery.AdjustPwm( &PWM );

         if     ( 0 < PWM && PWM <  100 ) PWM =  ( PWM / 10 ) * ( PWM / 10 );
         else if( 0 > PWM && PWM > -100 ) PWM = -( PWM / 10 ) * ( PWM / 10 );

         /*!if( oPID_Angle.Parameters.e < 2.0 && oPID_Angle.Parameters.e > -2.0 )
         {
            if(PWM >  110) PWM =  110;
            if(PWM < -110) PWM = -110;
         }
         if( 0.0f < oMpuKalman.AngleFiltered )
         {
            PWM -= ( oMpuKalman.AngleFiltered ) * ( oMpuKalman.AngleFiltered ) * 3;// - MinPwmToReact;
         }
         else
         {
            PWM += ( oMpuKalman.AngleFiltered ) * ( oMpuKalman.AngleFiltered ) * 3;// + MinPwmToReact;
         }*/

         /*! Check if PWM is within boundaries */
         ( 1000.0f < PWM ) ? ( PWM = 1000.0f ) : ( ( -1000.0f > PWM ) ? ( PWM = -1000.0f ) : ( PWM ) );

         oMotors.SetSpeedLeft( PWM + oPID_Rotation.Parameters.OutSignal );
         oMotors.SetSpeedRight( PWM - oPID_Rotation.Parameters.OutSignal );
      }

      /*! Stop motors if robot falls */
      else
      {
         oMotors.SetSpeedLeft( 0.0f );
         oMotors.SetSpeedRight( 0.0f );
      }

      /*! Set servo cam vertical */
      if( kRobotStates.PlatformInRange )
      {
         //oServos.SetAngle( SelectServoCamVer, oMpuKalman.AngleFiltered );
      }
      else oServos.SetAngle( SelectServoCamVer, 0.0f );

   }
}

void MainTask16ms()
{
#if 0
   static uint8_t Selector = 0;
   switch ( Selector++ )
   {
      case 0:
         pub_SendCommandBT( oBattery.ChargedPercent, 2 );
         break;
      case 1:
         pub_SendCommandBT( oPID_Rotation.Parameters.e_sum, 4 );
         break;
      case 3:
         pub_SendCommandBT( oPID_Omega.Parameters.OutSignal, 12);
         break;
      default:
         break;
   }
   if( Selector > 1 ) Selector = 0;
#endif

#if 0
   static uint8_t Selector = 0;
   switch ( Selector++ )
   {
      case 0:
   pub_SendCommandBT( oMpuKalman.AngleFiltered, ReadFilteredAngle);
         break;
      case 1:
   pub_SendCommandBT( oPID_Angle.Parameters.Kp, ReadPidAngleKp);
         break;
      case 2:
   pub_SendCommandBT( oPID_Omega.Parameters.e_sum, 15);
         break;
      case 3:
   pub_SendCommandBT( oPID_Angle.Parameters.Kd, ReadPidAngleKd);
         break;
      case 4:
   pub_SendCommandBT( oEncoder_Right.Parameters.Omega, ReadOmegaRight);
         break;
      case 5:
   pub_SendCommandBT( oPID_Omega.Parameters.Kp, ReadPidOmegaKp);
         break;
      case 6:
   pub_SendCommandBT( oPID_Omega.Parameters.Ki, ReadPidOmegaKi);
         break;
      case 7:
   pub_SendCommandBT( oPID_Omega.Parameters.Kd, ReadPidOmegaKd);
         break;
      case 8:
   pub_SendCommandBT( oPID_Omega.Parameters.OutSignal+AngleOffset, 12);
         break;
      case 84:
   pub_SendCommandBT( oPID_Omega.Parameters.OutSignal, 13);
         break;
      case 83:
   pub_SendCommandBT( oPID_Angle.Parameters.OutSignal, 14);
         break;
      case 9:
   pub_SendCommandBT( oPID_Angle.Parameters.Ki, ReadPidAngleKi);
         break;
      case 10:
   pub_SendCommandBT( oPID_Angle.Parameters.e_sum, 20);
         break;
      default:
         break;
   }
   if( Selector > 10 ) Selector = 0;
#endif
}

void MainTask32ms()
{
   LED1_Toggle;

#if 1
   /*! Calculate mean omega of the robot */
   float OmegaMean = ( oEncoder_Left.Perform ( &oEncoder_Left.Parameters )
                     + oEncoder_Right.Perform( &oEncoder_Right.Parameters )
                     ) / 2;

   float OmegaDiff = ( oEncoder_Left.GetOmega ( &oEncoder_Left.Parameters )
                     - oEncoder_Right.GetOmega( &oEncoder_Right.Parameters )
                     );

   /*! Apply PID filter to motors to get required omega */
   oPID_Omega.ApplyPid   ( &oPID_Omega.Parameters,    OmegaMean );
   oPID_Rotation.ApplyPid( &oPID_Rotation.Parameters, OmegaDiff );
   oPID_Angle.SetDstValue      ( &oPID_Angle.Parameters,       oPID_Omega.Parameters.OutSignal + AngleOffset );
   oPID_AngleMoving.SetDstValue( &oPID_AngleMoving.Parameters, oPID_Omega.Parameters.OutSignal + AngleOffset );
#endif
}

void MainTask128ms()
{
   LED2_Toggle;
   oBattery.Perform();
   oSharp.Perform();

   /*! Check if battery is discharged */
   kRobotStates.BatteryDischarged = oBattery.IsDischarged();

   /*! Check if any command from USART or buttons came and save buffer to the struct. ADCx2. */
   kRobotStates.ConnectionEstablished = Communicator_CheckInputs();

   if( kRobotStates.ConnectionEstablished )
   {
      LED4_Toggle;
   }
   else
   {
      //oPID_Omega.SetDstValue   ( &oPID_Omega.Parameters,    0.0f );
      //oPID_Rotation.SetDstValue( &oPID_Rotation.Parameters, 0.0f );
   }

   //oPID_Omega.SetDstValue( &oPID_Omega.Parameters, oSharp.Omega );
}
