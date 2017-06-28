#include "Timer1.h"

static Counters cnts;
static TimeCounter tcnt;

void Timer1_Init(void)
{
    TRISB |= (1<<6);       //RB6 is input it is used Timer1
    ANSELB &= ~(1<<6);      //RB6 pin is digital
    WPUB |= (1<<6);        //RB6's PullUP is enabled 
    
    T1CON |= (0x01<<2);   //external clock is not synchronization
    T1CON &= ~(0x01<<3);   //LP oscilltor is disable
    T1CON |= (0x00<<4);    //Timer clock prescalor is 1
    T1CON |= (0x02<<6);    //Timer clock sourc is external
        
    T1GCON = 0x00;         //Not use Trigger

    Timer1_Reset();
    
    TMR1IF = 0;
    TMR1IE = 1;
    PEIE = 1;
    GIE = 1;
    
    TMR1ON = 0;
}

/***Constat Accuracy Measurement***/

void Timer1_StartCount(void)
{
    Timer1_ClearRecord();
    TMR1ON = 1;
}

void Timer1_StopCount(void)
{   
    TMR1ON = 0;
}

void Timer1_ClearRecord(void)
{
    cnts.SigmaDeltaCount= 0;
    tcnt.Delta_t = 0;
    tcnt.Second_t = 0;
    tcnt.Minute_t = 0;
}

uint32_t Timer1_GetCountSum(void)
{
    return cnts.SigmaDeltaCount;
}

uint32_t Timer1_GetCPS(void)
{
    return (uint32_t)((cnts.SigmaDeltaCount * 1000UL)/tcnt.Delta_t);
}

uint32_t Timer1_GetCPM(void)
{
    return (uint32_t)(Timer1_GetCPS()*60);
}

uint8_t Timer1_GetSecond(void)
{
    return tcnt.Second_t;
}

uint8_t Timer1_GetMinute(void)
{
    return tcnt.Minute_t;
}

/***Put this function in interrupt function every 200us ***/
void Timer1_Count1ms(void)
{
    if(TMR1ON==1)
    {
        tcnt.Delta_t++;
        tcnt.RenewalRersult++;

        if(tcnt.RenewalRersult>1000)//Renewal Rersult Average of CPM every 1 second
        {
            tcnt.Second_t++;

            if((56<tcnt.Second_t)&&(tcnt.Second_t<60))
            {
                Buzzer_MiliSecond(300);
            }
            else if(tcnt.Second_t>59)
            {
                tcnt.Second_t = 0;
                tcnt.Minute_t++;

                Buzzer_MiliSecond(600);
            }

            tcnt.RenewalRersult = 0;
        }
    }

}

uint8_t Timer1_DetectAssignCount(void)//put into interrupt function
{
    if(TMR1IF&&TMR1IE)//Interrupt flag is rised by detected every 10 counts
    {
        cnts.SigmaDeltaCount+= DELTA_COUNT;//Count sum detected pulses
               
        Timer1_Reset();
        
        TMR1IF = 0;
        
        return 1;
    }
    return 0;
}