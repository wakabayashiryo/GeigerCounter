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
    I2C_Init(I2C2_MODULE,0x56,I2C_MODE_SLAVE,I2C_SPEED_STANDARD);
    LCD_Init();
    xdev_out(LCD_Put);

    uint8_t testdata[4]={
      19,98,05,06  
    };
    uint8_t resultdata[4];
    
    while(1)
    {  
        resultdata[0] = I2C_Transmit(I2C2_MODULE,0x56,testdata,4);
        I2C_Receive(I2C2_MODULE,0x56,resultdata,4);
        LCD_CursorPosition(0,0);
        xprintf("%d %d %d %d",resultdata[0],resultdata[1],resultdata[2],resultdata[3]);   
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