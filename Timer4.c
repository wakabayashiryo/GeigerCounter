#include "Timer4.h"

void Timer4_Init(void)
{
    PR4 = 0x7D;         //Period Register is 125
    TMR4 = 0x00;        //Clear 
    T4CON |= (0x03<<0); //Clock Prescaler is 64
    T4CON |= (0x00<<3); //Post Scaler is 1
    T4CON |= (0x01<<2); //Timer4 is enabled
    
    TMR4IF = 0;
    TMR4IE = 1;
    PEIE = 1;
    GIE = 1;
}

uint8_t Timer4_Handler(void)
{
    if(TMR4IE&&TMR4IF)
    {
        TMR4IF = 0;
        return 1;
    }
    return 0;
}

