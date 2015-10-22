#ifndef PINDEFINES_H_
#define PINDEFINES_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Framework/inc/stm32f30x_gpio.h"

//-----------------------Public typedefs------------------------------//
typedef enum
{
	SelectLed14,
	SelectLedEye,
	SelectLedNucleo,
	SelectBt,
	SelectWifi,
	SelectPi,
	SelectMpu,
} DriverSelector;
//-----------------------Public defines-------------------------------//
/*!
 * _USE_define
 */
//#define _USE_LED_14
//#define _USE_LED_EYE
#define _USE_LED_NUCLEO

#define _USE_BT
//#define _USE_WIFI
//#define _USE_PI
#define _USE_MPU

/*!
 * LEDs
 */
#define	LED_NUCLEO_GPIO		GPIOA
#define LED_NUCLEO_PIN		GPIO_Pin_5
#define LED1_GPIO 			GPIOB
#define LED1_PIN 			GPIO_Pin_12
#define LED2_GPIO 			GPIOB
#define LED2_PIN 			GPIO_Pin_13
#define LED3_GPIO 			GPIOA
#define LED3_PIN 			GPIO_Pin_10
#define LED4_GPIO 			GPIOA
#define LED4_PIN 			GPIO_Pin_11
#define LED_EYE_GPIO		GPIOA
#define LED_EYE_PIN			GPIO_Pin_12

/*!
 * Buttons
 */
#define BUTTON_OK_GPIO		GPIOB
#define BUTTON_OK_PIN		GPIO_Pin_10
#define BUTTON_BACK_GPIO	GPIOB
#define BUTTON_BACK_PIN		GPIO_Pin_2
#define BUTTON_UP_GPIO		GPIOC
#define BUTTON_UP_PIN		GPIO_Pin_8
#define BUTTON_DOWN_GPIO	GPIOB
#define BUTTON_DOWN_PIN		GPIO_Pin_1

/*!
 * MOTOR
 */
#define MOT1_DIRA_GPIO		GPIOC
#define MOT1_DIRA_PIN		GPIO_Pin_12
#define MOT1_DIRB_GPIO		GPIOB
#define MOT1_DIRB_PIN		GPIO_Pin_5

#define MOT1_PWM_GPIO		GPIOC
#define MOT1_PWM_PIN		GPIO_Pin_1
#define MOT1_PWM_SOURCE		GPIO_PinSource1
#define MOT1_AF				GPIO_AF_2


#define MOT2_DIRA_GPIO		GPIOB
#define MOT2_DIRA_PIN		GPIO_Pin_9
#define MOT2_DIRB_GPIO		GPIOB
#define MOT2_DIRB_PIN		GPIO_Pin_8

#define MOT2_PWM_GPIO		GPIOC
#define MOT2_PWM_PIN		GPIO_Pin_0

#define MOT1_TIMER			TIM1
#define CHANNEL_MOT1		2

#define TIMER_MOT2			TIM1
#define CHANNEL_MOT2		1

/*!
 * SERVOs
 */
#define SER_ARM_L_PWM_GPIO	GPIOC
#define SER_ARM_L_PWM_PIN	GPIO_Pin_6

#define SER_ARM_P_PWM_GPIO	GPIOC
#define SER_ARM_P_PWM_PIN	GPIO_Pin_7

#define SER_HOR_PWM_GPIO	GPIOC
#define SER_HOR_PWM_PIN		GPIO_Pin_2

#define SER_VER_PWM_GPIO	GPIOC
#define SER_VER_PWM_PIN		GPIO_Pin_3

#define TIMER_SER_ARM_L_PWM	TIM3_CH1
#define TIMER_SER_ARM_P_PWM	TIM3_CH2
#define TIMER_SER_HOR_PWM	TIM1_CH3
#define TIMER_SER_VER_PWM	TIM1_CH4

/*!
 * ADC
 */
#define ADC_SHARP_GPIO		GPIOB
#define ADC_SHARP_PIN		GPIO_Pin_15

