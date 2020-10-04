/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 24/8/2020                                   */
/* Vesion: 3.0                                         */
/* File  : GPIO_program.c                              */
/*******************************************************/ 

// 1- include Libraries 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// 2- include interface file of needed lower layers

// 3- include driver files
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"


void GPIO_voidInitPortPinDirection(t_PORT cpy_port , t_PIN cpy_pin  ,t_MODE mode){
    switch (cpy_port)
    {
    case PORTA:
        
        if (cpy_pin < 8){
            GPIOA_CRL &= ~ ( (0b1111)<< ( cpy_pin * 4 ) );      // Clear configuration bits
            GPIOA_CRL |= (mode << ( cpy_pin * 4 ) );            // Set configuration
        }else {
            GPIOA_CRH &= ~ ( (0b1111)<< ( (cpy_pin-8) * 4 ) );  // Clear configuration bits
            GPIOA_CRH |= (mode << ( (cpy_pin-8) * 4 ) );        // Set configuration    
        }
        break;
    case PORTB:
    
        
        if (cpy_pin < 8){
            GPIOB_CRL &= ~ ( (0b1111)<< ( cpy_pin * 4 ) );      // Clear configuration bits
            GPIOB_CRL |= (mode << ( cpy_pin * 4 ) );            // Set configuration
        }else {
            GPIOB_CRH &= ~ ( (0b1111)<< ( (cpy_pin-8) * 4 ) );  // Clear configuration bits
            GPIOB_CRH |= (mode << ( (cpy_pin-8) * 4 ) );        // Set configuration    
        }
        break;
    case PORTC:
        
        if (cpy_pin < 8){
            GPIOC_CRL &= ~ ( (0b1111)<< ( cpy_pin * 4 ) );      // Clear configuration bits
            GPIOC_CRL |= (mode << ( cpy_pin * 4 ) );            // Set configuration
        }else {
            GPIOC_CRH &= ~ ( (0b1111)<< ( (cpy_pin-8) * 4 ) );  // Clear configuration bits
            GPIOC_CRH |= (mode << ( (cpy_pin-8) * 4 ) );        // Set configuration    
        }
        
        break;
    default:
        /*Shouldn't be here 
            Retun error
        */
        break;
    }    
}

void GPIO_voidInitPortDirection (t_PORT cpy_port , t_MODE mode){
	u8 pins_num = 0 ;
	switch (cpy_port)
    {
    case PORTA:

        GPIOA_CRL = 0;                                          // Clear configuration bits
        GPIOA_CRH = 0;                                          // Clear configuration bits
        pins_num =  0;
        /*  Initialize all port pins to the selected mode*/
        for(pins_num = 0 ; pins_num < 8; pins_num ++){          
             GPIOA_CRL |= (mode << ( pins_num * 4 ) );      
        }
        for(pins_num = 0 ; pins_num < 8; pins_num ++){
             GPIOA_CRH |= (mode << ( pins_num * 4 ) );
        }
        
        break;

    case PORTB:

        GPIOB_CRL = 0;
        GPIOB_CRH = 0;
        pins_num = 0 ;
        /*  Initialize all port pins to the selected mode*/
        for(pins_num = 0 ; pins_num < 8; pins_num ++){
             GPIOB_CRL |= (mode << ( pins_num * 4 ) );
        }
        for(pins_num = 0 ; pins_num < 8; pins_num ++){
             GPIOB_CRH |= (mode << ( pins_num * 4 ) );
        }
    break;
    
    case PORTC:
        
        GPIOC_CRL = 0;
        GPIOC_CRH = 0;
        pins_num = 0 ;
        /*  Initialize all port pins to the selected mode*/
        for(pins_num = 0 ; pins_num < 8; pins_num ++){
             GPIOC_CRL |= (mode << ( pins_num * 4 ) );
        }
        for(pins_num = 0 ; pins_num < 8; pins_num ++){
             GPIOC_CRH |= (mode << ( pins_num * 4 ) );
        }
        break;
    default:
        break;
    }

}
void GPIO_voidSetPortPinValue(t_PORT cpy_port , t_PIN cpy_pin , u8 cpy_value){
    switch (cpy_port)
    {
    case PORTA:
        if(cpy_value == 0){
            SET_BIT(GPIOA_BRR , cpy_pin);                   // Reset Pin
        }else { 
            SET_BIT(GPIOA_BSRR , cpy_pin);                  // Set Pin
        }
        break;
    case PORTB:
        if(cpy_value == 0){
           SET_BIT(GPIOB_BRR  , cpy_pin);                    // Reset pin
        }else { 
           SET_BIT(GPIOB_BSRR , cpy_pin);                    // Set pin
        }
        break;
    case PORTC:
        if(cpy_value == 0){
           SET_BIT(GPIOC_BRR  , cpy_pin);                   // Reset Pin
        }else {
           SET_BIT(GPIOC_BSRR , cpy_pin);                   // Set Pin
        }
        break;    
    default:
        break;
    }
}

