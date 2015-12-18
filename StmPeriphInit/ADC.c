
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
   static uint8_t AlreadyDone = 0;
   if( 0 == AlreadyDone )
   {
      AlreadyDone = 1;

      ADC_InitTypeDef       ADC_InitStructure;
      ADC_CommonInitTypeDef ADC_CommonInitStructure;

      ADC_StructInit(&ADC_InitStructure);

      /* Calibration procedure */
      ADC_VoltageRegulatorCmd(ADC4, ENABLE);

      /* Insert delay equal to 10 µs */
      uint32_t i;
      for( i = 0; i < 720; i++ );

      ADC_SelectCalibrationMode(ADC4, ADC_CalibrationMode_Single);
      ADC_StartCalibration(ADC4);

      while(ADC_GetCalibrationStatus(ADC4) != RESET );

      ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
      ADC_CommonInitStructure.ADC_Clock = ADC_Clock_AsynClkMode;
      ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
      ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAAccessMode_Disabled;
      ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;

      ADC_CommonInit(ADC4, &ADC_CommonInitStructure);

      ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Disable;
      ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
      ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
      ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
      ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
      ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;
      ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
      ADC_InitStructure.ADC_NbrOfRegChannel = 1;
      ADC_Init(ADC4, &ADC_InitStructure);

   /* Enable ADC4 */
   ADC_Cmd(ADC4, ENABLE);

   /* wait for ADRDY */
   while(!ADC_GetFlagStatus(ADC4, ADC_FLAG_RDY));
   }
}
