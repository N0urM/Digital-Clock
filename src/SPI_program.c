/********************************************************/ 
/* Author : Nourhan Mansour                             */
/* Date   : 26/9/2020                                   */
/* Version: 1.0                                         */
/* File   : SPI_program.c                               */
/********************************************************/ 

// 1- include Libraries 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// 2- include interface file of needed lower layers

// 3- include driver files
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"

void SPI_voidInit(){

//	SPIx[0] -> CR1 = 0x0347;

    // CLEAR CFG
    SPIx[SPI_CH] -> CR1 = 0;
    SPIx[SPI_CH] -> CR2 = 0;

    #if SPI_MODE == MASTER_MODE
        // Select the BR[2:0] bits to define the serial clock baud rate
        SPIx[SPI_CH] -> CR1 |= ( SPI_BAUD_RATE_SET << SPI_CR1_BR0 );
        // Set MSTR
        SET_BIT (SPIx[SPI_CH] -> CR1  , SPI_CR1_MSTR);
        // Enable SW slave managment
        SET_BIT(SPIx[SPI_CH] -> CR1 , SPI_CR1_SSI);
        SET_BIT(SPIx[SPI_CH] -> CR1 , SPI_CR1_SSM);
    #elif  SPI_MODE == SLAVE MODE
       // Clear the MSTR bit
        SET_BIT (SPIx[SPI_CH] -> CR1  , SPI_CR1_MSTR);
    #endif


    // define 8-bit or 16-bit data frame format
    #if DFF_MODE == 0
        CLR_BIT (SPIx[SPI_CH] -> CR1 , SPI_CR1_DFF);    // 8-Bit data Selected
    #else
        SET_BIT (SPIx[SPI_CH] -> CR1 , SPI_CR1_DFF);    // 16-Bit data Selected
    #endif

    // Select the CPOL and CPHA
    #if SPI_CLK_POL == 0
        CLR_BIT (SPIx[SPI_CH] -> CR1 , SPI_CR1_CPOL);       //idle = 0
    #else
        SET_BIT (SPIx[SPI_CH] -> CR1 , SPI_CR1_CPOL);       //idle = 1
    #endif

    #if SPI_CLK_PHASE == 0
        CLR_BIT (SPIx[SPI_CH] -> CR1 , SPI_CR1_CPHA);       // Data on First Clock
    #else
        SET_BIT (SPIx[SPI_CH] -> CR1 , SPI_CR1_CPHA);       // Data on Second Clock
    #endif

    // frame format (MSB-first or LSB-first)
    #if LSB_FIRST == 1
        SET_BIT (SPIx[SPI_CH] -> CR1 , SPI_CR1_LSBF);       // LSB sent first
    #else
        CLR_BIT (SPIx[SPI_CH] -> CR1 , SPI_CR1_LSBF);       // MSB sent first
    #endif
    // ENABLE SPI
    SET_BIT (SPIx[SPI_CH] -> CR1  , SPI_CR1_SPE);

}

u8 SPI_u8SendRecieveSync(u8 data)
{
    // Clear ss pin (Active low)
        /* To Be handles in main by the GPIO Driver */
    // Send Data 
    SPIx[SPI_CH] -> DR = data;
    // Wait for Busy Flag 
    while (GET_BIT(SPIx[SPI_CH] -> SR , SPI_SR_BSY ) == 1 );
    // set SS pin
        /* To be handled in main by GPIO DRIVER */
    // Return Recieved data 
    return ( SPIx[SPI_CH] -> DR & 0xFF );
}

void SPI_voidSendRecieveAsync(u8 data , void (*callBack(u16)) ){

    // TO DO
}
void SPI_voidStop(){
    // Wait RXNE = 1 
    while (GET_BIT(SPIx[SPI_CH] -> SR , SPI_SR_RXNE ) != 1);
    // Wait TXE  = 1
    while (GET_BIT(SPIx[SPI_CH] -> SR , SPI_SR_TXE ) != 1);
    // Wait BSY  = 0
    while (GET_BIT(SPIx[SPI_CH] -> SR , SPI_SR_BSY ) != 0);
    // Clear SPE
    CLR_BIT(SPIx[SPI_CH] -> CR1 , SPI_CR1_SPE ); 
}

