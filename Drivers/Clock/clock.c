
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Framework/stm32f30x/inc/stm32f30x_rcc.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void InitializeClock()
{
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
#endif

	/* Enable Internal High Speed oscillator */
	RCC_HSICmd(ENABLE);


	/* Set PLL clock output to 24MHz using HSI (8MHz) as entry clock */
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_6);


	/* Select the PLL as system clock source */
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);


	/* Enable the PLL */
	RCC_PLLCmd(ENABLE);


	/* Output PLL clock divided by 2 on MCO pin */
	//RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);


	/* Configure HCLK such as HCLK = SYSCLK */
	RCC_HCLKConfig(RCC_SYSCLK_Div1);


	/* Configure PCLK1 such as PCLK1 = HCLK/2 */
	RCC_PCLK1Config(RCC_HCLK_Div1);


	/* Configure PCLK2 such as PCLK2 = HCLK */
	RCC_PCLK2Config(RCC_HCLK_Div1);
}
