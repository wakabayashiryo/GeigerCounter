/*
 * File:   main.c
 * Author: evaota
 *
 * Created on 2017/02/25, 21:19
 */


#include <xc.h>
#include "main.h"
#include "eeprom.h"

int8_t main(void)
{
    Basic_Init();

    uint8_t sample[10]={
        0,1,2,3,4,5,6,7,8,9
    };
    uint8_t readdat[10];
    
    while(1)
    {
        EEPROM_MultiWrite(sample,10,0);
        EEPROM_MultiRead(readdat,10,0);
    }
    return EXIT_SUCCESS;
}

int8_t Basic_Init(void)
{
    OSCCON = 0xF3;      //PLL ON: 
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