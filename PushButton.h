/* 
 * File:   PushButton.h
 * Author: K.Aladawy
 *
 * Created on July 7, 2020, 9:08 AM
 */

#ifndef PUSHBUTTON_H
#define	PUSHBUTTON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdutils.h"

#define PRESSED      0
#define RELEASED     255
    
typedef enum 
{
    RB_0, RB_1, RB_2, RB_3, RB_4, RB_5, RA_5     
}PBNames_et;

void PB_Init (PBNames_et Name);
uint8_t PB_Status (PBNames_et Name);

#ifdef	__cplusplus
}
#endif

#endif	/* PUSHBUTTON_H */

