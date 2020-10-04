/********************************************************/ 
/* Author : Nourhan Mansour                             */
/* Date   : 26/9/2020                                   */
/* Version: 1.0                                         */
/* File   : SPI_interface.h                             */
/********************************************************/ 
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void SPI_voidInit();

u8 SPI_u8SendRecieveSync(u8 data);

void SPI_voidSendRecieveAsync(u8 data , void (*callBack(u16)) );

void SPI_voidStop();

#endif // End Of File
