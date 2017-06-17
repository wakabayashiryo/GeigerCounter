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
    Timer1_Reset();
    cnts.SigmaDeltaCount= 0;
    cnts.SigmaCPM = 0;
    cnts.Num_of_Detect = 0;
    tcnt.Delta_t = 0;
}

uint32_t Timer1_GetCountSum(void)
{
    return cnts.SigmaDeltaCount;
}

uint16_t Timer1_GetCPM(void)
{
    return cnts.AverageCPM;
}

/***Put this function in interrupt function every 200us ***/
void Timer1_Count200us(void)
{
    tcnt.Delta_t++;
}

uint8_t Timer1_DetectAssignCount(void)//put into interrupt function
{
    static uint16_t PreviousTimer1;
    
//    if((tcnt.Delta_t>500000)&&(Timer1_Read()==PreviousTimer1))//If Counter did not detect between 1count and 10 counts. Reset CPM
//        cnts.SigmaCPM = 0;
//    PreviousTimer1 = Timer1_Read();
    
    tcnt.RenewalCPM++;
    if((tcnt.RenewalCPM>5000)&&cnts.Num_of_Detect)//Renewal Rersult Average of CPM every 1 second
    {
        tcnt.RenewalCPM = 0;  
        cnts.AverageCPM = (uint16_t)(cnts.SigmaCPM/cnts.Num_of_Detect);
    }
    
    if(TMR1IF&&TMR1IE)//Interrupt flag is rised by detected every 10 counts
    {
        cnts.SigmaDeltaCount+= DELTA_COUNT;
        
        cnts.SigmaCPM += (uint32_t)((DELTA_COUNT * 30000UL) / tcnt.Delta_t);
        cnts.Num_of_Detect++;//Number of Detected 10 counts
        
        tcnt.Delta_t = 0;
        Timer1_Write(0xFFFF-DELTA_COUNT);
        TMR1IF = 0;
        return 1;
    }
    return 0;
}