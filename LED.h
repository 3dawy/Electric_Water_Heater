/* 
 * File:   LED.h
 * Author: K.Aladawy
 *
 * Created on July 7, 2020, 9:48 AM
 */

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdutils.h"
    
typedef enum
{
    B0,B1,B2,B3,B4,B5,B6,B7
}LedName_et;

typedef enum
{
    LED_OFF,LED_ON,LED_TOGGLE
}LedStatus_et;

void LED_Init (LedName_et Led);
void LED_Status (LedName_et Led, LedStatus_et Status);


#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

