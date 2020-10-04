/*******************************************************/ 
/* Author : Nourhan Mansour                            */
/* Date   : 3/10/2020                                  */
/* Version: 2.0                                        */
/* File   : TFT_interface.h                            */
/*******************************************************/ 
#ifndef     TFT_INTERFACE_H
#define     TFT_INTERFACE_H

/* SPI Configurations: 
    CPOL = 1
    CPHA = 1
    MSB FIRST 
*/   

/******************* public functions *************************/

/**************************************************************
 * Function   : TFT_voidInit
 * Parameters : NONE
 * RETURN     : NONE
 * Description: initialize TFT Display
 * Notes      : This function doesn't handle SPI initialization
 * ***********************************************************/
void TFT_voidInit(void);


/**************************************************************
 * Function   : TFT_voidDisplayImage
 * Parameters : pointer to the image array
 * RETURN     : NONE
 * Description: Fit picture array to screen size
 * Notes      : Picture size must match display size
 * ***********************************************************/
void TFT_voidDisplayImage(const u16 * cpy_ptr_img);


/**************************************************************
 * Function   : TFT_voidFillColor
 * Parameters : copy_FillColor: Color in format R5GB5 
 * RETURN     : NONE
 * Description: Fill Display with solid color
 * Notes      : color is only 2 Bytes 
 * ***********************************************************/
void TFT_voidFillColor (u16 copy_FillColor);


/**************************************************************
 * Function   : TFT_voidDrawRect
 * Parameters : x1 & y1 : first point in the rect 
 *              x2 & y2 : last point in the rect
 *              copy_FillColor: color to fill the rect
 * RETURN     : NONE
 * Description: Fill a rect with solid color
 * Notes      : color is only 2 Bytes 
 * ***********************************************************/
void TFT_voidDrawRect (u8 x1 , u8 x2 , u8 y1 , u8 y2 , u16 copy_FillColor);

/**************************************************************
 * Function   : TFT_voidDrawRect
 * Parameters : x & y : start point of the text 
 *              text  : String to display
 *              textColor: color to fill the text
 *              BackgroudColor: BacgroudColor of the text
 * RETURN     : NONE
 * Description: Write text on Display
 * Notes      : color is only 2 Bytes 
 * ***********************************************************/
void TFT_voidPrintText (u8 x , u8 y , u8 * text , u16 Textcolor , u16 BackgroudColor );

#endif //End Of File
