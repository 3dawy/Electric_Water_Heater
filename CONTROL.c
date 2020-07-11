#include "CONTROL.h"
#include "EXT_EEPROM.h"
#include "PushButton.h"
#include "APP_DATA.h"


#define ON_OFF_PB                    RB_3
#define CHANGE_ON_OFF_PB_FLAG        1
#define SET_ON_OFF_PB_FLAG           2
#define NEGLECT_ON_OFF_PB_FLAG       3
#define EXT_EEPROM_BYTE_ADD          0x00
#define COUNTER_INITIAL_VALUE        0
#define SET_TEMP_INITIAL_VALUE       60 
#define PB_PUSH_FACTOR               3
#define MAX_SET_TEMP                 75
#define MIN_SET_TEMP                 35


void Control_Init (void)
{
    EXTEEPROM_Init();

    PB_Init(ON_OFF_PB);
   
}


void Control_Update (void)
{
    static SysStatus_et u8_Status = Sys_Off; /*variable to store system status*/
    static uint8_t OnOffPB_Flag = NEGLECT_ON_OFF_PB_FLAG; /*variable to store on/off button status*/
    uint8_t u8_SetTemp = SET_TEMP_INITIAL_VALUE; /*variable to store set temp*/
    static uint8_t u8_Counter= COUNTER_INITIAL_VALUE; /*counter used to get pushbutton one click*/
    
    /*ON/OFF PUSH BUTTON STATE MACHINE*/
    switch (OnOffPB_Flag)
    {
        case NEGLECT_ON_OFF_PB_FLAG:
            /*in case push button pressed for 150 ms change the status*/
            if (PRESSED == PB_Status(ON_OFF_PB))
            {
                u8_Counter++; /*Counter used to get one click*/
            }
            if (PB_PUSH_FACTOR < u8_Counter)
            {
                OnOffPB_Flag = SET_ON_OFF_PB_FLAG;
            }
            break;
            
        case SET_ON_OFF_PB_FLAG:
            if (PRESSED != PB_Status(ON_OFF_PB))
            {
                u8_Counter--;
                
            }
            if (PB_PUSH_FACTOR > u8_Counter)
            {
                OnOffPB_Flag = CHANGE_ON_OFF_PB_FLAG;
            }
            break;
            
        case CHANGE_ON_OFF_PB_FLAG:
                OnOffPB_Flag = NEGLECT_ON_OFF_PB_FLAG;
                u8_Counter = COUNTER_INITIAL_VALUE;
            
            break;
            
        default:
            break;
    }

    /*SYSTEM ON/OFF STATUS STATE MACHINE*/
    switch (u8_Status)
    {
        case Sys_Off:
            if (CHANGE_ON_OFF_PB_FLAG == OnOffPB_Flag)
            {
                u8_Status = Sys_On; /*turn system on*/
                
                SysStatus_Setter(Sys_On); /*update system status to other app s/w components*/
                
                EXTEEPROM_ReadByte(&u8_SetTemp, EXT_EEPROM_BYTE_ADD); /*get set temp from ext_eeprom*/
                if((MAX_SET_TEMP < u8_SetTemp)||(MIN_SET_TEMP > u8_SetTemp))
                {
                    u8_SetTemp = SET_TEMP_INITIAL_VALUE;
                }
                SetTemp_Setter(u8_SetTemp); /*update set temp to other app s/w components*/
            }
            else
            {
                SysStatus_Setter(Sys_Off);
            }
            break;
        /********************************************************************************/
        /********************************************************************************/
        case Sys_On:
            if (CHANGE_ON_OFF_PB_FLAG == OnOffPB_Flag)
            {
                u8_Status = Sys_Off; /*turn system off*/
                
                SetTemp_getter(&u8_SetTemp); /*get set temp from other app s/w components*/
                
                EXTEEPROM_WriteByte(u8_SetTemp,EXT_EEPROM_BYTE_ADD); /*store set temp to ext_eeprom*/
                
                SysStatus_Setter(Sys_Off); /*update system status to other app s/w components*/
            }
            else
            {
                SysStatus_Setter(Sys_On);
            }
            break;
        /********************************************************************************/
        /********************************************************************************/
        default:
            break;
    }
    
}
