/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 24/8/2020                                   */
/* Vesion: 3.0                                         */
/* File  : GPIO_interface.h                            */
/*******************************************************/ 
#ifndef     GPIO_INTERFACE_H
#define     GPIO_INTERFACE_H

/*********** Public data types *************/
typedef enum {
    PORTA,
    PORTB,
    PORTC,
}t_PORT;

typedef enum{
    PIN0 = 0,
    PIN1 = 1,
    PIN2 = 2,
    PIN3 = 3,
    PIN4 = 4,
    PIN5 = 5,
    PIN6 = 6,
    PIN7 = 7,
    PIN8 = 8,
    PIN9 = 9,
    PIN10 = 10,
    PIN11 = 11,
    PIN12 = 12,
    PIN13 = 13,
    PIN14 = 14,
    PIN15 = 15,
}t_PIN;

/******************* public constants *************************/
// GPIO MODES definitions
// Used with GPIO_voidInitPortPinDirection() function
typedef enum {
  INPUT_ANALOG    		   =0b0000,
  INPUT_FLOATING  		   =0b0100,
  INPUT_PULL_UP_DOWN  	   =0b1000,
    
  OUTPUT_PUSH_PULL_10MHZ   =0b0001,
  OUTPUT_OPEN_DRAIN_10MHZ  =0b0101,
  AF_PUSH_PULL_10MHZ       =0b1001,
  AF_OPEN_DRAIN_10MHZ      =0b1101,

  OUTPUT_PUSH_PULL_50MHZ   =0b0011,
  OUTPUT_OPEN_DRAIN_50MHZ  =0b0111,
  AF_PUSH_PULL_50MHZ       =0b1011,
  AF_OPEN_DRAIN_50MHZ      =0b1111,

  OUTPUT_PUSH_PULL_2MHZ    =0b0010,
  OUTPUT_OPEN_DRAIN_2MHZ   =0b0110,
  AF_PUSH_PULL_2MHZ        =0b1010,
  AF_OPEN_DRAIN_2MHZ       =0b1110,
}t_MODE;


typedef enum{
    EXTI,
}t_AF;
/******************* public functions *************************/

/*
    Function Name: GPIO_voidInitPortPinDirection
    Description  : initializa a GPIO pin direction and mode
    Parameters   :  
        port: PORTA,PORTB,PORTC
        pin : 0-15
        mode: input/output selection 
    No return
*/
void GPIO_voidInitPortPinDirection(t_PORT cpy_port , t_PIN cpy_pin  ,t_MODE mode);


/*
    Function Name: GPIO_voidInitPortDirection
    Description  : initialize a GPIO port direction and mode
    Parameters   :  
        port: PORTA,PORTB,PORTC
        mode: input/output selection
    No return

*/
void GPIO_voidInitPortDirection (t_PORT cpy_port , t_MODE mode);

/*
    Function Name: GPIO_voidSetPortPinValue
    Description  : set a GPIO pin value to 1 or 0
    Parameters   :  
        port   : PORTA,PORTB,PORTC
        pin    : 0-15
        value  : 1 / 0
    No return
*/
void GPIO_voidSetPortPinValue(t_PORT cpy_port , t_PIN cpy_pin , u8 cpy_value);


/*
    Function Name: GPIO_voidSetPortValue
    Description  : set a GPIO port value 0 - 0XFF
    Parameters   :  
        port   : PORTA, PORTB, PORTC
        value  : 0 ~ 0xFF
    No return
*/
void GPIO_voidSetPortValue(t_PORT cpy_port , u16 cpy_value);

/*
    Function Name: GPIO_voidSetPullType
    Description  : Used with input pull up down pins
    Parameters   :  
        port   : PORTA, PORTB, PORTC
        pin    : 0 ~ 15
        pull_type : 0: pull down 
                    1: pull up
    No return

*/
void GPIO_voidSetPullType (t_PORT cpy_port , t_PIN cpy_pin , u8 pull_type);

/*
    Function Name: GPIO_u8GetPortPinValue
    Description  : Get a GPIO pin value 1 or 0
    Parameters   :  
        port   : PORTA,PORTB,PORTC
        pin    : 0-15
    Return  :  pin value 0 or 1
*/
u8 GPIO_u8GetPortPinValue(t_PORT cpy_port , t_PIN cpy_pin);

/*
    Function Name: GPIO_u8GetPortValue
    Description  : Get a GPIO port value  0 ~ 0xFF
    Parameters   :  
                port   : PORTA,PORTB,PORTC
    Return  :  port value 
*/
u16 GPIO_u16GetPortValue(t_PORT cpy_port);

/*
    Function Name: GPIO_voidLockPortPin
    Description  : Using this function after enabling LOCL on PORTx 
                in the Config file will result in a freeze in selceted pin
    Parameters   :  
                port   : PORTA,PORTB,PORTC
                pin    : 0~15    
    Return  : No Return  

*/
void GPIO_voidEnableLockOnPortPin(t_PORT cpy_port ,t_PIN cpy_pin);

void GPIO_EnableAFOnPortPin(t_PORT cpy_port ,t_PIN cpy_pin , t_AF acpy_Alternative_function);

/***********************************************************/

#endif  // End Of File
