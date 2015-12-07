
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "PID_Usr.h"

//-----------------------Private defines-------------------------------//
#define AngleLinearBorder  5.0f

//-----------------------Private macros--------------------------------//

//-----------------------Private typedefs------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
float PID_AngleAdjust( float Angle )
{
   if( AngleLinearBorder < Angle )
   {
      return( AngleLinearBorder + (   ( Angle - AngleLinearBorder )
                                    * ( Angle - AngleLinearBorder )
                                  ) / 1.5
            );
   }
   else if( -AngleLinearBorder > Angle )
   {
      return( -AngleLinearBorder - (   ( Angle + AngleLinearBorder )
                                     * ( Angle + AngleLinearBorder )
                                   ) / 1.5
            );
   }
   return Angle;
}

