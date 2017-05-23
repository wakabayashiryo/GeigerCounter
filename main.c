/*
 * File:   main.c
 * Author: evaota
 *
 * Created on 2017/02/25, 21:19
 */


#include <xc.h>
#include "main.h"
#include <stdio.h>

int8_t main(void)
{
    Basic_Init();

    LCD_Init();
    Timer1_Init();
    Timer4_Init();
  
    Timer1_StartCount();
    
    while(1)
    {
        LCD_CursorHome();
        printf("%ul %d", Timer1_GetCPM(),Timer1_GetCountSum());
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

void interrupt Handler(void)
{
    if(Timer4_CheckFlag())
        Timer1_Count200us();
    
    if(Timer1_DetectAssignCount())
        LATA6 = !LATA6;
}
