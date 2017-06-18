/*
 * File:   main.c
 * Author: evaota
 *
 * Created on 2017/02/25, 21:19
 */

#include "main.h"

const uint16_t DAC_DataTable[];
uint8_t CPS_Data[3];
uint8_t CPS_PreData[3];
ModeConfig mode;
uint8_t mTouch_Interval[3];

void mTouch_IntervalDecrement(void);
uint8_t mTouch_Check(uint8_t chan);

int8_t main(void)
{
    Basic_Init();
    LED_BLUE(LED_OFF);      //Clear Bule LED    
    Buzzer_Init();
    LCD_Init();
    Timer1_Init();
    mTouch_Init();
//    Timer4_Init();
    Timer6_Init();
    DAC_Initialize();
    
    Timer1_StartCount();

    mode.ModeNum = 0;
    
    DAC_WriteVoltage(DAC_DataTable[6]);
    
    while(1)
    {
        if(mTouch_Check(2)&&(mode.ModeNum<NUM_OF_MODE-1))
            mode.ModeNum++;
        else if(mTouch_Check(1)&&(mode.ModeNum>0))
            mode.ModeNum--;
        
        LCD_CursorHome();
        switch(mode.ModeNum) 
        {
            case COUNT:
                printf("%7lu %7lu", Timer1_GetCPM(),Timer1_GetCountSum());
                LCD_CursorPosition(0,1);
                printf("%6lu",Timer1_GetCPS());
                printf("    %2d:%2d",Timer1_GetMinute(),Timer1_GetSecond());
                break;
            case SELECTFUNC:
                printf("SELECTFUNC");
            break;
            case ADJGAIN:
                printf("ADJGAIN");
            break;
            case PMTDEVICE:
                printf("PMTDEVICE");
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

void mTouch_IntervalDecrement(void)
{
    if(mTouch_Interval[0]>0)
        mTouch_Interval[0]--;
    if(mTouch_Interval[1]>0)
        mTouch_Interval[1]--;
    if(mTouch_Interval[2]>0)
        mTouch_Interval[2]--;
}

uint8_t mTouch_Check(uint8_t chan)
{
    if(chan>2)return 0;
    
    if(((CPS_PreData[chan]-CPS_Data[chan])>200)&&!mTouch_Interval[chan])
    {
        mTouch_Interval[chan] = 100;
        Buzzer_MiliSecond(100);
        return 1;
    }
    return 0;
}

