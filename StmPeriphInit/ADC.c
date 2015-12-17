
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "ADC.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void InitializeADC( uint8_t GPIO_Selector )
{
   ADC_TypeDef *ADCx = ADC4;

   ADC_InitTypeDef       ADC_InitStructure;
   ADC_CommonInitTypeDef ADC_CommonInitStructure;

   ADC_StructInit(&ADC_InitStructure);

   /* Calibration procedure */
   ADC_VoltageRegulatorCmd(ADCx, ENABLE);

   /* Insert delay equal to 10 µs */
   uint32_t i;
   for( i = 0; i < 720; i++ );

   ADC_SelectCalibrationMode(ADCx, ADC_CalibrationMode_Single);
   ADC_StartCalibration(ADCx);

   while(ADC_GetCalibrationStatus(ADCx) != RESET );

   ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
   ADC_CommonInitStructure.ADC_Clock = ADC_Clock_AsynClkMode;
   ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
   ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_OneShot;
   ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;

   ADC_CommonInit(ADCx, &ADC_CommonInitStructure);

   ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
   ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
   ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
   ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
   ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
   ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;
   ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
   ADC_InitStructure.ADC_NbrOfRegChannel = 1;
   ADC_Init(ADCx, &ADC_InitStructure);

   /* ADCx regular channel7 configuration */
   switch ( GPIO_Selector )
   {
      case DriverSelectBattery:
         ADC_RegularChannelConfig(ADCx, ADC_BATTERY_CHANNEL, 1, ADC_SampleTime_7Cycles5);
         break;
      case DriverSelectSharp:
         ADC_RegularChannelConfig(ADCx, ADC_SHARP_CHANNEL, 1, ADC_SampleTime_7Cycles5);
         break;
      default:
         while(1);
         break;
   }

   /* Enable ADCx */
   ADC_Cmd(ADCx, ENABLE);

   /* wait for ADRDY */
   while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_RDY));

   /* Start ADC1 Software Conversion */
   ADC_StartConversion(ADCx);

}
