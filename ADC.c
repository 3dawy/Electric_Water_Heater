
#include "ADC.h"
#include <pic16f877a.h>
#include "delay.h"

#define ADC_RIGHT_JUSTIFIED_AND_ALL_PINS_ANALOG   0X80
#define CHANNEL_SHIFT_FACTOR                      3
#define HIGH_RESULT_RIGHT_SHIFT                   8




void ADC_Init (void)
{
    /*sampling freq=osc_freq/2,ADC off initially*/
    ADCON0 = 0x00;
    
    /*All pins are configured as Analog input pins and
      the 10-bit ADC result is right justified */
    ADCON1 = ADC_RIGHT_JUSTIFIED_AND_ALL_PINS_ANALOG;
}



void ADC_StartConversion (AdcChannel_et Channel)
{
    /* select ADC channel*/
    ADCON0 = (Channel << CHANNEL_SHIFT_FACTOR);
    
    /*Enable ADC module*/
    util_BitSet(ADCON0, _ADCON0_ADON_POSN );
    
    /*Start conversion*/
    util_BitSet(ADCON0, _ADCON0_GO_nDONE_POSN);
}



void ADC_GetValue (uint16_t* ptr_Value)
{
    /*Wait until the conversion complete*/
    while(GO_DONE == HIGH);
    
    /*Return the conversion result*/
    *ptr_Value = ((ADRESH << HIGH_RESULT_RIGHT_SHIFT) | ADRESL) ; 
}
