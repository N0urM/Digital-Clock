/********************************************************/ 
/* Author : Nourhan Mansour                             */
/* Date   : 3/10/2020                                   */
/* Version: 2.0                                         */
/* File   : TFT_program.c                               */
/********************************************************/ 

// 1- include Libraries 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// 2- include interface file of needed lower layers
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "SPI_interface.h"

// 3- include driver files
#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"


void TFT_voidInit(void)
{

    /* Init sequence: */

    /** Rest Pulse **/
    GPIO_voidSetPortPinValue(TFT_RST_PORT , TFT_RST_PIN , 1);
    STK_voidSetBusyWait(100);
    GPIO_voidSetPortPinValue(TFT_RST_PORT , TFT_RST_PIN , 0);
    STK_voidSetBusyWait(2);
    GPIO_voidSetPortPinValue(TFT_RST_PORT , TFT_RST_PIN , 1);
    STK_voidSetBusyWait(100);
    GPIO_voidSetPortPinValue(TFT_RST_PORT , TFT_RST_PIN , 0);
    STK_voidSetBusyWait(100);
    GPIO_voidSetPortPinValue(TFT_RST_PORT , TFT_RST_PIN , 1);
    STK_voidSetBusyWait(120000);
    /*************************/

    // Sleep out CMD
    TFT_voidWriteCommand(TFT_CMD_SLPOUT);
    // Wait for 150 ms (Halt)
    STK_voidSetBusyWait(150000);
    // Color MODE CMD
    TFT_voidWriteCommand(TFT_CMD_COLORMODE);
    // Color Mode: RGB 565 = 0x05 
    TFT_voidWriteData(0x05);
    // DISP ON CMD
    TFT_voidWriteCommand(TFT_CMD_DISPON);
}   

void TFT_voidDisplayImage(const u16 * cpy_ptr_img)
{
    u16 local_counter=0;
    const u16 totalSize = TFT_X_SIZE * TFT_Y_SIZE;
    
    TFT_voidSet_X_Y (0 , TFT_X_SIZE , 0 , TFT_Y_SIZE);
    
    for(local_counter = 0 ; local_counter < totalSize ; local_counter++)
    {
    	TFT_voidWriteWord(cpy_ptr_img[local_counter]);
    }

}

void TFT_voidFillColor (u16 copy_FillColor){
    u16 local_counter=0;
    const u16 totalSize = TFT_X_SIZE * TFT_Y_SIZE;
    
    TFT_voidSet_X_Y (0 , TFT_X_SIZE , 0 , TFT_Y_SIZE);
    
    for(local_counter = 0 ; local_counter < totalSize ; local_counter++)
    {
    	TFT_voidWriteWord(copy_FillColor);
    }
}

void TFT_voidDrawRect (u8 x1 , u8 x2 , u8 y1 , u8 y2 , u16 copy_FillColor)
{
    if (x1 < x2 && y1 < y2 && x2 <= TFT_X_SIZE && y2 <= TFT_Y_SIZE)
    {
        u16 local_counter=0;
        const u16 totalSize = (x2 - x1) * (y2 - y1);

        TFT_voidSet_X_Y (x1 , x2 , y1 , y2);

        for(local_counter = 0 ; local_counter < totalSize ; local_counter++)
        {
            TFT_voidWriteWord(copy_FillColor);
        }
    }
}

void TFT_voidPrintText (u8 x , u8 y , u8 * text , u16 Textcolor , u16 BackgroudColor ){
	while (*text != '\0'){

		TFT_voidDrawLetter(x , y , *text++ , Textcolor , BackgroudColor );
		x+= ( MAX_CHAR_WIDTH +1 );
		if (x> TFT_X_SIZE){
			x = 0;
			y+= (MAX_CHAR_HEIGHT * 2);
		}
	}
}

/*******************************************************************/
/*                   Private Functions                             */
/*******************************************************************/

static void TFT_voidWriteCommand(u8 cpy_Command){
    
    // LOW for command
    GPIO_voidSetPortPinValue (TFT_DC_PORT , TFT_DC_PIN , 0);
    // CS low
    GPIO_voidSetPortPinValue (TFT_CS_PORT , TFT_CS_PIN , 0);
    // Send Command
    (void)SPI_u8SendRecieveSync(cpy_Command);
    // CS HIGH
    GPIO_voidSetPortPinValue (TFT_CS_PORT , TFT_CS_PIN , 1);


}

static void TFT_voidWriteData(u8 cpy_Data){
    //High for Data
    GPIO_voidSetPortPinValue (TFT_DC_PORT , TFT_DC_PIN , 1);   
    // CS low
    GPIO_voidSetPortPinValue (TFT_CS_PORT , TFT_CS_PIN , 0);
    // Send data 
    (void)SPI_u8SendRecieveSync(cpy_Data);
    // CS HIGH
    GPIO_voidSetPortPinValue (TFT_CS_PORT , TFT_CS_PIN , 1);
}


static void TFT_voidSet_X_Y(u8 x1 , u8 x2 , u8 y1 , u8 y2){
        // Set x Address
    TFT_voidWriteCommand(0x2A);
    // Start: 2Bytes
    TFT_voidWriteData(0);
    TFT_voidWriteData(x1);
    
    // End: 2 bytes
    TFT_voidWriteData(0);
    TFT_voidWriteData(x2);

    // Set Y address
    TFT_voidWriteCommand(0x2B);
    // Start: 2Bytes
    TFT_voidWriteData(0);
    TFT_voidWriteData(y1);

    // End: 2 bytes
    TFT_voidWriteData(0);
    TFT_voidWriteData(y2);

    // RAM WRITE
    TFT_voidWriteCommand(0x2C);
}


static void TFT_voidWriteWord(u16 copy_Word)
{
    u8 highByte = copy_Word>> 8;
    u8 lowByte =  copy_Word & 0x00ff;
    TFT_voidWriteData(highByte);
    TFT_voidWriteData(lowByte);
}


static void TFT_voidDrawPixel (u8 x , u8 y , u16 Color)
{
	TFT_voidSet_X_Y(x , x+1 , y , y+1);
	TFT_voidWriteWord(Color);
}

void TFT_voidDrawLetter (u8 x1 ,u8 y1 , u16 Letter , u16 copy_FillColor  , u16 copy_BackColor )
{
    if ( x1 <= TFT_X_SIZE && y1 <= TFT_Y_SIZE)
    {
        u16 i = 0 , j = 0 ;
        Letter = Letter - STARTING_CHAR;
        for(i = 0 ; i < MAX_CHAR_WIDTH ; i++)
        {
            for (j = 0 ; j< MAX_CHAR_HEIGHT ; j++)
            {
                if ( GET_BIT (CharArray [Letter] [i]  , j ) & 0x1)
                {
                	TFT_voidDrawPixel(x1+i , y1+j , copy_FillColor);
                }
                else
                {
                	TFT_voidDrawPixel(x1+i , y1+j , copy_BackColor);
                }
            }
        }
    }
}
