#include "LED.h"
#include "gpio.h"


void LED_Init (LedName_et Led)
{
    GPIO_PinDirection((Led+8), OUTPUT);
}
void LED_Status (LedName_et Led, LedStatus_et Status)
{
    if (LED_OFF == Status)
    {
        GPIO_PinWrite((Led+8), LOW);
    }
    else if (LED_ON == Status)
    {
        GPIO_PinWrite((Led+8), HIGH);
    }
    else if (LED_TOGGLE == Status)
    {
        GPIO_PinToggle(Led+8);
    }
}

