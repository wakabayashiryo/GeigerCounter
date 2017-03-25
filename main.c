/*
 * File:   main.c
 * Author: evaota
 *
 * Created on 2017/02/25, 21:19
 */

#include "main.h"
<<<<<<< HEAD
#include <stdio.h>
=======
#include "eeprom.h"
>>>>>>> eeprom

int8_t main(void)
{
<<<<<<< HEAD
    Basic_Init();
<<<<<<< HEAD

    Timer1_Init();
    Timer1_Start();

    LCD_Init();
    DAC_Initialize();
    xdev_out(LCD_Put);
<<<<<<< HEAD

    while(1)
    {
        LCD_CursorPosition(0,0);
        xprintf("%U ",Timer1_Read());
    }
    
=======
    uint8_t sample[5]={
        20,17,3,3,20
    };
    uint8_t readdat[5];
    LCD_Init();
    xdev_out(LCD_Put);
    
    while(1)
    {
//        EEPROM_MultiWrite(sample,5,0);
        LCD_CursorPosition(0,0);
        EEPROM_MultiRead(readdat,5,0);
        for(uint8_t i = 0;i<5;i++)
            xprintf("%d ",readdat[i]);
    }
>>>>>>> eeprom
=======
    Basic_Init();    
    Buzer_Init();
    Buzer_Sound();

    LCD_Init();
    xdev_out(LCD_Put);
    while(1)
    {  
        
=======
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
>>>>>>> ExternalDAC
    }    
>>>>>>> buzer
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

<<<<<<< HEAD
void interrupt Handler(void)
{
    Timer1_Handler();
=======

void interrupt hand(void)
{
    I2C_CommonInterrupt();
>>>>>>> ExternalDAC
}