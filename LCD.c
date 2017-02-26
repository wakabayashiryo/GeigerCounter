/*
 * File:   LCD.c
 * Author: evaota
 *
 * Created on 2017/02/25, 23:08
 */
#include "LCD.h"

/*----------------------------------------------------------
----------------------------------------------------------*/
static void LCD_WriteData(int8_t point)
{
    __delay_us(80);
    LCD_BUS((point>>4)&0x0F);   //Higher 4Bit
    LCD_STROBO();
    LCD_BUS(point&0x0F);        //Lower 4Bit
    LCD_STROBO();    
}

/*----------------------------------------------------------
----------------------------------------------------------*/
void LCD_Init(void)
{
    LCD_RS = 0;
    LCD_E = 0;

    __delay_ms(30);
    LCD_BUS(0x03);
    LCD_STROBO();
    __delay_ms(5);
    LCD_STROBO();
    __delay_us(400);
    LCD_STROBO();
    __delay_us(400);
    LCD_BUS(0x02);          // Fuction Set Mode = 4bit	
    LCD_STROBO();

    LCD_WriteData(0x28);    // Mode=4bit / Line=2 /Font=5x7dot	
    LCD_WriteData(0x0c);    // Display=on / Cursol=on / Blink=on
    LCD_DisplayClear();  
    LCD_WriteData(0x06);    // Cursor=incriment /Display_shift=off	
    
}

/*----------------------------------------------------------
----------------------------------------------------------*/
void LCD_Put(int8_t word)
{
    LCD_RS = 1;
    LCD_WriteData(word);	
}

/*----------------------------------------------------------
----------------------------------------------------------*/
void LCD_DisplayClear(void)
{
    LCD_RS  = 0;				
    LCD_WriteData(0x01);    //clear command
    __delay_ms(2);
}

/*----------------------------------------------------------
----------------------------------------------------------*/
void LCD_CursorHome(void)
{
    LCD_RS = 0;			 					
    LCD_WriteData(0x02);
    __delay_ms(2);
}

/*----------------------------------------------------------
----------------------------------------------------------*/
void LCD_CursorPosition(uint8_t tx ,uint8_t ty)
{
    LCD_RS = 0; 					
    LCD_WriteData(0x80|tx|(0x40*ty));	// Address =0 		
    __delay_us(40);											
} 

/*----------------------------------------------------------
----------------------------------------------------------*/
void LCD_CursorShift(uint8_t shift,uint8_t RL)
{
    uint8_t i;
    
    LCD_RS = 0;			

    for(i=0;i<shift;i++)
    {
        LCD_WriteData(0x10|((RL&0x01)<<2));
        __delay_us(40);
    }
}

/*----------------------------------------------------------
----------------------------------------------------------*/
void LCD_DispShift(uint8_t shift,uint8_t RL)
{
    uint8_t i;
    
    LCD_RS = 0;			 					
    for(i=0;i<shift;i++)
    {
        LCD_WriteData(0x18|((RL&0x01)<<2));
        __delay_us(40);
    }
}
