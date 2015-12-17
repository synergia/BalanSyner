
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "arm_math.h"
#include "PID.h"

//-----------------------Private typedefs------------------------------//
#define Kp_Def    1.0f;
#define Ki_Def    0.0f;
#define Kd_Def    0.0f;

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
static void priv_PID_Apply( PID_Parameters_T *PID, float ReadValue );
static void priv_SetDstValue( PID_Parameters_T *PID, float NewValue );
static float priv_GetDstValue( PID_Parameters_T *PID );
static void priv_SetKp( PID_Parameters_T *pkThis, float NewValue );
static void priv_SetKi( PID_Parameters_T *pkThis, float NewValue );
static void priv_SetKd( PID_Parameters_T *pkThis, float NewValue );
static float priv_GetKp( PID_Parameters_T *pkThis);
static float priv_GetKi( PID_Parameters_T *pkThis);
static float priv_GetKd( PID_Parameters_T *pkThis);

//-----------------------Private functions-----------------------------//
static void priv_PID_Apply( PID_Parameters_T *PID, float ReadValue )
{
   PID->e = PID->DstValue - ReadValue;
   PID->e_sum += PID->e;

   /*!< Check if integral error doesn't exceed boundaries */
   if( PID->e_sum > PID->iWindUp )
      PID->e_sum = PID->iWindUp;
   else if( PID->e_sum < -PID->iWindUp )
      PID->e_sum = -PID->iWindUp;

   /*! Do math only if needed */
   PID->OutSignal = 0;
   if( 0 != PID->Kp )
      PID->OutSignal = PID->Kp * PID->e;

   if( 0 != PID->Ki )
      PID->OutSignal += PID->Ki * PID->e_sum;

   if( 0 != PID->Kd )
   {
      float dOut = ( PID->e - PID->e_last );

      if( dOut > PID->dWindUp )        dOut =  PID->dWindUp;
      else if( dOut < -PID->dWindUp )  dOut = -PID->dWindUp;

      PID->OutSignal += PID->Kd * dOut;
   }

   /*! Windup prevention */
   if( PID->OutSignal > PID->MaxOutSignal )
      PID->OutSignal = PID->MaxOutSignal;
   else if( PID->OutSignal < -PID->MaxOutSignal )
      PID->OutSignal = -PID->MaxOutSignal;

   PID->e_last = PID->e;
}

static void priv_SetDstValue( PID_Parameters_T *PID, float NewValue )
{
   PID->DstValue = NewValue;
}

static float priv_GetDstValue( PID_Parameters_T *PID )
{
   return PID->DstValue;
}

static void priv_SetKp( PID_Parameters_T *pkThis, float NewValue )
{
   pkThis->Kp = NewValue;
}

static void priv_SetKi( PID_Parameters_T *pkThis, float NewValue )
{
   pkThis->Ki = NewValue;
}

static void priv_SetKd( PID_Parameters_T *pkThis, float NewValue )
{
   pkThis->Kd = NewValue;
}

static float priv_GetKp( PID_Parameters_T *pkThis)
{
   return ( pkThis->Kp );
}

static float priv_GetKi( PID_Parameters_T *pkThis)
{
   return ( pkThis->Ki );
}

static float priv_GetKd( PID_Parameters_T *pkThis)
{
   return ( pkThis->Kd );
}

//-----------------------Public functions------------------------------//
void PID_Initialize( PID_Struct_C *PID )
{
   PID->Parameters.Kp = Kp_Def;
   PID->Parameters.Ki = Ki_Def;
   PID->Parameters.Kd = Kd_Def;

   PID->Parameters.e          = 0.0f;
   PID->Parameters.e_sum      = 0.0f;
   PID->Parameters.e_last     = 0.0f;
   PID->Parameters.OutSignal  = 0.0f;
   PID->Parameters.DstValue   = 0.0f;

   PID->ApplyPid = priv_PID_Apply;

   PID->SetDstValue = priv_SetDstValue;
   PID->GetDstValue = priv_GetDstValue;
   PID->GetKp = priv_GetKp;
   PID->GetKi = priv_GetKi;
   PID->GetKd = priv_GetKd;
   PID->SetKp = priv_SetKp;
   PID->SetKi = priv_SetKi;
   PID->SetKd = priv_SetKd;
}

