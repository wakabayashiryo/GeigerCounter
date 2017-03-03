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
<<<<<<< HEAD

    Timer1_Init();
//    Timer1_Start();

    LCD_Init();
    xdev_out(LCD_Put);

    uint16_t j = 0;
    uint16_t i=500;

    uint8_t buff[10];
    while(1)
    {
        uint16_t p = 0;
//        Timer1_Write(i);
//        LCD_CursorPosition(0,0);
//        xprintf("TMR1H,TMR1L,i");
//        LCD_CursorPosition(0,1);
//        xprintf("%3U %3U ,%d %d",TMR1H,TMR1L,i++,j++);
        LCD_CursorPosition(0,1);
        sprintf(buff,"%d %d",i++,j++);
        while(buff[p])
        {
            LCD_Put(buff[p]);
            p++;
        }
    }
    
=======
    LCD_Init();
    xdev_out(LCD_Put);
  
    while(1)
    {  
        LCD_CursorPosition(0,0);
        xprintf("Hellow World");
    }    
>>>>>>> master
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

void interrupt Handler(void)
{
    Timer1_Handler();
}