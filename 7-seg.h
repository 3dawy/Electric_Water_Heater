/* 
 * File:   7-seg.h
 * Author: K.Aladawy
 *
 * Created on June 30, 2020, 12:57 PM
 */

#ifndef _7_SEG_H
#define	_7_SEG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "gpio.h"
#include "stdutils.h"   

typedef enum
{
    Seg_1, Seg_2, Seg_3, Seg_4
}SevSegNum_et;
    
void SevSeg_Init (SevSegNum_et Number);
void SevSeg_Display (uint8_t Value, SevSegNum_et Number);
void SevSeg_Off (SevSegNum_et Number);

#ifdef	__cplusplus
}
#endif

#endif	/* _7_SEG_H */

