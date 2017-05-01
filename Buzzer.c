/*
 * File:   Buzer.c
 * Author: evaota
 *
 * Created on 2017/02/27, 13:10
 */
#include "Buzzer.h"

static uint16_t count;

void Buzzer_Init(void)
{
    TRISA &= ~(0x01<<7);    //RA7 is output
    ANSELA &= ~(0x01<<7);   //one is digital mode
    APFCON0 |= (0x01<<3);   //Alternate of CCP2 is RA7
    
    T2CON |= (0x00<<3);     //output prescalor is 1
    T2CON |= (0x02<<0);     //input clock which of prescalor is 1
    T2CON |= (0x01<<2);     //Timer2 is enabled
    
    TMR2 = 0x00;
    PR2 = BUZZER_PR2;
    
    CCP2CON &= ~(0x03<<6);  //PWM output configuration is single
    CCP2CON |= (0x0C<<0);   //ECCP mpde is PWM
    CCPTMRS &= ~(0x03<<2);  //CCP2 is applied clock from TMR2
    
    CCPR2L = 0x00;
}

void Buzzer_SetDuty(uint16_t duty)
{
    uint8_t CCP2CON_Pre = CCP2CON;
    CCPR2L = (duty>>2);
    CCP2CON = CCP2CON_Pre | ((duty&0x03)<<4);
}

void Buzzer_MiliSecond(uint16_t time)
{
    if(count==0)
        count = time;
}

void Buzzer_Handler(void)//Set Function Repeat for 1 mili second
{
    if(count>0)
    {
        count--;
        Buzzer_Sound();
    }
    else
    {
        Buzzer_Silent();
    }
}