#define ADC_BATTERY_GPIO	GPIOB
#define ADC_BATTERY_PIN		GPIO_Pin_14

#define ADC_SHARP_CHANNEL	ADC4_IN5
#define ADC_BATTERY_CHANNEL	ADC4_IN4
#define ADC_IRQn			ADC4_IRQn

/*!
 * USART
 */
#define USART_BT			USART2
#define USART_BT_IRQn		USART2_IRQn
#define USART_AF_BT			GPIO_AF_7

#define USART_BT_RX_GPIO	GPIOA
#define USART_BT_RX_PIN		GPIO_Pin_3
#define USART_BT_RX_SOURCE	GPIO_PinSource3
#define USART_BT_TX_GPIO	GPIOA
#define USART_BT_TX_PIN		GPIO_Pin_2
#define USART_BT_TX_SOURCE	GPIO_PinSource2

#define USART_WIFI				USART1
#define USART_WIFI_IRQn			USART1_IRQn
#define USART_AF_WIFI			GPIO_AF_7

#define USART_WIFI_RX_GPIO		GPIOC
#define USART_WIFI_RX_PIN		GPIO_Pin_5
#define USART_WIFI_RX_SOURCE	GPIO_PinSource5
#define USART_WIFI_TX_GPIO		GPIOC
#define USART_WIFI_TX_PIN		GPIO_Pin_4
#define USART_WIFI_TX_SOURCE	GPIO_PinSource4

#define USART_PI			USART3
#define USART_PI_IRQn		USART3_IRQn
#define USART_PI_RX_GPIO	GPIOC
#define USART_PI_RX_PIN		GPIO_Pin_11
#define USART_PI_TX_GPIO	GPIOC
#define USART_PI_TX_PIN		GPIO_Pin_10

/*!
 * ACCELEROMETER+GYROSCOPE (MPU)
 */
#define MPU_I2C				I2C3
#define MPU_AF_I2C3			GPIO_AF_3

#define MPU_SCL_GPIO		GPIOA
#define MPU_SCL_PIN			GPIO_Pin_8
#define MPU_SCL_SOURCE		GPIO_PinSource8

#define MPU_SDA_GPIO		GPIOC
#define MPU_SDA_PIN			GPIO_Pin_9
#define MPU_SDA_SOURCE		GPIO_PinSource9

#define MPU_AD0_GPIO		GPIOA
#define MPU_AD0_PIN			GPIO_Pin_9


/*!
 * ENCODERs
 */
#define ENC1_A_GPIO			GPIOB
#define ENC1_A_PIN			GPIO_Pin_6
#define ENC1_B_GPIO			GPIOB
#define ENC1_B_PIN			GPIO_Pin_7

#define ENC2_A_GPIO			GPIOA
#define ENC2_A_PIN			GPIO_Pin_0
#define ENC2_B_GPIO			GPIOA
#define ENC2_B_PIN			GPIO_Pin_1

#define TIMER_ENC1_A		TIM4_CH1
#define TIMER_ENC1_B		TIM4_CH2
#define TIMER_ENC2_A		TIM2_CH1
#define TIMER_ENC2_B		TIM2_CH2

/*!
 * S65 DISPLAY
 */
#define S65_PWM_GPIO		GPIOB
#define S65_PWM_PIN			GPIO_Pin_0

#define S65_MOSI_GPIO		GPIOA
#define S65_MOSI_PIN		GPIO_Pin_7

#define S65_RS_GPIO			GPIOA
#define S65_RS_PIN			GPIO_Pin_6
#define S65_RESET_GPIO		GPIOB
#define S65_RESET_PIN		GPIO_Pin_11
#define S65_CS_GPIO			GPIOA
#define S65_CS_PIN			GPIO_Pin_4

//TODO:define it
#define TIMER_S65_PWM		TIM3_CH3
//#define S65_SPI			SPI1

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//

#endif
