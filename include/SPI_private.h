/********************************************************/ 
/* Author : Nourhan Mansour                             */
/* Date   : 26/9/2020                                   */
/* Version: 1.0                                         */
/* File   : SPI_private.h                               */
/********************************************************/ 
#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

#define SPI_CH_MAX       3
/********** Registers definition **********/
typedef struct 
{
    volatile u32 CR1; 
    volatile u32 CR2;
    volatile u32 SR;
    volatile u32 DR;
    volatile u32 CRCPR;
    volatile u32 RXCRCR;
    volatile u32 TXCRCR;
    volatile u32 I2SCFGR;
    volatile u32 I2SPR;
}t_SPI;

volatile t_SPI * SPIx [SPI_CH_MAX] = {
    0x40013000,
    0x40003800,
    0x40013C00          // Not used in stm32 (BluePill board)
};


/******** Registers Bits *************/

#define SPI_CR1_CPHA        0
#define SPI_CR1_CPOL        1
#define SPI_CR1_MSTR        2
#define SPI_CR1_BR0         3
#define SPI_CR1_BR1         4
#define SPI_CR1_BR2         5
#define SPI_CR1_SPE         6
#define SPI_CR1_LSBF        7
#define SPI_CR1_SSI         8
#define SPI_CR1_SSM         9
#define SPI_CR1_RXONLY      10
#define SPI_CR1_DFF         11
#define SPI_CR1_CRCNXT      12
#define SPI_CR1_CRCEN       13
#define SPI_CR1_BIDIOE      14
#define SPI_CR1_BIDIMODE    15

/***************************************/

#define SPI_CR2_RXDMAEN     0
#define SPI_CR2_TXDMAEN     1
#define SPI_CR2_SSOE        2
#define SPI_CR2_ERRIE       5
#define SPI_CR2_RXNEIE      6
#define SPI_CR2_TXEIE       7

/***************************************/

#define SPI_SR_RXNE         0
#define SPI_SR_TXE          1
#define SPI_SR_CHSIDE       2
#define SPI_SR_UDR          3
#define SPI_SR_CRCERR       4
#define SPI_SR_MODF         5
#define SPI_SR_OVR          6
#define SPI_SR_BSY          7


#endif // End Of File
