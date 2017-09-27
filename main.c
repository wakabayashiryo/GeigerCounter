/*
 * File:   main.c
 * Author: evaota
 *
 * Created on 2017/02/25, 21:19
 */

#include "main.h"


/*---Version Information---
 * 1.01:fixed to set PMT's Gain
 * 1.10:changed count parameter rised interrupt flag
 */

//TODO
//Optimize code and be sipmlify Never finish.
//Reduce Code size and wornings

__EEPROM_DATA(SERIAL_NO,0x00,0x00,0x00,0x00,0x00,0x00,0x00);

static void Basic_Init(void);
static void Buzzer_Init_Port(void);
static void mTouch_Init_Port(void);

int8_t main(void)
{
    static STATE_OF_MODE state_mode = STOPPING;
    static PMT_CONFIGURATION pmt_config;

    Basic_Init();
    
    LED_BLUE(LED_OFF);      //Clear Bule LED    
    
    Buzzer_Init(Buzzer_Init_Port,TMR2_PRESCALER16,0xFF);
    
    LCD1602_Init(NULL);
    
    Timer1_Init();
    Timer1_StopCount();
    
    static CPS_CHANNELCONFIG cps_config[3];
    cps_config[0].CPS_Channel = START_SYMBOL;
    cps_config[0].Threshould_Diff = START_SYMBOL_PARAM;
    cps_config[1].CPS_Channel = RESET_SYMBOL;
    cps_config[1].Threshould_Diff = RESET_SYMBOL_PARAM;
    cps_config[2].CPS_Channel = STOP_SYMBOL;
    cps_config[2].Threshould_Diff = STOP_SYMBOL_PARAM;
    mTouch_Init(mTouch_Init_Port,cps_config,3);
    
    Timer6_Init(TMR6_PRESCALER64,0x7D);
    
    DAC_Initialize();

    StartUp_Menu(&pmt_config);

    while(1)
    {
        switch(state_mode)
        {
            case COUNTING:
                if(mTouch_Check(STOP_SYMBOL))
                {
                    Timer1_StopCount();
                    LCD1602_DisplayClear();
                    state_mode = STOPPING;
                }
                break;
 
            case STOPPING:
                if(mTouch_Check(START_SYMBOL))
                {
                    Timer1_StartCount();
                    LCD1602_DisplayClear();
                    state_mode = COUNTING;
                }
                else if(mTouch_Check(RESET_SYMBOL))
                {
                    Timer1_ClearRecord();
                }
                else if(mTouch_Check(STOP_SYMBOL))
                {
                    Timer1_StopCount();
                    LCD1602_DisplayClear();
                    state_mode = RESULT;
                }
                break;
                
            case RESULT:
                if(mTouch_Check(START_SYMBOL))
                {
                    LCD1602_DisplayClear();
                    state_mode = SETTING;
                }
                else if(mTouch_Check(STOP_SYMBOL))
                {
                    LCD1602_DisplayClear();
                    state_mode = STOPPING;
                }
                else if(mTouch_Check(RESET_SYMBOL))
                {
                    LCD1602_DisplayClear();
                    state_mode = SHOW_CONFIG;
                }
                break;
                
            default:
                break;
        }
        
        switch(state_mode)
        {
            case COUNTING:
                LCD1602_CursorPosition(0,0);
                printf("  Countting...  ");
                LCD1602_CursorPosition(0,1);
                printf(" %7lu  %02d:%02d",Timer1_GetCountSum(),Timer1_GetMinute(),Timer1_GetSecond()); 
                break;
                
            case STOPPING:
                LCD1602_CursorPosition(0,0);
                printf(" Count Stopped ");
                LCD1602_CursorPosition(0,1);
                printf(" %7lu  %02d:%02d",Timer1_GetCountSum(),Timer1_GetMinute(),Timer1_GetSecond()); 
                break;
                
            case RESULT:
                LCD1602_CursorPosition(0,0);
                printf("%7lu %7lu",Timer1_GetCPS(),Timer1_GetCPM());
                LCD1602_CursorPosition(0,1);
                printf(" %7lu  %02d:%02d",Timer1_GetCountSum(),Timer1_GetMinute(),Timer1_GetSecond()); 
                break;
                
            case SETTING:
                Ssetting_PMT_Config(&pmt_config);
                state_mode = RESULT;
                break;
                
            case SHOW_CONFIG:
                Show_PMT_Config(&pmt_config);
                state_mode = RESULT;
                break;
            default:
                break;
        }
    }
    return EXIT_SUCCESS;
}

static void Basic_Init(void)
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
    
}

void interrupt Handler(void)
{
    if(Timer1_DetectAssignCount())
        LED_BLUE(LED_TOG);

    if(Timer6_CheckFlag())//every 1ms
    {
        mTouch_Count1ms();
        Timer1_Count1ms();

        mTouch_Scan();
        Buzzer_Count1ms();
    }
    I2C_Interrupt();
}

static void I2C2_Init_Port(void)
{
    TRISB |= ((1<<2)|(1<<5));
    ANSELB &= ~((1<<2)|(1<<5));
}

static void Buzzer_Init_Port(void)
{
    TRISA &= ~(0x01<<7);    //RA7 is output
    ANSELA &= ~(0x01<<7);   //one is digital mode
    APFCON0 |= (0x01<<3);   //Alternate of CCP2 is RA7
}

static void mTouch_Init_Port(void)
{
    TRISA |= (0x07);
    ANSELA |= (0x07);
}