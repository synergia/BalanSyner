
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Framework/inc/stm32f30x_rcc.h"
#include "RCC.h"
#include "../Drivers/PinDefines.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
void priv_InitializeMPU();
void priv_InitializeLedNucleo();
void priv_InitializeLed14();
void priv_InitializeLedEye();
void priv_InitializeBt();
void priv_InitializePi();
void priv_InitializeWifi();
void priv_InitializeMotors();
void priv_InitializeServosArm();
void priv_InitializeServosCam();

//-----------------------Private functions-----------------------------//
void priv_InitializeMPU()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3, ENABLE);
}

void priv_InitializeLedNucleo()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
}

void priv_InitializeLed14()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
}

void priv_InitializeLedEye()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
}

void priv_InitializeBt()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //todo make it define
}

void priv_InitializeWifi()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //todo make it define
}

void priv_InitializePi()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //todo make it define
}

void priv_InitializeMotors()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
}

void priv_InitializeServosArm()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
}

void priv_InitializeServosCam()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
}

//-----------------------Public functions------------------------------//
void InitializeRCC(uint8_t RCCx)
{
	switch (RCCx)
	{
	case SelectLedNucleo:
		priv_InitializeLedNucleo();
		break;
	case SelectLed14:
		priv_InitializeLed14();
		break;
	case SelectLedEye:
		priv_InitializeLedEye();
		break;
	case SelectMpu:
		priv_InitializeMPU();
		break;
	case SelectBt:
		priv_InitializeBt();
		break;
	case SelectPi:
		priv_InitializePi();
		break;
	case SelectWifi:
		priv_InitializeWifi();
		break;
	case SelectMotors:
		priv_InitializeMotors();
		break;
	case SelectServosArm:
		priv_InitializeServosArm();
		break;
	case SelectServosCam:
		priv_InitializeServosCam();
		break;
	default:
		break;
	}

	/*
	 * ADC
	 */
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC34, ENABLE);

	/*!
	 * SPI
	 */
	//RCC_APB1PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
}
