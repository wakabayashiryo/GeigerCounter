#include "I2C.h"

I2Cx_Configuration I2C1_Config;
I2Cx_Configuration I2C2_Config;

void I2C_Init(I2Cx_Module I2Cx,uint8_t address,I2Cx_Mode mode,I2Cx_Speed Speed)
{
    switch(I2Cx)
    {
        case I2C1_MODULE:
            I2C1_Setting(address,mode,Speed);
        break;

        case I2C2_MODULE:
            I2C2_Setting(address,mode,Speed);            
        break;
    }

    PEIE = 1;
    GIE = 1;
}

int8_t I2C_Transmit(I2Cx_Module I2Cx,uint8_t address,uint8_t *pData,uint8_t size)
{
    int8_t result;
    
     switch(I2Cx)
    {
        case I2C1_MODULE:
            result = I2C1_Transmit(address,pData,size);
        break;

        case I2C2_MODULE:
            result = I2C2_Transmit(address,pData,size);
        break;
    }
    return result;
}

int8_t I2C_Receive(I2Cx_Module I2Cx,uint8_t address,uint8_t *pData,uint8_t size)
{
    int8_t result;
    
    switch(I2Cx)
    {
        case I2C1_MODULE:
             result = I2C1_Receive(address,pData,size);
        break;

        case I2C2_MODULE:
             result = I2C2_Receive(address,pData,size);
        break;
    }
    
    return result;
}

void I2C_CommonInterrupt(void)
{
    I2C1_Interrupt();
    I2C2_Interrupt();
}