#ifndef PINDEFINES_H_
#define PINDEFINES_H_

//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Framework/stm32f30x/inc/stm32f30x_gpio.h"

//-----------------------Public typedefs------------------------------//
typedef enum
{
   DriverSelectLed14 = 0u,
   DriverSelectLedEye,
   DriverSelectLedNucleo,
   DriverSelectBt,
   DriverSelectWifi,
   DriverSelectPi,
   DriverSelectMpu,
   DriverSelectMotors,
   DriverSelectServosArm,
   DriverSelectServosCam,
   DriverSelectEncoders,
   DriverSelectBattery,
   DriverSelectSharp,
} DriverSelector_T;

//-----------------------Public defines-------------------------------//
/*!
 * _USE_define
 */
#define _USE_MOTORS
#define _USE_ENCODERS
#define _USE_SERVOS
#define _USE_LED_14
#define _USE_LED_EYE
//#define _USE_LED_NUCLEO
#define _USE_ADC_BATTERY
#define _USE_ADC_SHARP
#define _USE_BT
//#define _USE_WIFI
//#define _USE_PI
#define _USE_MPU

/*!
 * LEDs
 */
#define LEDNUCLEO_GPIO       GPIOA
#define LEDNUCLEO_PIN        GPIO_Pin_5
#define LED1_GPIO            GPIOB
#define LED1_PIN             GPIO_Pin_12
#define LED2_GPIO            GPIOB
#define LED2_PIN             GPIO_Pin_13
#define LED3_GPIO            GPIOA
#define LED3_PIN             GPIO_Pin_10
#define LED4_GPIO            GPIOA
#define LED4_PIN             GPIO_Pin_11
#define LEDEYE_GPIO          GPIOA
#define LEDEYE_PIN           GPIO_Pin_12

/*!
 * Buttons
 */
#define BUTTON_OK_GPIO     GPIOB
#define BUTTON_OK_PIN      GPIO_Pin_10
#define BUTTON_BACK_GPIO   GPIOB
#define BUTTON_BACK_PIN    GPIO_Pin_2
#define BUTTON_UP_GPIO     GPIOC
#define BUTTON_UP_PIN      GPIO_Pin_2
#define BUTTON_DOWN_GPIO   GPIOC
#define BUTTON_DOWN_PIN    GPIO_Pin_3

/*!
 * MOTOR
 * Warning! Check in RCC.c if channels are selected as you want
 */
#define TIM_AF_MOTOR       GPIO_AF_2
#define TIM_MOTORS         TIM1
#define MOT1_PWM_CHANNEL   CCR2
#define MOT2_PWM_CHANNEL   CCR1

#define MOT1_DIRA_GPIO     GPIOC
#define MOT1_DIRA_PIN      GPIO_Pin_12
#define MOT1_DIRB_GPIO     GPIOB
#define MOT1_DIRB_PIN      GPIO_Pin_5

/*!< ENCODER 1 */
#define TIM_AF_ENC1     GPIO_AF_2

#define TIM_ENC1           TIM4
#define TIM_ENC1_IRQn      TIM4_IRQn
#define ENC1A_CHANNEL      CCR1
#define ENC1B_CHANNEL      CCR2

#define ENC1_GPIO       GPIOB
#define ENC1A_PIN       GPIO_Pin_6
#define ENC1A_SOURCE    GPIO_PinSource6

#define ENC1B_PIN       GPIO_Pin_7
#define ENC1B_SOURCE    GPIO_PinSource7
/*!< END OF ENCODER 1 */

#define MOT2_DIRA_GPIO     GPIOB
#define MOT2_DIRA_PIN      GPIO_Pin_9
#define MOT2_DIRB_GPIO     GPIOB
#define MOT2_DIRB_PIN      GPIO_Pin_8

#define MOT2_PWM_GPIO      GPIOC
#define MOT2_PWM_PIN       GPIO_Pin_1
#define MOT2_PWM_SOURCE    GPIO_PinSource1

#define MOT1_PWM_GPIO      GPIOC
#define MOT1_PWM_PIN       GPIO_Pin_0
#define MOT1_PWM_SOURCE    GPIO_PinSource0

/*!< ENCODER 2 */
#define TIM_AF_ENC2        GPIO_AF_1

#define TIM_ENC2           TIM2
#define TIM_ENC2_IRQn      TIM2_IRQn
#define ENC2A_CHANNEL      CCR1
#define ENC2B_CHANNEL      CCR2

#define ENC2_GPIO       GPIOA
#define ENC2A_PIN       GPIO_Pin_0
#define ENC2A_SOURCE    GPIO_PinSource0

#define ENC2B_PIN       GPIO_Pin_1
#define ENC2B_SOURCE    GPIO_PinSource1
/*!< END OF ENCODER 1 */

/*!
 * SERVOs
 */
#define TIMER_AF_SERVOS       GPIO_AF_2
#define TIM_SERVOS            TIM3

