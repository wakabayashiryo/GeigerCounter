/*
 * File:   main.c
 * Author: evaota
 *
 * Created on 2017/02/25, 21:19
 */

#include "main.h"

uint8_t CPS_Data[3];
uint8_t CPS_PreData[3];

int8_t main(void)
{
    Basic_Init();
    
    LED_BLUE(LED_OFF);      //Clear Bule LED    
    
    LCD_Init();
    xdev_out(LCD_Put);
    
    Timer1_Init();
    Timer1_Start();
    
    mTouch_Init();
    
    Timer4_Init();
    
    Buzer_Init();
    
    DAC_Initialize();

    while(1)
    {
        LCD_CursorPosition(0,0);
        if((CPS_PreData[0]-CPS_Data[0])>150)
            xprintf("CPS1");
        if((CPS_PreData[1]-CPS_Data[1])>150)
            xprintf("CPS2");
        if((CPS_PreData[2]-CPS_Data[2])>150)
            xprintf("CPS3");
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
    static uint16_t count = 0;
    if(Timer4_Handler())
    {
        CPSx_Read();
        count++;
        if(count>1000)
        {
            count = 0;
            LATA6 ^= 1;
        }
    }
    
    Timer1_Handler();
    I2C_CommonInterrupt();
}
