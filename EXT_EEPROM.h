/* 
 * File:   EXT_EEPROM.h
 * Author: K.Aladawy
 *
 * Created on July 7, 2020, 10:07 AM
 */

#ifndef EXT_EEPROM_H
#define	EXT_EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdutils.h"
    
void EXTEEPROM_Init (void);
void EXTEEPROM_WriteByte (uint8_t Data, uint8_t ByteAdd);
void EXTEEPROM_ReadByte (uint8_t* Data, uint8_t ByteAdd);


#ifdef	__cplusplus
}
#endif

#endif	/* EXT_EEPROM_H */