#define SERVO_ARM_L_PWM_CHANNEL  CCR1
#define SERVO_ARM_P_PWM_CHANNEL  CCR2
#define SERVO_HOR_PWM_CHANNEL CCR3
#define SERVO_VER_PWM_CHANNEL CCR4

#define SERVO_ARM_L_PWM_GPIO  GPIOC
#define SERVO_ARM_L_PWM_PIN      GPIO_Pin_6
#define SERVO_ARM_L_PWM_SOURCE   GPIO_PinSource6

#define SERVO_ARM_P_PWM_GPIO  GPIOC
#define SERVO_ARM_P_PWM_PIN      GPIO_Pin_7
#define SERVO_ARM_P_PWM_SOURCE   GPIO_PinSource7

#define SERVO_HOR_PWM_GPIO    GPIOC
#define SERVO_HOR_PWM_PIN     GPIO_Pin_8
#define SERVO_HOR_PWM_SOURCE  GPIO_PinSource8

#define SERVO_VER_PWM_GPIO    GPIOB
#define SERVO_VER_PWM_PIN     GPIO_Pin_1
#define SERVO_VER_PWM_SOURCE  GPIO_PinSource1

/*!
 * ADC
 */
#define ADC_SHARP          ADC4
#define ADC_SHARP_GPIO     GPIOB
#define ADC_SHARP_PIN      GPIO_Pin_15
#define ADC_SHARP_SOURCE   GPIO_PinSource15
#define ADC_SHARP_CHANNEL  ADC_Channel_5

#define ADC_BATTERY           ADC4
#define ADC_BATTERY_GPIO      GPIOB
#define ADC_BATTERY_PIN       GPIO_Pin_14
#define ADC_BATTERY_SOURCE    GPIO_PinSource14
#define ADC_BATTERY_CHANNEL   ADC_Channel_4

/*!
 * USART
 */
#define USART_BT           USART2
#define USART_BT_IRQn      USART2_IRQn
#define USART_AF_BT        GPIO_AF_7

#define USART_BT_RX_GPIO   GPIOA
#define USART_BT_RX_PIN    GPIO_Pin_3
#define USART_BT_RX_SOURCE GPIO_PinSource3
#define USART_BT_TX_GPIO   GPIOA
#define USART_BT_TX_PIN    GPIO_Pin_2
#define USART_BT_TX_SOURCE GPIO_PinSource2

#define USART_WIFI            USART1
#define USART_WIFI_IRQn       USART1_IRQn
#define USART_AF_WIFI         GPIO_AF_7

#define USART_WIFI_RX_GPIO    GPIOC
#define USART_WIFI_RX_PIN     GPIO_Pin_5
#define USART_WIFI_RX_SOURCE  GPIO_PinSource5
#define USART_WIFI_TX_GPIO    GPIOC
#define USART_WIFI_TX_PIN     GPIO_Pin_4
#define USART_WIFI_TX_SOURCE  GPIO_PinSource4

#define USART_PI           USART3
#define USART_PI_IRQn      USART3_IRQn
#define USART_PI_RX_GPIO   GPIOC
#define USART_PI_RX_PIN    GPIO_Pin_11
#define USART_PI_TX_GPIO   GPIOC
#define USART_PI_TX_PIN    GPIO_Pin_10

/*!
 * ACCELEROMETER+GYROSCOPE (MPU)
 */
#define MPU_I2C            I2C3
#define MPU6050_I2C        I2C3
#define MPU6050_ADDRESS    0b1101000
#define MPU_AF_I2C3        GPIO_AF_3

#define MPU_SCL_GPIO       GPIOA
#define MPU_SCL_PIN        GPIO_Pin_8
#define MPU_SCL_SOURCE     GPIO_PinSource8

#define MPU_SDA_GPIO    GPIOC
#define MPU_SDA_PIN        GPIO_Pin_9
#define MPU_SDA_SOURCE     GPIO_PinSource9

#define MPU_AD0_GPIO       GPIOA
#define MPU_AD0_PIN        GPIO_Pin_9

/*!
 * S65 DISPLAY
 */
#define S65_PWM_GPIO       GPIOA
#define S65_PWM_PIN        GPIO_Pin_6

#define S65_MOSI_GPIO      GPIOA
#define S65_MOSI_PIN       GPIO_Pin_7

#define S65_RS_GPIO        GPIOB
#define S65_RS_PIN         GPIO_Pin_0
#define S65_RESET_GPIO     GPIOB
#define S65_RESET_PIN      GPIO_Pin_11
#define S65_CS_GPIO        GPIOA
#define S65_CS_PIN         GPIO_Pin_4

#define TIMER_S65_PWM      TIM16_CH1
//#define S65_SPI       SPI1

//-----------------------Public macros--------------------------------//

//-----------------------Public variables-----------------------------//

//-----------------------Public prototypes----------------------------//

#endif
