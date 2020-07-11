/* 
 * File:   ADC.h
 * Author: K.Aladawy
 *
 * Created on June 30, 2020, 7:28 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdutils.h"

    
typedef enum 
{
    AN0=0,
    AN1=1, 
    AN2=2, 
    AN3=3, 
    AN4=4, 
    AN5=5, 
    AN6=6, 
    AN7=7 
}AdcChannel_et;

void ADC_Init (void);
void ADC_StartConversion (AdcChannel_et Channel);
void ADC_GetValue (uint16_t* ptr_Value);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

