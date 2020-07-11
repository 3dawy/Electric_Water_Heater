#include "OPERATING_MODE.h"
#include "7-seg.h"
#include "PushButton.h"
#include "APP_DATA.h"



#define UP_PB                                  RB_1
#define DOWN_PB                                RB_2
#define CURRENT_TEMP_INITIAIL_VALUE            0
#define UP_PB_COUNTER_INITIAL_VALUE            0
#define DOWN_PB_COUNTER_INITIAL_VALUE          0
#define PB_CLICK_FACTOR                        3
#define SEV_SEG_BLINKING_COUNTER_INITIAL_VALUE 0
#define MAX_SET_TEMP                           75
#define MIN_SET_TEMP                           35
#define SET_TEMP_CHANGE_FACTOR                 5
#define SWITCH_MODE_COUNTER_INITAL_VALUE       0

typedef enum 
{
    Mode_Normal=13, Mode_Setting=21
}Mode_et;
typedef enum
{
    UP_PRESS,DOWN_PRESS,NO_PRESS
}SetTempPB_et;
typedef enum
{
    FIRST_SEV_SEG,SECOND_SEV_SEG
}SevSegFlag_et;

void OperatingMode_Init (void)
{    
    PB_Init(UP_PB);
    
    PB_Init(DOWN_PB);
    
    SevSeg_Init(Seg_3);
    
    SevSeg_Init(Seg_4);
}
void OperatingMode_Update (void)
{
    static Mode_et en_Mode = Mode_Normal;
    uint8_t u8_CurrentTemp = CURRENT_TEMP_INITIAIL_VALUE;
    SetTempPB_et SetTempPB = NO_PRESS;
    static uint8_t u8_SetTemp = 60;
    SysStatus_et Status = Sys_Off;
    static uint8_t u8_UpPBCounter = UP_PB_COUNTER_INITIAL_VALUE;
    static uint8_t u8_DownPBCounter = DOWN_PB_COUNTER_INITIAL_VALUE;
    static uint8_t u8_SevSegBlinkingCounter = SEV_SEG_BLINKING_COUNTER_INITIAL_VALUE;
    static uint8_t u8_SwitchModeCounter = SWITCH_MODE_COUNTER_INITAL_VALUE;
    static SevSegFlag_et SevSeg = FIRST_SEV_SEG;
    
    /*get on/off system status*/
    SysStatus_getter(&Status);
    
    /*in case system off turn 7-seg off*/
    if (Sys_Off == Status)
    {
        SevSeg_Off(Seg_3);
        
        SevSeg_Off(Seg_4);
    }
    /*in case system status is on*/
    else if (Sys_On == Status)
    {
        /*check if up or down push button pressed*/
        if (PRESSED == PB_Status(UP_PB))
        {
            /*counter helps in catch one click*/
            u8_UpPBCounter++;
            u8_DownPBCounter = DOWN_PB_COUNTER_INITIAL_VALUE;
        }
        else if (PRESSED == PB_Status(DOWN_PB))
        {
            /*counter helps in catch one click*/
            u8_DownPBCounter++;
            u8_UpPBCounter = UP_PB_COUNTER_INITIAL_VALUE;
        }
        else
        {
            u8_UpPBCounter = UP_PB_COUNTER_INITIAL_VALUE;
            u8_DownPBCounter = DOWN_PB_COUNTER_INITIAL_VALUE;
        }
        /*set temp push buttons status*/
        if(PB_CLICK_FACTOR == u8_UpPBCounter)
        {
            SetTempPB = UP_PRESS;
            u8_UpPBCounter = UP_PB_COUNTER_INITIAL_VALUE;
        }
        else if (PB_CLICK_FACTOR == u8_DownPBCounter)
        {
            SetTempPB = DOWN_PRESS;
            u8_DownPBCounter = DOWN_PB_COUNTER_INITIAL_VALUE;            
        }
        else 
        {
            SetTempPB = NO_PRESS;
        }
        /*SYSTEM OPERATING MODE STATE MACHINE*/
        switch (en_Mode)
        {
            case Mode_Normal:
                /*get current temp from app data*/
                CurTemp_getter(&u8_CurrentTemp);
                if(FIRST_SEV_SEG == SevSeg)
                {
                    /*display 1st 7-seg*/
                    SevSeg_Display((u8_CurrentTemp/10), Seg_3);
                    SevSeg = SECOND_SEV_SEG;
                }
                else if(SECOND_SEV_SEG == SevSeg)
                {
                    /*display 2nd 7-seg*/
                    SevSeg_Display((u8_CurrentTemp%10), Seg_4);
                    SevSeg = FIRST_SEV_SEG;
                }
                
                /*in case pb pressed change status to setting mode*/
                if ((UP_PRESS == SetTempPB) || (DOWN_PRESS == SetTempPB))
                {
                    en_Mode = Mode_Setting;
                    SetTemp_getter(&u8_SetTemp);
                    
                    u8_SevSegBlinkingCounter = SEV_SEG_BLINKING_COUNTER_INITIAL_VALUE;
                }
                break;
            
            case Mode_Setting:
                u8_SevSegBlinkingCounter++;
                /*7-seg blinking*/
                if(20 > u8_SevSegBlinkingCounter)
                {
                    if(FIRST_SEV_SEG == SevSeg)
                    {
                        /*display 1st 7-seg*/
                        SevSeg_Display((u8_SetTemp/10), Seg_3);
                        SevSeg = SECOND_SEV_SEG;
                    }   
                    else if(SECOND_SEV_SEG == SevSeg)
                    {
                        /*display 2nd 7-seg*/
                        SevSeg_Display((u8_SetTemp%10), Seg_4);
                        SevSeg = FIRST_SEV_SEG;
                    } 
                }
                else if (40 > u8_SevSegBlinkingCounter)
                {
                    /*turn off both 7-seg*/
                    SevSeg_Off(Seg_3);
                    SevSeg_Off(Seg_4);
                }
                else
                {
                    u8_SevSegBlinkingCounter = SEV_SEG_BLINKING_COUNTER_INITIAL_VALUE;
                }
                
                /*change set temp according to the pushed pb*/
                if (UP_PRESS == SetTempPB)
                {
                    if (MAX_SET_TEMP > u8_SetTemp)
                    {
                        /*increase set temp*/
                        u8_SetTemp += SET_TEMP_CHANGE_FACTOR;
                    }
                    u8_SwitchModeCounter = SWITCH_MODE_COUNTER_INITAL_VALUE;
                }
                else if (DOWN_PRESS == SetTempPB)
                {
                    if (MIN_SET_TEMP < u8_SetTemp)
                    {
                        /*decrease set temp*/
                        u8_SetTemp -= SET_TEMP_CHANGE_FACTOR;
                    }
                    u8_SwitchModeCounter = SWITCH_MODE_COUNTER_INITAL_VALUE;
                }
                else if (NO_PRESS == SetTempPB)
                {
                    u8_SwitchModeCounter++;
                    /*in case no press for 5 sec turn mode to normal*/
                    if(100 == u8_SwitchModeCounter)
                    {
                        en_Mode = Mode_Normal;
                        SetTemp_Setter(u8_SetTemp);
                        u8_SwitchModeCounter = SWITCH_MODE_COUNTER_INITAL_VALUE;
                    }
                }
                break;
            
            default:
                break;
        }
    }
    
}
