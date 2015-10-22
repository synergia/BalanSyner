
//-----------------------Includes-------------------------------------//
#include "Wifi.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void InitializeWifi()
{
#ifdef USART_WIFI

	GPIO_InitTypeDef usart_gpio;
	/* Configure USART Tx and Rx as alternate function push-pull */
	usart_gpio.GPIO_Mode = GPIO_Mode_AF;
	usart_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	usart_gpio.GPIO_OType = GPIO_OType_PP;
	usart_gpio.GPIO_PuPd = GPIO_PuPd_UP;
	usart_gpio.GPIO_Pin = USART_WIFI_TX_PIN;
	GPIO_Init(USART_BT_TX_GPIO, &usart_gpio);

	//usart_gpio.GPIO_Pin = USART_WIFI_RX_PIN;
	//GPIO_Init(USART_WIFI_RX_GPIO, &usart_gpio);

	//GPIO_PinAFConfig(USART_WIFI_RX_GPIO, USART_WIFI_RX_SOURCE, USART_AF_WIFI);
	GPIO_PinAFConfig(USART_WIFI_TX_GPIO, USART_WIFI_TX_SOURCE, USART_AF_WIFI);

#endif
}

void Wifi_Send(uint8_t Char)
{
#ifdef USART_WIFI
	while (USART_GetFlagStatus(USART_WIFI, USART_FLAG_TXE) == RESET);
	USART_SendData(USART_WIFI, Char);
#endif
}
