/*
 * File:   Buzer.c
 * Author: evaota
 *
 * Created on 2017/02/27, 13:10
 */
#include "Buzer.h"

void Buzer_Init(void)
{
    TRISA &= ~(0x01<<7);    //RA7 is output
    ANSELA &= ~(0x01<<7);   //one is digital mode
    APFCON0 |= (0x01<<3);   //Alternate of CCP2 is RA7
    
    T2CON |= (0x00<<3);     //output prescalor is 1
    T2CON |= (0x01<<0);     //input clock which of prescalor is 1
    T2CON |= (0x01<<2);     //Timer2 is enabled
    
    TMR2 = 0x00;
    PR2 = BUZER_PR2;
    
    CCP2CON &= ~(0x03<<6);  //PWM output configuration is single
    CCP2CON |= (0x0C<<0);   //ECCP mpde is PWM
    CCPTMRS &= ~(0x03<<2);  //CCP2 is applied clock from TMR2
    
    CCPR2L = 0x00;
}

void Buzer_SetDuty(uint16_t duty)
{
    uint8_t CCP2CON_Pre = CCP2CON;
    CCPR2L = (duty>>2);
    CCP2CON = CCP2CON_Pre | ((duty&0x03)<<4);
}
