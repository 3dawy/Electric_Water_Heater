#include "HEATING_SYSTEM.h"
#include "gpio.h"
#include "LM35.h"
#include "LED.h"
#include "APP_DATA.h"




#define HEATER                                        PC_5
#define COOLER                                        PC_2
#define HEATING_ELEMENT_LED                           B5
#define CURRENT_TEMP_INITIAIL_VALUE                   0
#define LED_BLINKING_COUNTER_INITIAL_VALUE            0
#define CURRENT_TEMP_READING_COUNTER_INITIAL_VALUE    0
#define TEMP_READ_FACTOR                              2
#define READING_COUNTER_INIITAL_VALUE                 0

typedef enum 
{
    OP_Cooling, OP_Heating
}Operation_et;



void HeatingSystem_Init (void)
{
    GPIO_PinDirection(HEATER, OUTPUT); /*initialize heater pin*/
    
    GPIO_PinDirection(COOLER, OUTPUT); /*initialize cooler pin*/
    
    LED_Init(HEATING_ELEMENT_LED); /*initialize heating element led*/
    
    LM35_Init();
}
void HeatingSystem_Update (void)
{
    static Operation_et Operation;
    static uint8_t u8arr_CurrentTemp[10] = {CURRENT_TEMP_INITIAIL_VALUE};    
    static uint16_t u16_CurrentTemp = CURRENT_TEMP_INITIAIL_VALUE;    
    static uint8_t u8_ReadingCounter = READING_COUNTER_INIITAL_VALUE;    
    static uint8_t u8_SetTemp = 60;    
    static uint8_t u8_CurrentTempReadingCounter = CURRENT_TEMP_READING_COUNTER_INITIAL_VALUE;   
    static uint8_t u8_LedBlinkingCounter = LED_BLINKING_COUNTER_INITIAL_VALUE;
    SysStatus_et Status;
    uint8_t LoopCounter;
    
    /*get system on/off status*/
    SysStatus_getter(&Status); 
    
    if (Sys_Off == Status)
    {
        /*turn led off*/
        LED_Status(HEATING_ELEMENT_LED, LED_OFF); 
        /*turn the heater off*/
        GPIO_PinWrite(HEATER, LOW); 
        /*turn the cooler off*/
        GPIO_PinWrite(COOLER, LOW); 
        

        
        /*return counters to initial values*/
        u8_CurrentTempReadingCounter = CURRENT_TEMP_READING_COUNTER_INITIAL_VALUE; 
        
        u8_LedBlinkingCounter = LED_BLINKING_COUNTER_INITIAL_VALUE;
    }
    else if (Sys_On == Status)
    {
        /*counter used to get one read each 100 ms*/
        u8_CurrentTempReadingCounter ++; 
        
        if (TEMP_READ_FACTOR > u8_CurrentTempReadingCounter)
        {
            /*get actual temp*/
            LM35_Value(&u8arr_CurrentTemp[u8_ReadingCounter]); 
            /*store actual temp in the current temp array*/
            //u8arr_CurrentTemp[u8_ReadingCounter] = u8_CurrentTemp; 
            /*counter help in storing just last 10 reading*/
            u8_ReadingCounter++; 
            
            if(10 == u8_ReadingCounter)
            {
                /*return the counter to it's initial value*/
                u8_ReadingCounter = READING_COUNTER_INIITAL_VALUE; 
            }
            /*return current temp to it's initial value*/
            u16_CurrentTemp = CURRENT_TEMP_INITIAIL_VALUE; 
            
            /*loop used to calculate last 10 reading*/
            for(LoopCounter=0; LoopCounter<10; LoopCounter++)
            {
                u16_CurrentTemp = u16_CurrentTemp + u8arr_CurrentTemp[LoopCounter];
            }
            /*calculate the last 10 reading average*/
            u16_CurrentTemp = u16_CurrentTemp / 10;
            /*store the average current temp in app data*/
            CurTemp_Setter(u16_CurrentTemp);
        }
        else
        {
            /*return the current temp reading counter to it's initial value*/
            u8_CurrentTempReadingCounter = CURRENT_TEMP_READING_COUNTER_INITIAL_VALUE;
        }
        /*get set temp from app data*/
        SetTemp_getter(&u8_SetTemp);
        
        /*compare average current temp with set temp and take decision*/
        if(u16_CurrentTemp > (u8_SetTemp+5))
        {
			GPIO_PinWrite(HEATER, LOW); /*turn off heater*/
			GPIO_PinWrite(COOLER, HIGH); /*turn on the cooler*/
			LED_Status(HEATING_ELEMENT_LED, LED_ON); /*turn led on*/
        }
        else if (u16_CurrentTemp < (u8_SetTemp-5))
        {
            GPIO_PinWrite(HEATER, HIGH); /*turn on heater*/
			GPIO_PinWrite(COOLER, LOW); /*turn off cooler*/
			/*led blinking each 1 sec*/
			if(19 > u8_LedBlinkingCounter)
			{
			    u8_LedBlinkingCounter++;
			}
			else
			{
			    u8_LedBlinkingCounter = LED_BLINKING_COUNTER_INITIAL_VALUE;
			    
			    LED_Status(HEATING_ELEMENT_LED, LED_TOGGLE);
			}
        } 
    }
    

}
