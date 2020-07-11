



#include <pic16f877a.h>
#include "delay.h"
#include "7-seg.h"




void SevSeg_Init (SevSegNum_et Number)
{
    GPIO_PortDirection (PORT_D, OUTPUT);
    
    switch (Number)
    {
        case Seg_1:
            GPIO_PinDirection(PA_2, OUTPUT);
            break;
            
        case Seg_2:
            GPIO_PinDirection(PA_3, OUTPUT);
            break;    
    
        case Seg_3:
            GPIO_PinDirection(PA_4, OUTPUT);
            break;
            
        case Seg_4:
            GPIO_PinDirection(PA_5, OUTPUT);
            break;
    }
    
}


void SevSeg_Display (uint8_t Value, SevSegNum_et Number)
{
    uint8_t seg_code[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    
    GPIO_PortWrite (PORT_D, seg_code[Value]);
    
    switch (Number)
    {
        case Seg_1:
            GPIO_PinWrite(PA_2, HIGH);
            GPIO_PinWrite(PA_3, LOW);
            GPIO_PinWrite(PA_4, LOW);
            GPIO_PinWrite(PA_5, LOW);
            break;
            
        case Seg_2:
            GPIO_PinWrite(PA_3, HIGH);
            GPIO_PinWrite(PA_2, LOW);
            GPIO_PinWrite(PA_4, LOW);
            GPIO_PinWrite(PA_5, LOW);
            break;    
    
        case Seg_3:
            GPIO_PinWrite(PA_4, HIGH);
            GPIO_PinWrite(PA_2, LOW);
            GPIO_PinWrite(PA_3, LOW);
            GPIO_PinWrite(PA_5, LOW);
            break;
            
        case Seg_4:
            GPIO_PinWrite(PA_5, HIGH);
            GPIO_PinWrite(PA_2, LOW);
            GPIO_PinWrite(PA_3, LOW);
            GPIO_PinWrite(PA_4, LOW);
            break;
    }
}

void SevSeg_Off (SevSegNum_et Number)
{
    switch (Number)
    {
        case Seg_1:
            GPIO_PinWrite(PA_2, LOW);
            break;
            
        case Seg_2:
            GPIO_PinWrite(PA_3, LOW);
            break;    
    
        case Seg_3:
            GPIO_PinWrite(PA_4, LOW);
            break;
            
        case Seg_4:
            GPIO_PinWrite(PA_5, LOW);
            break;
    }
}