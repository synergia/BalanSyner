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
#define Time1600ms   200u  /*! Only if loop period is 8ms!! */
#define Time1000ms   125u  /*! Only if loop period is 8ms!! */

#define TimerBalToStandDef Time1000ms
#define TimerStandingUpDef Time1600ms

#define AngleStanding   ( 80.0f )
#define AngleMax        ( 90.0f )
#define AngleTiltBack   ( -10.0f )

//-----------------------Private macros--------------------------------//

//-----------------------Private typedefs------------------------------//

//-----------------------Private variables-----------------------------//
/*! Create structure with states and initialize to its default values */
RobotProperties_T kRobotProperties = {
   .BatteryDischarged = true,
   .ConnectionEstablished = false,
   .IsMoving = false,
   .IsPlatformInRange = false,

   .Timer_BalToStand = TimerBalToStandDef,
   .Timer_StandingUp = TimerStandingUpDef,

   .StateRequested = StateRequested_Balancing,
   .StateActive = RobotStates_Balances
};

//-----------------------Private prototypes----------------------------//
static void priv_StateBalancing();
static void priv_StateStandsUp();
static void priv_StateArmsBackDown();
static void priv_StateLiesDown();
static void priv_StateWaitForStanding();

static void priv_EventMotorsBalancing();
static void priv_EventArmsUp();
static void priv_EventArmsMaxDown();
static void priv_EventMotorsStop();
static void priv_CheckActualState();

//-----------------------Private functions-----------------------------//
static void priv_CheckActualState()
{
   /*! Check robot actual state */
   kRobotProperties.IsInStandingRange =
      ( -18.0f < oMpuKalman.AngleFiltered && 18.0f > oMpuKalman.AngleFiltered );

   kRobotProperties.IsLying =
      ( -45.0f > oMpuKalman.AngleFiltered || 45.0f < oMpuKalman.AngleFiltered );

   kRobotProperties.IsPlatformInRange =
      ( -20.0f < oMpuKalman.AngleFiltered && 30.0f > oMpuKalman.AngleFiltered );

   kRobotProperties.IsMoving = !( ( 0.0f == oPID_Omega.GetDstValue( &oPID_Omega.Parameters ) )
                               && ( 0.0f == oPID_Rotation.GetDstValue( &oPID_Rotation.Parameters ) )
                                );

   /*! Show off */
   ( true == kRobotProperties.IsMoving ) ? ( LEDEYE_SetOn ) : ( LEDEYE_SetOff );
}

static void priv_StateBalancing()
{
   priv_EventMotorsBalancing();
   priv_EventArmsUp();
}

static void priv_StateStandsUp()
{
   priv_EventMotorsStop();
   if( 0 < oMpuKalman.AngleFiltered )
   {
      oServos.SetAngleArmLeft ( AngleStanding );
      oServos.SetAngleArmRight( AngleStanding );
   }
   else
   {
      oServos.SetAngleArmLeft ( -AngleStanding );
      oServos.SetAngleArmRight( -AngleStanding );
   }
}

static void priv_StateLiesDown()
{
   priv_EventMotorsStop();
   priv_EventArmsUp();
}

static void priv_StateWaitForStanding()
{
   priv_EventMotorsStop();
   priv_EventArmsUp();
   if( 0 != kRobotProperties.Timer_StandingUp )
   {
      --kRobotProperties.Timer_StandingUp;
   }
}

static void priv_StateArmsBackDown()
{
   priv_EventMotorsBalancing();
   oServos.SetAngleArmLeft ( -AngleStanding );
   oServos.SetAngleArmRight( -AngleStanding );
   if( 0u != kRobotProperties.Timer_BalToStand )
   {
      --kRobotProperties.Timer_BalToStand;
   }
}

static void priv_EventArmsMaxDown()
{
   if( 0.0f < oMpuKalman.AngleFiltered )
   {
      oServos.SetAngleArmLeft ( AngleMax );
      oServos.SetAngleArmRight( AngleMax );
   }
   else
   {
      oServos.SetAngleArmLeft ( -AngleMax );
      oServos.SetAngleArmRight( -AngleMax );
   }
}

static void priv_EventArmsUp()
{
   oServos.SetAngleArmLeft ( 0.0f );
   oServos.SetAngleArmRight( 0.0f );
}

static void priv_EventMotorsStop()
{
   //TODO: Reset PIDs
   oMotors.SetSpeedLeft( 0.0f );
   oMotors.SetSpeedRight( 0.0f );
}

