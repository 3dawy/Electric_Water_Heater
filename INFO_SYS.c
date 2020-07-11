#include "INFO_SYS.h"
#include "7-seg.h"
#include "LED.h"
#include "APP_DATA.h"



void InfoSys_Init (void)
{
    SevSeg_Init(Seg_3);
    SevSeg_Init(Seg_4);
    LED_Init(B7);
}
void InfoSys_Update (void)
{
    uint8_t u8_Status,
            u8_Operation,
            u8_DisStatus;
    
    SysStatus_getter(u8_Status);
    
    switch (u8_Status)
    {
        case Sys_On:
            switch (u8_Operation)
            {
                case OP_Cooling:
                    break;
                   
                case OP_Heating:
                    break;
                    
                case OP_Neutral:
                    break;
                    
                default:
                    break;
            }
            
            switch (u8_DisStatus)
            {
                case Dis_CurrentTemp:
                    break;
                    
                case Dis_SetTemp:
                    break;
                    
                default:
                    break;
            }
            break;
         
        case Sys_Off:
            break;

        default:
            break;
    }

}
