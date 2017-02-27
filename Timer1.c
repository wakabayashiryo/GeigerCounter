#include "Timer1.h"

void Timer1_Init(void)
{
    TRISB |= (1<<6);       //RA6 is input it is used Timer1
    ANSELB |= (1<<6);      //All PORTB pin is digital
    
    T1CON |= (0x01<<2);   //external clock is not synchronization
    T1CON &= ~(0x01<<3);   //LP oscilltor is disable
    T1CON |= (0x00<<4);    //Timer clock prescalor is 0
    T1CON |= (0x02<<6);    //Timer clock sourc is external
        
    T1GCON = 0x00;         //Not use Trigger
    
    TMR1 = 0x00;           //Clear Timer1

    TMR1IE = 1;
    TMR1IF = 0;
    PEIE = 1;
    GIE = 1;
    
}

void Timer1_Clear(void)
{
    TMR1_STOP();
    TMR1 = 0x0000;
    TMR1_START();
}

uint16_t Timer1_Read(void)
{
    return TMR1;
}

void Timer1_Handler(void)
{
    if(TMR1IF&&TMR1IE)
    {
     ;   
    }
    TMR1IF = 0;
}