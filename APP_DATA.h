/* 
 * File:   APP_DATA.h
 * Author: K.Aladawy
 *
 * Created on July 7, 2020, 10:59 AM
 */

#ifndef APP_DATA_H
#define	APP_DATA_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdutils.h"
    

typedef enum
{
    Sys_On, Sys_Off
}SysStatus_et;


void CurTemp_Setter (uint8_t Value);
void CurTemp_getter (uint8_t* Value);

void SetTemp_Setter (uint8_t Value);
void SetTemp_getter (uint8_t* Value);

void SysStatus_Setter (SysStatus_et Value);
void SysStatus_getter (SysStatus_et* Value);   

#ifdef	__cplusplus
}
#endif

#endif	/* APP_DATA_H */

