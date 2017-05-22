#include "Timer1.h"

static uint32_t SigmaCount,SigmaCPM,Num_of_Detect,AverageCPM;
static uint32_t timecount;
static uint16_t RenewalCPM;

void Timer1_Init(void)
{
    TRISB |= (1<<6);       //RA6 is input it is used Timer1
    ANSELB &= ~(1<<6);      //All PORTB pin is digital
    WPUB |= (1<<6);
    
    T1CON |= (0x01<<2);   //external clock is not synchronization
    T1CON &= ~(0x01<<3);   //LP oscilltor is disable
    T1CON |= (0x00<<4);    //Timer clock prescalor is 1
    T1CON |= (0x02<<6);    //Timer clock sourc is external
        
    T1GCON = 0x00;         //Not use Trigger

    Timer1_Write(0xFFFF - DETECT_NUM_OF_COUNT);
    
    TMR1IF = 0;
    TMR1IE = 1;
    PEIE = 1;
    GIE = 1;
}

/***Constat Accuracy Measurement***/
uint32_t Timer1_GetCountSum(void)
{
    return SigmaCount;
}

uint16_t Timer1_GetError(void)
{
    return (uint16_t)((sqrt(SigmaCount)/(float)SigmaCount)*10);
}

uint16_t Timer1_GetCPM(void)
{
    return AverageCPM;
}

void Timer1_Count200us(void)
{
    timecount++;
}

uint8_t Timer1_DetectAssignCount(void)//put into interrupt function
{    
    static uint16_t PreviousTimer1;
    if((timecount>50000)&&(TMR1==PreviousTimer1))//If Counter did not detect between 1count and 10 counts. Reset CPM
        SigmaCPM = 0;
    PreviousTimer1 = Timer1_Read();
    
    RenewalCPM++;
    if(RenewalCPM>5000)
    {
        RenewalCPM = 0;  
        AverageCPM = SigmaCPM/Num_of_Detect;
    }
    
    if(TMR1IF&&TMR1IE)
    {
        SigmaCount += DETECT_NUM_OF_COUNT;
        
        SigmaCPM += (uint16_t)((DETECT_NUM_OF_COUNT * 12000UL) / timecount);
        Num_of_Detect++;
        
        timecount = 0;
        Timer1_Write(0xFFFF-DETECT_NUM_OF_COUNT);
        TMR1IF = 0;
        return 1;
    }
    return 0;
}