/* 
 * File:   LM35.h
 * Author: K.Aladawy
 *
 * Created on July 7, 2020, 10:22 AM
 */

#ifndef LM35_H
#define	LM35_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdutils.h"
    
void LM35_Init (void);
void LM35_Value (uint8_t* Temp);



#ifdef	__cplusplus
}
#endif

#endif	/* LM35_H */

