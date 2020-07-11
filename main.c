#include <xc.h>
#include "stdutils.h"
#include <pic16f877a.h>
#include "CONTROL.h"
#include "HEATING_SYSTEM.h"
#include "OPERATING_MODE.h"




void Timer1Delay(uint16_t Delay_ms);       //Delay Function

void main (void)
{
    Control_Init();
    
    HeatingSystem_Init();
    
    OperatingMode_Init();
   
    while(1)
    {
        Control_Update();
        
        HeatingSystem_Update();
        
        OperatingMode_Update();

        Timer1Delay(50);
    }
}

void Timer1Delay(uint16_t Delay_ms){     //1ms delay
    int counter = 0;
    T1CON=0x20;             //Timer-1 16-bit mode Prescaler 1:4
//    INTCONbits.GIE=1;
//    INTCONbits.PEIE=1;
//    PIE1bits.TMR1IE=1;
    
    //Runing loop for 100 times produces 1 second 10ms x 100 = 1 second
    for(counter=0; counter<Delay_ms; counter++)
    {         
        TMR1H=0xFE;             //Count Hight Byte
        TMR1L=0x19;             //Count Low Byte
        T1CONbits.TMR1ON=1;         //Run timer
        while(PIR1bits.TMR1IF==0);     //Wait for flag to over flow
        T1CONbits.TMR1ON=0;              //Switch off timer
        PIR1bits.TMR1IF=0;             //Clear Interrupt
    }
}