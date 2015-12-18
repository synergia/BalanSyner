
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Framework/stm32f30x/inc/stm32f30x_gpio.h"
#include "GPIO.h"
#include "RCC.h"
#include "ADC.h"
#include "Sharp.h"

//-----------------------Private defines-------------------------------//
#define MeanLength            10u

#define MinSharpVoltage       ( 0.4f )
#define MaxSharpVoltage       ( 3.1f )
#define AdcVoltage            ( 3.21f )
#define MaxAdcValue           ( 4095.0f )
#define MinSharpReadValue     ( MaxAdcValue * MinSharpVoltage / AdcVoltage )
#define MaxSharpReadValue     ( MaxAdcValue * MaxSharpVoltage / AdcVoltage )
#define MinSharpDistance      ( 7.0f )    /*! [cm] */
#define MaxSharpDistance      ( 20.0f )   /*! [cm] */
#define MeanDefDistanceValue  ( (MinSharpDistance + MaxSharpDistance ) / 2 ) /*! [cm] */
#define a   ( 24602.8f )
#define b   ( 264.252f )
//-----------------------Private macros--------------------------------//
#define GetDistance( ReadValue ) ( ((ReadValue > MinSharpReadValue) && (ReadValue < MaxSharpReadValue)) ? \
                                    ( a / ( ReadValue - b) ) : ( 0 ) )

//-----------------------Private typedefs------------------------------//

//-----------------------Private variables-----------------------------//
static float SharpDistanceBuffer[MeanLength];

//-----------------------Private prototypes----------------------------//
static void pub_Perform();

static float priv_GetNewMean( float NewValue );

//-----------------------Private functions-----------------------------//
static void pub_Perform()
{
   ADC_RegularChannelConfig(ADC4, ADC_SHARP_CHANNEL, 1, ADC_SampleTime_61Cycles5);
   ADC_StartConversion(ADC4);

   while (!ADC_GetFlagStatus(ADC4, ADC_FLAG_EOC));
   oSharp.Distance = priv_GetNewMean( (float)GetDistance( ADC_GetConversionValue( ADC_SHARP ) ) );
   if( 0 < oSharp.Distance && 10 > oSharp.Distance )        oSharp.Omega = -50;
   else if( 15 < oSharp.Distance && 30 > oSharp.Distance )  oSharp.Omega =  50;
   else oSharp.Omega = 0;
}

static float priv_GetNewMean( float NewValue )
{
   uint8_t Counter;
   /*! Shifting buffer one position right (>>) */
   for( Counter = MeanLength - 2; Counter != 0; Counter-- )
   {
      SharpDistanceBuffer[Counter + 1] =  SharpDistanceBuffer[Counter];
   }
   SharpDistanceBuffer[1] = SharpDistanceBuffer[0];
   SharpDistanceBuffer[0] = NewValue;

   /*! Add last measurements */
   float Sum = 0;
   for( Counter = MeanLength - 1; Counter != 0; Counter-- )
   {
      Sum += SharpDistanceBuffer[Counter];
   }
   Sum += SharpDistanceBuffer[0];

   /*! return mean */
   return ( Sum / MeanLength );
}

static void priv_MeanBufferInitialize()
{
   uint8_t Counter;
   for( Counter = 0; Counter <= MeanLength; Counter++ )
   {
      SharpDistanceBuffer[Counter] =  MeanDefDistanceValue;
   }
}

//-----------------------Public functions------------------------------//
void InitializeSharp()
{
   //-------------HARDWARE-------------//
   InitializeRCC( DriverSelectSharp );
   InitializeGPIO( DriverSelectSharp );
   InitializeADC( DriverSelectSharp );

   //-------------SOFTWARE-------------//
   priv_MeanBufferInitialize();
   oSharp.Perform = pub_Perform;
}

