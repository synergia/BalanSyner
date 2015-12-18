
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

      DMA_InitTypeDef  DMA_InitStructure;

      DMA_DeInit(DMA2_Channel2);
      DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC4->DR;
      DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
      DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
      DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AdcBufferTable;
      DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
      DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
      DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
      DMA_InitStructure.DMA_BufferSize = 2;
      DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
      DMA_InitStructure.DMA_Priority = DMA_Priority_High;
      DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
      DMA_Init(DMA2_Channel2, &DMA_InitStructure);

      /* Enable DMA2 Channel2 */
      DMA_Cmd(DMA2_Channel2, ENABLE);


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
      ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
      ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_Circular;
      ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;

      ADC_CommonInit(ADC4, &ADC_CommonInitStructure);

      ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
      ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
      ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_1;
      ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
      ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
      ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;
      ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
      ADC_InitStructure.ADC_NbrOfRegChannel = 2;
      ADC_Init(ADC4, &ADC_InitStructure);

      ADC_RegularChannelConfig(ADC4, ADC_BATTERY_CHANNEL, BatteryNumber, ADC_SampleTime_61Cycles5);
      ADC_RegularChannelConfig(ADC4, ADC_SHARP_CHANNEL, SharpNumber, ADC_SampleTime_61Cycles5);

      ADC_Cmd(ADC4, ENABLE);

      /* wait for ADRDY */
      while(!ADC_GetFlagStatus(ADC4, ADC_FLAG_RDY));

      /* ADC1 DMA Enable */
      ADC_DMACmd(ADC4, ENABLE);
      ADC_DMAConfig(ADC4, ADC_DMAMode_Circular);

      /* Start ADC1 Software Conversion */
      ADC_StartConversion(ADC4);
   }
}
