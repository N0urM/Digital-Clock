/********************************************************/ 
/* Author : Nourhan Mansour                             */
/* Date   : 26/9/2020                                   */
/* Version: 1.0                                         */
/* File   : SPI_config.h                                */
/********************************************************/ 
#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

/* SPI1 = 0
   SPI2 = 1
*/
#define SPI_CH              0       

/* Master Slave Selection */
#define MASTER_MODE         1
#define SLAVE_MODE          0
#define SPI_MODE            MASTER_MODE

/* Clk Polarity & phase  for either master or slave*/
/*
    Logic 0 when Idle = 0
    Logic 1 when Idle = 1
*/
#define SPI_CLK_POL         1
/*
    First data Transition in first clock  = 0
    First data Transition in second clock = 1 
*/
#define SPI_CLK_PHASE       1

/* LSB FIRST = 1 
   MSB FIRST = 0
*/ 
#define LSB_FIRST           0

/* 8  Bit Data Frame  = 0 
   16 Bit Data Frame  = 1
*/
#define DFF_MODE            0


#if SPI_MODE == MASTER_MODE 
        
    #define SPIBAUD_RATE_CLK_DIV2           0
    #define SPIBAUD_RATE_CLK_DIV4           1
    #define SPIBAUD_RATE_CLK_DIV8           2
    #define SPIBAUD_RATE_CLK_DIV16          3
    #define SPIBAUD_RATE_CLK_DIV32          4
    #define SPIBAUD_RATE_CLK_DIV64          5
    #define SPIBAUD_RATE_CLK_DIV128         6
    #define SPIBAUD_RATE_CLK_DIV256         7

    #define SPI_BAUD_RATE_SET               SPIBAUD_RATE_CLK_DIV2
#endif


#endif // End Of File
