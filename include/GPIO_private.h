/******************************************************/ 
/* Author: Nourhan Mansour                            */
/* Date  : 24/8/2020                                  */
/* Vesion: 3.0                                        */
/* File  : GPIO_private.h                             */
/******************************************************/ 
#ifndef     GPIO_PRIVATE_H
#define     GPIO_PRIVATE_H


/*************** Registers definitions ****************/

/*********************** PORT A **********************/
#define GPIOA_CRL           *((volatile u32 *) 0x40010800)
#define GPIOA_CRH           *((volatile u32 *) 0x40010804)
#define GPIOA_IDR           *((volatile u32 *) 0x40010808)
#define GPIOA_ODR           *((volatile u32 *) 0x4001080C)
#define GPIOA_BSRR          *((volatile u32 *) 0x40010810)
#define GPIOA_BRR           *((volatile u32 *) 0x40010814)
#define GPIOA_LCKR          *((volatile u32 *) 0x40010818)

/*********************** PORT B **********************/
#define GPIOB_CRL           *((volatile u32 *) 0x40010C00)
#define GPIOB_CRH           *((volatile u32 *) 0x40010C04)
#define GPIOB_IDR           *((volatile u32 *) 0x40010C08)
#define GPIOB_ODR           *((volatile u32 *) 0x40010C0C)
#define GPIOB_BSRR          *((volatile u32 *) 0x40010C10)
#define GPIOB_BRR           *((volatile u32 *) 0x40010C14)
#define GPIOB_LCKR          *((volatile u32 *) 0x40010C18)

/*********************** PORT C **********************/
#define GPIOC_CRL           *((volatile u32 *) 0x40011000)
#define GPIOC_CRH           *((volatile u32 *) 0x40011004)
#define GPIOC_IDR           *((volatile u32 *) 0x40011008)
#define GPIOC_ODR           *((volatile u32 *) 0x4001100C)
#define GPIOC_BSRR          *((volatile u32 *) 0x40011010)
#define GPIOC_BRR           *((volatile u32 *) 0x40011014)
#define GPIOC_LCKR          *((volatile u32 *) 0x40011018)

/****************** AFIO Registers *******************/
typedef struct 
{
   volatile u32 EVCR;
   volatile u32 MAPR;
   volatile u32 EXTICR[4];

}t_AFIO;

typedef enum {
    PORTA_MAP = 0b0000,
    PORTB_MAP ,
    PORTC_MAP ,
}t_PORT_MAPPING;


#define AFIO_BASE_ADDRESS       0x40010000
#define AFIO                    ((t_AFIO *) AFIO_BASE_ADDRESS)
#endif  // End Of File
