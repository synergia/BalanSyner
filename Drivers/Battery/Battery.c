
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Framework/stm32f30x/inc/stm32f30x_gpio.h"
#include "GPIO.h"
#include "RCC.h"
#include "ADC.h"
#include "Battery.h"

//-----------------------Private defines-------------------------------//
#define MeanLength            100u
#define MeanDefVoltageValue   11.1f

#define VoltageDiverter    ( 2.8f / 12.8f )
#define MaxBatteryVoltage  ( 12.6f )
#define MinBatteryVoltage  ( 10.0f )
#define AdcVoltage         ( 3.21f )
#define MaxAdcValue        ( 4095.0f )
#define MaxAdcVoltage      ( VoltageDiverter * MaxBatteryVoltage )
#define MinAdcVoltage      ( VoltageDiverter * MinBatteryVoltage )
#define MaxAdcReadValue    ( MaxAdcValue * MaxAdcVoltage / AdcVoltage )
#define MinAdcReadValue    ( MaxAdcValue * MinAdcVoltage / AdcVoltage )
#define ReadAdcRange       ( MaxAdcReadValue - MinAdcReadValue )

//-----------------------Private macros--------------------------------//
#define GetPercent( ReadValue )  ( (ReadValue - MinAdcReadValue) / ReadAdcRange * 100 )
#define GetVoltage( ReadValue )  ( ReadValue / MaxAdcValue * AdcVoltage / VoltageDiverter )

//-----------------------Private typedefs------------------------------//

//-----------------------Private variables-----------------------------//
static float BatteryVoltageBuffer[MeanLength];

//-----------------------Private prototypes----------------------------//
static void pub_Perform( void );
static void pub_AdjustPwm( float *PWM );

static float priv_GetNewMean( float NewValue );

//-----------------------Private functions-----------------------------//
static void pub_Perform( void )
{
   ADC_RegularChannelConfig(ADC4, ADC_BATTERY_CHANNEL, 1, ADC_SampleTime_61Cycles5);
   ADC_StartConversion(ADC4);

   while (!ADC_GetFlagStatus(ADC4, ADC_FLAG_EOC));
   oBattery.Voltage = priv_GetNewMean ( (float)GetVoltage( ADC_GetConversionValue( ADC_BATTERY ) ) );
}

static void pub_AdjustPwm( float *PWM )
{
   if( MinBatteryVoltage < oBattery.Voltage )
   {
      *PWM *= MaxBatteryVoltage / oBattery.Voltage;
   }
   else *PWM = 0;
}

static float priv_GetNewMean( float NewValue )
{
   uint8_t Counter;
   /*! Shifting buffer one position right (>>) */
   for( Counter = MeanLength - 2; Counter != 0; Counter-- )
   {
      BatteryVoltageBuffer[Counter + 1] =  BatteryVoltageBuffer[Counter];
   }
   BatteryVoltageBuffer[1] =  BatteryVoltageBuffer[0];
   BatteryVoltageBuffer[0] = NewValue;

   /*! Add last measurements */
   float Sum = 0;
   for( Counter = MeanLength - 1; Counter != 0; Counter-- )
   {
      Sum += BatteryVoltageBuffer[Counter];
   }
   Sum += BatteryVoltageBuffer[0];

   /*! return mean */
   return ( Sum / MeanLength );
}

static void priv_MeanBufferInitialize()
{
   uint8_t Counter;
   for( Counter = 0; Counter <= MeanLength; Counter++ )
   {
      BatteryVoltageBuffer[Counter] =  MeanDefVoltageValue;
   }
}

//-----------------------Public functions------------------------------//
void InitializeBattery()
{
   //-------------HARDWARE-------------//
   InitializeRCC( DriverSelectBattery );
   InitializeGPIO( DriverSelectBattery );
   InitializeADC( DriverSelectBattery );

   //-------------SOFTWARE-------------//
   priv_MeanBufferInitialize();
   oBattery.Perform = pub_Perform;
   oBattery.AdjustPwm = pub_AdjustPwm;
}