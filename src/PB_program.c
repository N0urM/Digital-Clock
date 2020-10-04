/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 20/8/2020                                   */
/* Vesion: 1.0                                         */
/* File  : PB_program.c                                */
/*******************************************************/ 

// 1- include Libraries 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// 2- include interface file of needed lower layers
#include "GPIO_interface.h"
#include "RCC_interface.h"

// 3- include driver files
#include "PB_interface.h"
#include "PB_config.h"
#include "PB_private.h"


static tPB_Info pb_info[NUMBER_OF_PUSH_BUTTONS];

void PB_Init(t_PORT cpy_port ,t_PIN cpy_pin ,tPB pb, tPB_State initial_state)
{
    /* Enable Clock */
    switch (cpy_port)
	{
		case PORTA:
			RCC_voidEnableClock(t_APB2, RCC_APB2ENR_IOPAEN);
			break;
		case PORTB:
			RCC_voidEnableClock(t_APB2, RCC_APB2ENR_IOPBEN);
			break;
		case PORTC:
			RCC_voidEnableClock(t_APB2, RCC_APB2ENR_IOPCEN);
			break;
		default:
			break;
	}
    /* Initialize hw pins */
    GPIO_voidInitPortPinDirection(cpy_port , cpy_pin , INPUT_PULL_UP_DOWN);
    #if PB_PRESSED_VOLTAGE == 1
        GPIO_voidSetPullType(cpy_port , cpy_pin , 0);   //pull down
    #else
        GPIO_voidSetPullType(cpy_port , cpy_pin , 1);   //pull up
    #endif
    /* Initialize state */
    pb_info[pb].state = initial_state;
    pb_info[pb].port = cpy_port; 
    pb_info[pb].pin  = cpy_pin;
    /* Initialize samples */
    switch (initial_state)
    {
    case PB_RELEASED:
    case PB_PRE_RELEASED:
        pb_info[pb].samples[0] = PB_RELEASED_VOLTAGE;
        pb_info[pb].samples[1] = PB_RELEASED_VOLTAGE;
        break;
    case PB_PRESSED:
    case PB_PRE_PRESSED:
        pb_info[pb].samples[0] = PB_PRESSED_VOLTAGE;
        pb_info[pb].samples[1] = PB_PRESSED_VOLTAGE;
        break;
    }
}

void PB_Update(void)
{
    tPB current_button = PB_MINIUTE;
    for (current_button = 0; current_button <= NUMBER_OF_PUSH_BUTTONS ; current_button++)
    {
        /* Update samples */
        pb_info[current_button].samples[0] = pb_info[current_button].samples[1];

        pb_info[current_button].samples[1] = GPIO_u8GetPortPinValue(pb_info[current_button].port , pb_info[current_button].pin);

        /* Update state */
        switch(pb_info[current_button].state)
        {
        case PB_RELEASED:
            if((pb_info[current_button].samples[0] == PB_PRESSED_VOLTAGE) &&
               (pb_info[current_button].samples[1] == PB_PRESSED_VOLTAGE))
            {
                pb_info[current_button].state = PB_PRE_PRESSED;
            }
            break;
        case PB_PRE_PRESSED:
            if(pb_info[current_button].samples[1] == PB_PRESSED_VOLTAGE)
            {
                pb_info[current_button].state = PB_PRESSED;
            }
            break;
        case PB_PRESSED:
            if((pb_info[current_button].samples[0] == PB_RELEASED_VOLTAGE) &&
               (pb_info[current_button].samples[1] == PB_RELEASED_VOLTAGE))
            {
                pb_info[current_button].state = PB_PRE_RELEASED;
            }
            break;
        case PB_PRE_RELEASED:
            if(pb_info[current_button].samples[1] == PB_RELEASED_VOLTAGE)
            {
                pb_info[current_button].state = PB_RELEASED;
            }
            break;
            break;
        default:
            /* Should not be here */
            break;
        }

    }

}

tPB_State PB_GetState(tPB pb)
{
    tPB_State ret = PB_RELEASED;

    ret = pb_info[pb].state;

    return ret;
}
