/*******************************************************/ 
/* Author : Nourhan Mansour                            */
/* Date   : 3/10/2020                                  */
/* Version: 2.0                                        */
/* File   : TFT_CONFIG.h                               */
/*******************************************************/ 
#ifndef     TFT_CONFIG_H
#define     TFT_CONFIG_H

/* Data Command pin wiring */
#define TFT_DC_PORT     	PORTA
#define TFT_DC_PIN      	PIN0

/* Reset pin wiring */
#define TFT_RST_PORT    	PORTA
#define TFT_RST_PIN      	PIN1

/* Chip Select / Slave Select pin */
#define TFT_CS_PORT			PORTA
#define TFT_CS_PIN			PIN3

#define TFT_X_SIZE          130
#define TFT_Y_SIZE          130

#endif //End Of File
