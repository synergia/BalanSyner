/*
 * Logic.c
 *
 *  Created on: Nov 22, 2015
 *      Author: Kuba
 */

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "Logic.h"
#include "RobotStates.h"

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
RobotProperties_T kRobotProperties = {
   .BatteryDischarged = true,
   .ConnectionEstablished = false,
   .Moving = false,
   .PlatformInRange = false,

   .StateUserRequested = RobotStateUser_LiesDown
};

//-----------------------Private prototypes----------------------------//
static void priv_EventBalancing();
static void priv_EventStandingUp();
static void priv_EventArmsUp();
static void priv_EventArmsDown();
static void priv_EventMotorsStop();
static void priv_CheckActualState();

//-----------------------Private functions-----------------------------//
static void priv_CheckActualState()
{
   /*! Check robot actual state */
   if( -18.0f < oMpuKalman.AngleFiltered && 18.0f > oMpuKalman.AngleFiltered )
   {
      kRobotProperties.StateActual = RobotStateActual_StandsUp;
   }
   else if( -45.0f > oMpuKalman.AngleFiltered || 45.0f < oMpuKalman.AngleFiltered )
   {
      kRobotProperties.StateActual = RobotStateActual_LiesDown;
   }
   else
   {
      kRobotProperties.StateActual = RobotStateActual_Unspecified;
   }

   kRobotProperties.PlatformInRange = ( -20.0f < oMpuKalman.AngleFiltered && 30.0f > oMpuKalman.AngleFiltered );
   kRobotProperties.Moving = !( ( 0.0f == oPID_Omega.GetDstValue( &oPID_Omega.Parameters ) )
                             && ( 0.0f == oPID_Rotation.GetDstValue( &oPID_Rotation.Parameters ) )
                              );

   /*! Show off */
   ( true == kRobotProperties.Moving ) ? ( LEDEYE_SetOn ) : ( LEDEYE_SetOff );
}

static void priv_EventBalancing()
{
   /*! Execute standing functionality */
   float PWM;
   /*! Apply PID filter to motors to get required angle (output of omega regulator) */
   oPID_Angle.ApplyPid      ( &oPID_Angle.Parameters,       oMpuKalman.AngleFiltered );
   oPID_AngleMoving.ApplyPid( &oPID_AngleMoving.Parameters, oMpuKalman.AngleFiltered );

   ( false == kRobotProperties.Moving ) ? ( PWM = oPID_Angle.Parameters.OutSignal )
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

   oMotors.SetSpeedLeft(  PWM + oPID_Rotation.Parameters.OutSignal );
   oMotors.SetSpeedRight( PWM - oPID_Rotation.Parameters.OutSignal );


   /*! Set servo cam vertical */
   if( kRobotProperties.PlatformInRange )
   {
      //oServos.SetAngle( SelectServoCamVer, oMpuKalman.AngleFiltered );
   }
   else oServos.SetAngleCamVer( 0.0f );
}

static void priv_EventStandingUp()
{
   if( !time3072msPassed )
   {
      if( 0 < oMpuKalman.AngleFiltered )
      {
         oServos.SetAngleArmLeft ( 82.0f );
         oServos.SetAngleArmRight( 82.0f );
      }
      else
      {
         oServos.SetAngleArmLeft ( -82.0f );
         oServos.SetAngleArmRight( -82.0f );
      }
   }
}

static void priv_EventArmsUp()
{
   oServos.SetAngleArmLeft ( 0.0f );
   oServos.SetAngleArmRight( 0.0f );
}

static void priv_EventArmsDown()
{
   oServos.SetAngleArmLeft ( -80.0f );
   oServos.SetAngleArmRight( -80.0f );
}

static void priv_EventMotorsStop()
{
   //TODO: Reset PIDs
   oMotors.SetSpeedLeft( 0.0f );
   oMotors.SetSpeedRight( 0.0f );
}

//-----------------------Public functions------------------------------//
void MainTask8ms()
{
   /*! Measure angle of the robot */
   oMpuKalman.ApplyFilter();

   /*! Perform action only if battery in not discharged */
   if( false == kRobotProperties.BatteryDischarged )
   {
#if 1
      priv_CheckActualState();

      /*! This switch checks which state is requested by user */
      switch( kRobotProperties.StateUserRequested )
      {
         case RobotStateUser_Balancing:
            switch( kRobotProperties.StateActual )
            {
               case RobotStateActual_LiesDown:
                  kRobotProperties.StateRequested = RobotStateRequested_StandingUp;
                  break;

               case RobotStateActual_StandsUp:
                  kRobotProperties.StateRequested = RobotStateRequested_Balancing;

               default:
                  /*! When robot falls down, StateActual = LaysDown and StateRequested = StandingUp.
                   * When angle is close to 0, StateActual = StandsUp and StateRequested = Balancing
                   * Then robot will balance until StateActual = LiesDown. When angle is greater than
                   * Standing and less than laying, default case is triggered and nothing changes */
                  break;
            }
            break;
            case RobotStateUser_LiesDown:
               kRobotProperties.StateRequested = RobotStateRequested_LyingDown;
               break;
            case RobotStateUser_StandsUp:
               switch( kRobotProperties.StateActual )
               {
                  case RobotStateActual_LiesDown:
                     kRobotProperties.StateRequested = RobotStateRequested_StandingUp;
                     break;

                  case RobotStateActual_StandsUp:
                  default:
                     break;
               }
               break;
            default:
               break;
      }

      /*! This switch executes internal requests from the application */
      switch( kRobotProperties.StateRequested )
      {
         case RobotStateRequested_TiltBack:
            priv_EventArmsDown();
            oPID_Angle.SetDstValue( &oPID_Angle.Parameters, -15.0f );
            oPID_Omega.SetDstValue( &oPID_Omega.Parameters, 0.0f );
            break;
         case RobotStateRequested_LyingDown:
            priv_EventMotorsStop();
            priv_EventArmsUp();
            break;
         case RobotStateRequested_StandingUp:
            priv_EventMotorsStop();
            priv_EventStandingUp();
            break;
         case RobotStateRequested_Balancing:
            priv_EventBalancing();
            priv_EventArmsUp();
            break;
         default:
            break;
      }
#endif

   }
}

void MainTask16ms()
{
#if 1
   static uint8_t Selector = 0;
   switch ( Selector++ )
   {
      case 0:
         pub_SendCommandBT( oMpuKalman.AngleFiltered, ReadFilteredAngle );
         break;
      case 1:
         pub_SendCommandBT( oPID_Angle.Parameters.OutSignal, 4 );
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
   oEncoders.Perform();
   float OmegaMean = ( oEncoders.GetOmegaLeft() + oEncoders.GetOmegaRight() ) / 2;
   float OmegaDiff = ( oEncoders.GetOmegaLeft() - oEncoders.GetOmegaRight() );

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
   kRobotProperties.BatteryDischarged = oBattery.IsDischarged();

   /*! Check if any command from USART or buttons came and save buffer to the struct. ADCx2. */
   kRobotProperties.ConnectionEstablished = Communicator_CheckInputs();

   if( kRobotProperties.ConnectionEstablished )
   {
      LED4_Toggle;
   }
   else
   {
      oPID_Omega.SetDstValue   ( &oPID_Omega.Parameters,    0.0f );
      oPID_Rotation.SetDstValue( &oPID_Rotation.Parameters, 0.0f );
   }

   //oPID_Omega.SetDstValue( &oPID_Omega.Parameters, oSharp.Omega );
}
