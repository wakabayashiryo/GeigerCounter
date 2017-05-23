#include "Timer6.h"

void Timer6_Init(void)
{
    PR6 = 0x7D;         //Period Register is 125
    TMR6 = 0x00;        //Clear 
    T6CON |= (0x03<<0); //Clock Prescaler is 64
    T6CON |= (0x00<<3); //Post Scaler is 1
    T6CON |= (0x01<<2); //Timer6 is enabled
    
    TMR6IF = 0;
    TMR6IE = 1;
    PEIE = 1;
    GIE = 1;
}

uint8_t Timer6_CheckFlag(void)//10us
{
    if(TMR6IE&&TMR6IF)
    {
        TMR6IF = 0;
        return 1;
    }
    return 0;
}

