#include "Timer1.h"

static uint32_t countsum;
static uint16_t count10us,resulttime;

void Timer1_Init(void)
{
    TRISB |= (1<<6);       //RA6 is input it is used Timer1
    ANSELB &= ~(1<<6);      //All PORTB pin is digital
    
    T1CON |= (0x01<<2);   //external clock is not synchronization
    T1CON &= ~(0x01<<3);   //LP oscilltor is disable
    T1CON |= (0x00<<4);    //Timer clock prescalor is 1
    T1CON |= (0x02<<6);    //Timer clock sourc is external
        
    T1GCON = 0x00;         //Not use Trigger
    
    TMR1 = 0xFFFF-DETECT_NUM_OF_COUNT;//Clear Timer1
    count10us = 0x0000;
    
    TMR1IF = 0;
    TMR1IE = 1;
    PEIE = 1;
    GIE = 1;
}

/***Constat Accuracy Measurement***/

inline uint32_t Timer1_SumRead(void)
{
    return countsum;
}

inline uint16_t Timer1_ResultRead(void)
{
    return resulttime;
}

inline void Timer1_Count10us(void)
{
    count10us++;
}

uint8_t Timer1_DetectAssignCount(void)//put into interrupt function
{
    if(TMR1IF&&TMR1IE)
    {
        countsum += 100;
        resulttime = count10us;
        count10us = 0;
        TMR1 = 0xFFFF-DETECT_NUM_OF_COUNT;
        TMR1IF = 0;
        return 1;
    }
    return 0;
}