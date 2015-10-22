
//-----------------------Includes-------------------------------------//
#include "stm32f30x.h"
#include "../Framework/inc/stm32f30x_gpio.h"
#include "../Drivers/PinDefines.h"
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
	InitializeRCC(SelectLedNucleo);
	InitializeGPIO(SelectLedNucleo);
}

void InitializeLed14()
{
	InitializeRCC(SelectLed14);
	InitializeGPIO(SelectLed14);
}

void InitializeLedEye()
{
	InitializeRCC(SelectLedEye);
	InitializeGPIO(SelectLedEye);
}
