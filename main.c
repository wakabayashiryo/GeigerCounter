/*
 * File:   main.c
 * Author: evaota
 *
 * Created on 2017/02/25, 21:19
 */

#include "main.h"

//TODO
//add start menu

const uint16_t DAC_DataTable[];
static STATE_OF_MODE state_mode = STOPPING;

int8_t main(void)
{
    Basic_Init();
    
    LED_BLUE(LED_OFF);      //Clear Bule LED    
    
    Buzzer_Init();
    
    LCD_Init();
    
    Timer1_Init();
    Timer1_StopCount();
    
    mTouch_Init();
    
    Timer6_Init();
    
    DAC_Initialize();
    DAC_WriteVoltage(DAC_DataTable[0]);    
    DAC_WriteVoltage(DAC_DataTable[6]);
    
    while(1)
    {
        LCD_CursorHome();
        if(mTouch_Check(START_SYMBOL)&&(state_mode==STOPPING))
        {
            Timer1_StartCount();
            LCD_DisplayClear();
            state_mode = COUNTING;
        }
        else if(mTouch_Check(STOP_SYMBOL))
        {
            Timer1_StopCount();
            LCD_DisplayClear();
            if(state_mode==STOPPING)
                state_mode = RESULT;
            else
                state_mode = STOPPING;
        }
        else if(mTouch_Check(RESET_SYMBOL)&&(state_mode!=COUNTING))
        {
            Timer1_ClearRecord();
        }

        switch(state_mode)
        {
            case COUNTING:
                LCD_CursorPosition(0,0);
                printf("  Countting...  ");
                LCD_CursorPosition(0,1);
                printf(" %7lu  %02d:%02d",Timer1_GetCountSum(),Timer1_GetMinute(),Timer1_GetSecond()); 
                break;
                
            case STOPPING:
                LCD_CursorPosition(0,0);
                printf(" Count Stopped ");
                LCD_CursorPosition(0,1);
                printf(" %7lu  %02d:%02d",Timer1_GetCountSum(),Timer1_GetMinute(),Timer1_GetSecond()); 
                break;
                
            case RESULT:
                LCD_CursorPosition(0,0);
                printf("%7lu",Timer1_GetCPS());
                printf("%7lu",Timer1_GetCPM());
                LCD_CursorPosition(0,1);
                printf(" %7lu  %02d:%02d",Timer1_GetCountSum(),Timer1_GetMinute(),Timer1_GetSecond()); 
                break;
        }
    
    }
    return EXIT_SUCCESS;
}

int8_t Basic_Init(void)
{
    OSCCON = 0xF0;      //PLL ON: 
                        //internal Oscilltor is 32MHz
                        //clock source is internal one.
    
    TRISA = 0x00;       //All PORTA is output 
    ANSELA = 0x00;      //All PORTA  is analog 
   
    TRISB = 0x00;       //All PORTB pin is output
    ANSELB = 0x00;      //All PORTB pin is digital
    /*alternate pin fuction control*/
    APFCON0 = 0x00;     //no alteration
    APFCON1 = 0x00;     //no alteration
    
    PORTA = 0x00;       //clear
    PORTB = 0x00;       //clear
    
    return EXIT_SUCCESS;
}

void interrupt Handler(void)
{
    if(Timer1_DetectAssignCount())
        LED_BLUE(LED_TOG);

    if(Timer6_CheckFlag())//every 1ms
    {
        mTouch_IntervalDecrement();
        Timer1_Count1ms();

        mTouch_Read();
        Buzzer_Count1ms();
    }
    I2C_CommonInterrupt();
}