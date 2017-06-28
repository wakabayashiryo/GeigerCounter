#include "mTouch.h"

uint8_t CPS_Data[3];
uint8_t CPS_PreData[3];
uint8_t mTouch_Interval[3];

static const uint8_t sense_parameter[] = {
    START_SYMBOL_PARAM,
    RESET_SYMBOL_PARAM,
    STOP_SYMBOL_PARAM 
};

static void mTouch_PortInit(void)
{
    TRISA |= (0x07);
    ANSELA |= (0x07);
}

void mTouch_Init(void)
{
    mTouch_PortInit();
    
    /*Timer0 Configration*/
    OPTION_REG |= (0x0<<0);     //Prescaler Rate is 2
    OPTION_REG |= (0x1<<3);     //Clock not pass prescaler
    OPTION_REG |= (0x1<<5);     //Clock source is CPS
    TMR0 = 0x00;
    
    /*CPS Configration*/
    CPSCON0 |= (0x01<<0);       //Timer0 clock source is the capacitive sensing oscillator
    CPSCON0 |= (0x03<<2);       //SPS range is 18uA
    CPS_DISABLE();
    CPS_CHANNEL(0x00);
}

void mTouch_Read(void)
{
    static uint8_t channel=0;
    
    CPS_PreData[channel] = CPS_Data[channel];

    CPS_DISABLE();
    CPS_Data[channel] = TMR0;
    TMR0 = 0x00;
    CPS_ENABLE();

    if(++channel>2)channel = 0;    
    CPS_CHANNEL(channel);
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
    if(2<chan)return 0;

    if(((CPS_PreData[chan]-CPS_Data[chan])>sense_parameter[chan])&&!mTouch_Interval[chan])
    {
        mTouch_Interval[chan] = 100;
        Buzzer_MiliSecond(100);
        return 1;
    }
    return 0;
}
