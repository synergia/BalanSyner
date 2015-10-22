
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Drivers/PinDefines.h"
#include "GPIO.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//
static void priv_InitializeLed14();
static void priv_InitializeLedEye();
static void priv_InitializeLedNucleo();
static void priv_InitializeBt();
static void priv_InitializeWifi();
static void priv_InitializePi();
static void priv_InitializeMpu();

//-----------------------Private functions-----------------------------//
static void priv_InitializeLed14()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;	// to save power

	GPIO_InitStruct.GPIO_Pin = LED1_PIN;
	GPIO_Init(LED1_GPIO, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LED2_PIN;
	GPIO_Init(LED2_GPIO, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LED3_PIN;
	GPIO_Init(LED3_GPIO, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LED4_PIN;
	GPIO_Init(LED4_GPIO, &GPIO_InitStruct);
}

static void priv_InitializeLedEye()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;	// to save power

	GPIO_InitStruct.GPIO_Pin = LED_EYE_PIN;
	GPIO_Init(LED_EYE_GPIO, &GPIO_InitStruct);
}

static void priv_InitializeLedNucleo()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;	// to save power

	GPIO_InitStruct.GPIO_Pin = LED_NUCLEO_PIN;
	GPIO_Init(LED_NUCLEO_GPIO, &GPIO_InitStruct);
}

static void priv_InitializeBt()
{
	GPIO_PinAFConfig(USART_BT_RX_GPIO, USART_BT_RX_SOURCE, USART_AF_BT);
	GPIO_PinAFConfig(USART_BT_TX_GPIO, USART_BT_TX_SOURCE, USART_AF_BT);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Pin = USART_BT_TX_PIN;
	GPIO_Init(USART_BT_TX_GPIO, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = USART_BT_RX_PIN;
	GPIO_Init(USART_BT_RX_GPIO, &GPIO_InitStruct);
}

static void priv_InitializeWifi()
{
	//todo write it
}

static void priv_InitializePi()
{
	//todo write it
}
static void priv_InitializeMpu()
{
	GPIO_PinAFConfig(MPU_SDA_GPIO, MPU_SDA_SOURCE, MPU_AF_I2C3);
	GPIO_PinAFConfig(MPU_SCL_GPIO, MPU_SCL_SOURCE, MPU_AF_I2C3);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStruct.GPIO_Pin = MPU_SDA_PIN;
	GPIO_Init(MPU_SDA_GPIO, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = MPU_SCL_PIN;
	GPIO_Init(MPU_SCL_GPIO, &GPIO_InitStruct);
}

//-----------------------Public functions------------------------------//
void InitializeGPIO(uint8_t GPIOx)
{
	switch (GPIOx)
	{
	case SelectLed14:
		priv_InitializeLed14();
		break;
	case SelectLedEye:
		priv_InitializeLedEye();
		break;
	case SelectLedNucleo:
		priv_InitializeLedNucleo();
		break;
	case SelectBt:
		priv_InitializeBt();
		break;
	case SelectWifi:
		priv_InitializeWifi();
		break;
	case SelectPi:
		priv_InitializePi();
		break;
	case SelectMpu:
		priv_InitializeMpu();
		break;

	default:
		break;
	}

}
