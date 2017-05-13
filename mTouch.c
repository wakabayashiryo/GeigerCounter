#include "mTouch.h"

extern uint8_t CPS_Data[3];
extern uint8_t CPS_PreData[3];

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
    CPSCON0 |= (0x03<<2);       //SPS range is 0.1uA
    CPS_DISABLE();
    CPS_CHANNEL(0x00);
}

void CPSx_Read(void)
{
    static uint8_t channel=0;
    
    CPS_PreData[channel] = CPS_Data[channel];
    CPS_DISABLE();
    CPS_Data[channel] = TMR0;
    TMR0 = 0x00;
    CPS_ENABLE();

    if(channel++>2)channel = 0;    
    CPS_CHANNEL(channel);
    
}