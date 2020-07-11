#include "APP_DATA.h"

uint8_t u8_CurrentTemp,
        u8_SetTemp = 60;

static SysStatus_et  SysStatus = Sys_Off;

void CurTemp_Setter (uint8_t Value)
{
    u8_CurrentTemp = Value;
}
void CurTemp_getter (uint8_t* Value)
{
    *Value = u8_CurrentTemp;
}

void SetTemp_Setter (uint8_t Value)
{
    u8_SetTemp = Value;
}
void SetTemp_getter (uint8_t* Value)
{
    *Value = u8_SetTemp;
}

//void DisTemp_Setter (uint8_t Value)
//{
//    DisTemp = Value;
//}
//void DisTemp_getter (uint8_t* Value)
//{
//    *Value = DisTemp;
//}

void SysStatus_Setter (SysStatus_et Value)
{
    SysStatus = Value;
}
void SysStatus_getter (SysStatus_et* Value)
{
    *Value = SysStatus;
}
        