void GPIO_voidSetPortValue(t_PORT cpy_port , u16 cpy_value){
    /* Set the value of the output data register */
    switch (cpy_port)
    {
    case PORTA:
        GPIOA_ODR = cpy_value;
        break;
    case PORTB:
        GPIOB_ODR = cpy_value;
        break;
    case PORTC:
        GPIOC_ODR = cpy_value;
        break;
    default:
        break;
    }
}


u8 GPIO_u8GetPortPinValue(t_PORT cpy_port , t_PIN cpy_pin){
    /* Get the pin value from the input data register */
    u8 retValue = 0;
    switch (cpy_port)
    {
    case PORTA:
        retValue = GET_BIT(GPIOA_IDR , cpy_pin);
        break;
    case PORTB:
        retValue = GET_BIT(GPIOB_IDR , cpy_pin);
        break;
    case PORTC:
        retValue = GET_BIT(GPIOC_IDR , cpy_pin);
        break;    
    default:
        break;
    }
    return retValue;
}

u16 GPIO_u16GetPortValue(t_PORT cpy_port){
    /* Get the value of the input data register */
     u16 retValue = 0;
    switch (cpy_port)
    {
    case PORTA:
        retValue = (GPIOA_IDR);
        break;
    case PORTB:
        retValue = (GPIOB_IDR);
        break;
    case PORTC:
        retValue = (GPIOC_IDR);
        break;    
    default:
        break;
    }
    return retValue;
}

void GPIO_voidSetPullType (t_PORT cpy_port , t_PIN cpy_pin , u8 pull_type){
    if (pull_type == 1){
        switch (cpy_port)
        {
        case PORTA:
            SET_BIT(GPIOA_BSRR , cpy_pin);                  // Activate internal pull up
            break;
        case PORTB:
            SET_BIT(GPIOB_BSRR , cpy_pin);                  // Activate internal pull up
            break;
        case PORTC:
            SET_BIT(GPIOC_BSRR , cpy_pin);                  // Activate internal pull up
            break;
        default:
            break;
        }
        
    }
    else {       	
        switch (cpy_port)
        {
        case PORTA:
            SET_BIT(GPIOA_BRR , cpy_pin);                  // Activate internal pull down
            break;
        case PORTB:
            SET_BIT(GPIOB_BRR , cpy_pin);                  // Activate internal pull down
            break;
        case PORTC:
            SET_BIT(GPIOC_BRR , cpy_pin);                  // Activate internal pull down
            break;
        default:
            break;
        }   
    }
}

void GPIO_voidEnableLockOnPortPin(t_PORT port ,t_PIN pin){
	u32 tmp = 0x00010000;
	tmp |=  (1 << pin);

	switch (port)
    {
    case PORTA:
    	// Initiate Lock sequence
    	GPIOA_LCKR = tmp;
    	/* Reset LCKK bit */
    	GPIOA_LCKR =  (1 << pin);
    	/* Set LCKK bit */
    	GPIOA_LCKR = tmp;
    	/* Read LCKK bit*/
     	tmp = GPIOA_LCKR;
      	/* Read LCKK bit*/
       	tmp = GPIOA_LCKR;

    	break;
    case PORTB:
    	// Initiate Lock sequence
    	GPIOB_LCKR = tmp;
    	/* Reset LCKK bit */
    	GPIOB_LCKR =  (1 << pin);
    	/* Set LCKK bit */
    	GPIOB_LCKR = tmp;
    	/* Read LCKK bit*/
    	tmp = GPIOB_LCKR;
    	/* Read LCKK bit*/
    	tmp = GPIOB_LCKR;
        break;
    case PORTC:
    	// Initiate Lock sequence
    	GPIOC_LCKR = tmp;
    	/* Reset LCKK bit */
      	GPIOC_LCKR =  (1 << pin);
     	/* Set LCKK bit */
       	GPIOC_LCKR = tmp;
      	/* Read LCKK bit*/
       	tmp = GPIOC_LCKR;
       	/* Read LCKK bit*/
     	tmp = GPIOC_LCKR;
    	break;

    default:
        break;
    }
}

void GPIO_EnableAFOnPortPin(t_PORT cpy_port ,t_PIN cpy_pin , t_AF cpy_Alternative_function)
{
    u8 local_reg_idx  = cpy_pin / 4;            // Select register in the array
    u8 local_line_bit = (cpy_pin % 4) * 4;      // Select bits numbers
    u8 local_port_map = PORTA_MAP;
    switch (cpy_Alternative_function)
    {
    case EXTI:

        /* Select Mapping */
        
        switch (cpy_port)
        {
        case PORTA:
            local_port_map = PORTA_MAP;
            break;
        case PORTB:
            local_port_map = PORTB_MAP;
            break;
        case PORTC:
            local_port_map = PORTC_MAP;
            break;
        default:
            break;
        }
        /** Set new AF value **/
        AFIO->EXTICR[local_reg_idx] &= ~ ((0b1111) << local_line_bit);
        AFIO->EXTICR[local_reg_idx] |= local_port_map << local_line_bit;    
        break;
        
    default:
        break;
    }
    
}