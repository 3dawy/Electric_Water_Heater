#include "PushButton.h"
#include "gpio.h"


void PB_Init (PBNames_et Name)
{
    if (Name <= 5)
    {
        GPIO_PinDirection((Name+8), INPUT);
    }
    else 
    {
        GPIO_PinDirection(PA_5, INPUT);
    }
}

uint8_t PB_Status (PBNames_et Name)
{
    uint8_t au8_Status;
    if (Name <= 5)
    {
        au8_Status = GPIO_PinRead(Name+8);
    }
    else 
    {
        au8_Status = GPIO_PinRead(PA_5);
    }
    return (au8_Status);
}