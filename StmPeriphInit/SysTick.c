
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "SysTick.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
extern void MainTask16ms();
extern void MainTask128ms();

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//

void InitializeSysTick()
{
   SysTick_Config(SYSTICK_FREQUENCY_KHZ>>0);
   SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
   NVIC_SetPriority(SysTick_IRQn, 0x0);
}

void SysTick_Handler(void)
{
   static uint16_t Counter = 124;

   //-------------------------8ms tasks-------------------------------------//
   --Counter;

   if( 0 == (Counter % 2) )
   {
      MainTask16ms();
   }

   //-------------------------128ms tasks-------------------------------------//
   if( 0 == (Counter % 16) )
   {
      MainTask128ms();
   }

   //-------------------------1000ms(1Hz) tasks-------------------------------------//
   if( 0 == Counter)
   {
      Counter = 124;
   }

}
