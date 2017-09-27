/*
 * File:   LCD1602.c
 * Author: evaota
 *
 * Created on 2017/02/25, 23:08
 */
#include "LCD1602.h"

/*----------------------------------------------------------
 * Feature:
 *  This function is sending data from MCU to LCD.
 * Worning:
 *  User is not able to use.
----------------------------------------------------------*/
static void LCD1602_WriteData(int8_t point)
{
    __delay_us(80);
    LCD1602_BUS((point>>4)&0x0F);   //Higher 4Bit
    LCD1602_STROBO();
    LCD1602_BUS(point&0x0F);        //Lower 4Bit
    LCD1602_STROBO();     
}

/*----------------------------------------------------------
 * Feature:
 *  Intialize LCD module in 4Bit mode
----------------------------------------------------------*/
void LCD1602_Init(LCD1602_Init_PORTTypedef LCD1602_Init_PORT)
{
    LCD1602_Init_PORT();

    LCD1602_RS = 0;
    LCD1602_E = 0;

    __delay_ms(30);
    LCD1602_BUS(0x03);
    LCD1602_STROBO();
    __delay_ms(5);
    LCD1602_STROBO();
    __delay_us(400);
    LCD1602_STROBO();
    __delay_us(400);
    LCD1602_BUS(0x02);          // Fuction Set Mode = 4bit	
    LCD1602_STROBO();

    LCD1602_WriteData(0x28);    // Mode=4bit / Line=2 /Font=5x8dot	
    LCD1602_WriteData(0x0c);    // Display=on / Cursol=off / Blink of Cursol=off
    LCD1602_DisplayClear();  
    LCD1602_WriteData(0x06);    // Cursor=incriment /Display_shift=off	
}

/*----------------------------------------------------------
 * Feature:
 *  Display a word on LCD
----------------------------------------------------------*/
void LCD1602_Put(int8_t word)
{
    LCD1602_RS = 1;
    LCD1602_WriteData(word);	
}

/*----------------------------------------------------------
 * Feature:
 *  PIC standard I/O API
----------------------------------------------------------*/
void putch(char c)
{
    LCD1602_RS = 1;
    LCD1602_WriteData(c);
}
/*----------------------------------------------------------
 * Feature:
 *  Clear all words on LCD
----------------------------------------------------------*/
void LCD1602_DisplayClear(void)
{
    LCD1602_RS  = 0;				
    LCD1602_WriteData(0x01);    //clear command
    __delay_ms(2);          //excuted time
}

/*----------------------------------------------------------
 * Feature:
 *  Move cursor to first point.
----------------------------------------------------------*/
void LCD1602_CursorHome(void)
{
    LCD1602_RS = 0;			 					
    LCD1602_WriteData(0x02);
    __delay_ms(2);          //excuted time
}

/*---------------------------------------------------------
 * Feature:
 *  Cursor is set arbitary point.
----------------------------------------------------------*/
void LCD1602_CursorPosition(uint8_t tx ,uint8_t ty)
{
    LCD1602_RS = 0; 					
    LCD1602_WriteData(0x80|tx|(0x40*ty));	// Address =0 		
    __delay_us(40);                     //excuted time					
} 

/*----------------------------------------------------------
 * Feature:
 *  Cursor is moved Left or Right.
----------------------------------------------------------*/
void LCD1602_CursorShift(uint8_t shift,uint8_t RL)
{
    uint8_t i;
    
    LCD1602_RS = 0;			

    for(i=0;i<shift;i++)
    {
        LCD1602_WriteData(0x10|((RL&0x01)<<2));
        __delay_us(40);                 //excuted time
    }
}

/*----------------------------------------------------------
 * Feature:
 *  Some words on LCD is moved right or left
----------------------------------------------------------*/
void LCD1602_DispShift(uint8_t shift,uint8_t RL)
{
    uint8_t i;
    
    LCD1602_RS = 0;			 					
    for(i=0;i<shift;i++)
    {
        LCD1602_WriteData(0x18|((RL&0x01)<<2));
    }
}
