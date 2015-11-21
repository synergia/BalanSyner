
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Framework/stm32f30x/inc/stm32f30x_gpio.h"
#include "GPIO.h"
#include "RCC.h"
#include "LED.h"

//-----------------------Private typedefs------------------------------//

//-----------------------Private defines-------------------------------//

//-----------------------Private macros--------------------------------//

//-----------------------Private variables-----------------------------//

//-----------------------Private prototypes----------------------------//

//-----------------------Private functions-----------------------------//

//-----------------------Public functions------------------------------//
void InitializeLedNucleo()
{
	InitializeRCC(DriverSelectLedNucleo);
	InitializeGPIO(DriverSelectLedNucleo);
}

void InitializeLed14()
{
	InitializeRCC(DriverSelectLed14);
	InitializeGPIO(DriverSelectLed14);
}

void InitializeLedEye()
{
	InitializeRCC(DriverSelectLedEye);
	InitializeGPIO(DriverSelectLedEye);
}
