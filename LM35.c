#include "LM35.h"
#include "ADC.h"


void LM35_Init (void)
{
    ADC_Init();
}
void LM35_Value (uint8_t* Temp)
{
    uint16_t Data;
    
    ADC_StartConversion(AN2);
        
    ADC_GetValue(&Data);
        
    *Temp = Data/2;
}
