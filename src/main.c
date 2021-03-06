#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "SPI_interface.h"

#include "PB_interface.h"
#include "TFT_interface.h"
#include "DigitalClock.h"


void main(void) {

	/* Enable Clock */
	RCC_voidInitSystemClock();
	RCC_voidEnableClock(t_APB2, RCC_APB2ENR_IOPAEN);
	RCC_voidEnableClock(t_APB2, RCC_APB2ENR_SPI1EN);

	/** Init pinsout **/
	GPIO_voidInitPortPinDirection(PORTA, PIN1, OUTPUT_PUSH_PULL_10MHZ);	// RESET PIN
	GPIO_voidInitPortPinDirection(PORTA, PIN0, OUTPUT_PUSH_PULL_10MHZ);	// Data Command PIN
	GPIO_voidInitPortPinDirection(PORTA, PIN3, OUTPUT_PUSH_PULL_10MHZ);	// Chip Select  PIN
	GPIO_voidInitPortPinDirection(PORTA, PIN5, AF_PUSH_PULL_10MHZ);	// CLK PIN
	GPIO_voidInitPortPinDirection(PORTA, PIN6, INPUT_FLOATING);		// MISO PIN
	GPIO_voidInitPortPinDirection(PORTA, PIN7, AF_PUSH_PULL_10MHZ);	// MOSI PIN

	PB_Init(PORTB , PIN0 , PB_MINIUTE , PB_RELEASED);
	PB_Init(PORTB , PIN1 , PB_HOUR    , PB_RELEASED);
	/* Init Peripherals */
	STK_voidInit();
	SPI_voidInit();
	TFT_voidInit();
	TFT_voidFillColor(0);
	DigitalClockinit();
	STK_voidSetIntervalPeriodic(1000000 , updateClock);

	while (1)
	{
		PB_Update();
		ClockUserSetCheck();

	}
}
