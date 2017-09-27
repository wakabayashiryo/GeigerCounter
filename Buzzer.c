/*
 * File:   Buzzer.c
 * Author: evaota
 *
 * Created on 2017/02/27, 13:10
 */
#include "Buzzer.h"

static uint16_t count;

void Buzzer_Init(Buzzer_Init_PORTTypedef Buzzer_Init_PORT,TMR2_PRESCALER_VAL pre_val,uint8_t period)
{
    Buzzer_Init_PORT();
    
    T2CON |= (0x00<<3);     //output prescalor is 1
    T2CON |= ((uint8_t)pre_val<<0); //Set Clock Prescaler
    T2CON |= (0x01<<2);     //Timer2 is enabled
    
    TMR2 = 0x00;
    PR2 = period;                   //Set Period Register
    
    CCP2CON &= ~(0x03<<6);  //PWM output configuration is single
    CCP2CON |= (0x0C<<0);   //ECCP mode is PWM
    CCPTMRS &= ~(0x03<<2);  //CCP2 is applied clock from TMR2
    
    CCPR2L = 0x00;
}

void Buzzer_SetDuty(uint16_t duty)
{
    uint8_t CCP2CON_Pre = CCP2CON & ~(0x03<<4);
    CCPR2L = (duty>>2);
    CCP2CON = CCP2CON_Pre | ((duty&0x03)<<4);
}

void Buzzer_Sound_ms(uint16_t time)
{
    if(count==0)
        count = time;
}

void Buzzer_Count1ms(void)//Set Function Repeat for 1 mili second
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