#include "PIC_Timer6.h"

void Timer6_Init(TMR6_PRESCALER_VAL pre_val,uint8_t period)
{
    PR6 = period;       //set Period Register
    TMR6 = 0x00;        //Clear
    T6CON |= ((uint8_t)pre_val<<0); //Set Clock Prescaler
    T6CON |= (0x00<<3); //Post Scaler is 1
    T6CON |= (0x01<<2); //Timer6 is enabled
    
    TMR6IF = 0;
    TMR6IE = 1;
    PEIE = 1;
    GIE = 1;
}

uint8_t Timer6_CheckFlag(void)
{
    if(TMR6IE&&TMR6IF)
    {
        TMR6IF = 0;
        return 1;
    }
    return 0;
}
