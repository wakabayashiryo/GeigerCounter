/*
 * File:   main.c
 * Author: evaota
 *
 * Created on 2017/02/25, 21:19
 */


#include <xc.h>
#include "main.h"

int8_t main(void)
{
    Basic_Init();
    LCD_Init();
    DAC_Initialize();
    xdev_out(LCD_Put);
    LATA7 = 1;

    while(1)
    {  
        for(uint16_t voltage = 0;voltage<0x0FFF;voltage++)
        {
            DAC_WriteVoltage(voltage);
            __delay_us(100);
        }
        for(uint16_t voltage = 0;voltage<0x0FFF;voltage++)
        {
            DAC_WriteVoltage(0x0FFF-voltage);
            __delay_us(100);
        }
    }    
    return EXIT_SUCCESS;
}

int8_t Basic_Init(void)
{
    OSCCON = 0xF0;      //PLL ON: 
                        //internal Oscilltor is 32MHz
                        //clock source is internal one.
    
    TRISA = 0x07;       //RA0~2 is input it is used CPS  
    ANSELA = 0x07;      //RA0~2 is analog it is used CPS
   
    TRISB = 0x40;       //RA6 is input it is used Timer1
    ANSELB = 0x00;      //All PORTB pin is digital
    /*alternate pin fuction control*/
    APFCON0 = 0x08;     //RA7 use CCP2
    APFCON1 = 0x00;     //no alteration
    
    PORTA = 0x00;       //clear
    PORTB = 0x00;       //clear
    
    return EXIT_SUCCESS;
}


void interrupt hand(void)
{
    I2C_CommonInterrupt();
}