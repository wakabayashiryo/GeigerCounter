#include "User_Interface.h"

//uint16_t DAC_DataTable[];
uint8_t *H7826_Gain[];
uint8_t *H7826_01_Gain[];

static uint8_t Save_PMTConfig(PMT_CONFIGURATION *data)
{    
    return EEPROM_MultiWrite(data->Eeprom_table,NUM_OF_DATA,0);
}

static uint8_t Load_PMTConfing(PMT_CONFIGURATION *data)
{
    return EEPROM_MultiRead(data->Eeprom_table,NUM_OF_DATA,0);
}

void StartUp_Menu(PMT_CONFIGURATION *data)
{
    Load_PMTConfing(data);
    DAC_WriteVoltage(409+41*data->GainElements);

    LCD1602_CursorHome();
    printf(" Geiger Counter ");
    LCD1602_CursorPosition(0,1);
    printf("    with PIC    ");
    __delay_ms(2000);

    LCD1602_DisplayClear();

    LCD1602_CursorHome();
    printf("SotWare ver%s",SOFTWARE_VER);
    LCD1602_CursorPosition(0,1);
    printf("   Ser.No.%0003d   ",data->SerialNum);
    __delay_ms(2000);    

    LCD1602_DisplayClear();

    LCD1602_CursorHome();
    printf("Created By");
    LCD1602_CursorPosition(0,1);
    printf("  Ryo Wakabayshi");
    __delay_ms(2000);

    LCD1602_DisplayClear();    
}

void Ssetting_PMT_Config(PMT_CONFIGURATION *data)
{
    LCD1602_CursorHome();
    printf("   PMT Device   ");
    
    while(!mTouch_Check(START_SYMBOL))
    {
        if(mTouch_Check(RESET_SYMBOL)&&(data->DeviceNum==0))
            data->DeviceNum = 1;
        else if(mTouch_Check(STOP_SYMBOL)&&(data->DeviceNum==1))
            data->DeviceNum = 0;
        
        LCD1602_CursorPosition(0,1);
        if(data->DeviceNum==0)
            printf("<--  H7826   -->");
        else if(data->DeviceNum==1)
            printf("<-- H7826_01 -->");
    }

    LCD1602_CursorHome();
    printf("  Set PMT Gain  ");
    
    while(!mTouch_Check(START_SYMBOL))
    {
        if(mTouch_Check(RESET_SYMBOL)&&(data->GainElements<11))
            data->GainElements++;
        else if(mTouch_Check(STOP_SYMBOL)&&(0<data->GainElements))
            data->GainElements--;
        
        LCD1602_CursorPosition(0,1);
        if(data->DeviceNum==0)
            printf("<-- %8s -->",H7826_Gain[data->GainElements]);
        else if(data->DeviceNum==1)
            printf("<-- %8s -->",H7826_01_Gain[data->GainElements]);
    }
    
    DAC_WriteVoltage(409+41*data->GainElements);
    
    LCD1602_DisplayClear();

    Save_PMTConfig(data);
}

void Show_PMT_Config(PMT_CONFIGURATION *data)
{
    while(!mTouch_Check(START_SYMBOL))
    {
        LCD1602_CursorHome();
        printf("SotWare ver%s",SOFTWARE_VER);
        LCD1602_CursorPosition(0,1);
        printf("   Ser.No.%0003d   ",data->SerialNum);
    }
    while(!mTouch_Check(START_SYMBOL))
    {
        LCD1602_CursorHome();
        if(data->DeviceNum==0)
            printf("Deveice:H7826   ");
        else if(data->DeviceNum==1)
            printf("Deveice:H7826_01");
        LCD1602_CursorPosition(0,1);
        if(data->DeviceNum==0)
            printf(" Gain: %8s ",H7826_Gain[data->GainElements]);
        else if(data->DeviceNum==1)
            printf(" Gain: %8s ",H7826_01_Gain[data->GainElements]);
    }
    LCD1602_DisplayClear();
}