static void priv_EventMotorsBalancing()
{
   /*! Execute standing functionality */
   float PWM;
   /*! Apply PID filter to motors to get required angle (output of omega regulator) */
   oPID_Angle.ApplyPid      ( &oPID_Angle.Parameters,       oMpuKalman.AngleFiltered );
   oPID_AngleMoving.ApplyPid( &oPID_AngleMoving.Parameters, oMpuKalman.AngleFiltered );

   ( false == kRobotProperties.IsMoving ) ? ( PWM = oPID_Angle.Parameters.OutSignal )
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
   if( kRobotProperties.IsPlatformInRange )
   {
      //oServos.SetAngle( SelectServoCamVer, oMpuKalman.AngleFiltered );
   }
   else oServos.SetAngleCamVer( 0.0f );
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
      switch( kRobotProperties.StateActive )
      {
         case RobotStates_ArmsBackDown:
            priv_StateArmsBackDown();
            if( ( 0u == kRobotProperties.Timer_BalToStand ) && ( AngleTiltBack > oMpuKalman.AngleFiltered ) &&
                  ( ( StateRequested_LiesDown == kRobotProperties.StateRequested )
                 || ( StateRequested_StandsUp == kRobotProperties.StateRequested )
                  )
              )
            {
               kRobotProperties.StateActive = RobotStates_StandsUp;
            }
            /*! Tilt back */
            else if( ( 0u == kRobotProperties.Timer_BalToStand ) &&
                     ( ( StateRequested_LiesDown == kRobotProperties.StateRequested )
                    || ( StateRequested_StandsUp == kRobotProperties.StateRequested )
                     )
                   )
            {
               oPID_Omega.Parameters.DstValue = 0.0f;
               oPID_Rotation.Parameters.DstValue = 0.0f;
               oPID_Angle.Parameters.DstValue = AngleTiltBack;
            }
            if( StateRequested_Balancing == kRobotProperties.StateRequested )
            {
               kRobotProperties.StateActive = RobotStates_Balances;
               kRobotProperties.Timer_BalToStand = TimerBalToStandDef;
            }
            break;

         case RobotStates_Balances:
            priv_StateBalancing();
            if( true == kRobotProperties.IsLying )
            {
               kRobotProperties.StateActive = RobotStates_LiesDown;
            }
            else if(  ( StateRequested_LiesDown == kRobotProperties.StateRequested )
                   || ( StateRequested_StandsUp == kRobotProperties.StateRequested )
                   )
            {
               kRobotProperties.StateActive = RobotStates_ArmsBackDown;
            }
            break;

         case RobotStates_LiesDown:
            priv_StateLiesDown();
            if( StateRequested_Balancing == kRobotProperties.StateRequested )
            {
               kRobotProperties.Timer_StandingUp = TimerStandingUpDef;
               kRobotProperties.StateActive = RobotStates_WaitForStanding;
            }
            else if( StateRequested_StandsUp == kRobotProperties.StateRequested )
            {
               kRobotProperties.StateActive = RobotStates_StandsUp;
            }
            break;

         case RobotStates_StandsUp:
            priv_StateStandsUp();
            if( StateRequested_LiesDown == kRobotProperties.StateRequested )
            {
               kRobotProperties.StateActive = RobotStates_LiesDown;
            }
            if( ( StateRequested_Balancing == kRobotProperties.StateRequested )
             && ( true == kRobotProperties.IsInStandingRange )
              )
            {
               kRobotProperties.Timer_BalToStand = TimerBalToStandDef;
               kRobotProperties.StateActive = RobotStates_Balances;
            }
            else if( ( StateRequested_Balancing == kRobotProperties.StateRequested )
                  && ( false == kRobotProperties.IsInStandingRange )
                   )
            {
               priv_EventArmsMaxDown();
            }
            break;

         case RobotStates_WaitForStanding:
            priv_StateWaitForStanding();
            if(  ( ( 0u == kRobotProperties.Timer_StandingUp )
                && ( StateRequested_Balancing == kRobotProperties.StateRequested )
                 )
                || ( StateRequested_StandsUp == kRobotProperties.StateRequested )
              )
            {
               kRobotProperties.StateActive = RobotStates_StandsUp;
               kRobotProperties.Timer_StandingUp = TimerStandingUpDef;
            }
            if( StateRequested_LiesDown == kRobotProperties.StateRequested)
            {
               kRobotProperties.StateActive = RobotStates_LiesDown;
               kRobotProperties.Timer_StandingUp = TimerStandingUpDef;
            }
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
