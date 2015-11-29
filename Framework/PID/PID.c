
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
static void priv_ChangeDstValue( PID_Parameters_T *PID, float NewValue );

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

static void priv_ChangeDstValue( PID_Parameters_T *PID, float NewValue )
{
   PID->DstValue = NewValue;
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
   PID->ChangeDstValue = priv_ChangeDstValue;
}
