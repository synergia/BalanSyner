
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "arm_math.h"
#include "PID.h"

//-----------------------Private typedefs------------------------------//
#define Kp_Def    1;
#define Ki_Def    0;
#define Kd_Def    0;

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
   PID->OutSignal = PID->Kp * PID->e
                  + PID->Ki * PID->e_sum
                  + PID->Kd * ( PID->e - PID->e_last );
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

   PID->Parameters.e          = 0;
   PID->Parameters.e_sum      = 0;
   PID->Parameters.e_last     = 0;
   PID->Parameters.OutSignal  = 0;
   PID->Parameters.DstValue   = 0;

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
