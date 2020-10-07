/********************************************************/
/* Author : Nourhan Mansour                             */
/* Date   : 27/9/2020                                   */
/* Version: 1.0                                         */
/* File   : TFT_program.c                               */
/********************************************************/

// 1- include Libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "TFT_interface.h"
#include "PB_interface.h"

#include "DigitalClock.h"
#include "DigitalClock_Config.h"
#include "DigitalClock_private.h"


/* functions definitions */

void DigitalClockinit()
{
	TFT_voidPrintText(20, 20, "Digital Clock ", 0xF760, 0);
	TFT_voidPrintText(30, 40, Date, 0x7F9D, 0);
	TFT_voidPrintText(30, 60, Time, 0x7F9D, 0);
	TFT_voidPrintText(40, 80, Weekday[DayNameIndex], 0xE61F, 0);
}

void ClockUserSetCheck()
{

	u8 temp  = 0;
	temp = PB_GetState(PB_HOUR);
	if (temp  == PB_PRE_RELEASED)
		TimeHour++;
	temp = PB_GetState(PB_MINIUTE);
		if (temp  == PB_PRE_RELEASED)
			TimeMin++;

}

void updateClock()
{
	UpdateTime();
	updateDisplayStrings();
	TFT_voidPrintText(30, 40, Date, 0x7F9D, 0);
	TFT_voidPrintText(30, 60, Time, 0x7F9D, 0);
	TFT_voidPrintText(40, 80, Weekday[DayNameIndex], 0xE61F, 0);
	if (TimeMode) {
		TFT_voidPrintText(90, 60, "PM", 0x7F9D, 0);
	} else {
		TFT_voidPrintText(90, 60, "AM", 0x7F9D, 0);
	}
}


/******** Private Functions ************/

void UpdateTime(void)
{
	TimeSec++;
	if (TimeSec > 59) {
		TimeSec = 0;
		TimeMin++;
	}
	if (TimeMin > 59) {
		TimeMin = 0;
		TimeHour++;
	}
	if (TimeHour > 23) {
		DateDay++;
		if (++DayNameIndex > 6) {
			DayNameIndex = 0;
		}
		TimeHour = 0;
	}

	if (DateDay > Monthdays[DateMonth]) {
		DateDay = 1;
		DateMonth++;
	}
	if (DateMonth > 12) {
		DateMonth = 1;
		DateYear++;
	}

}

void AppendIntegerToString(u8 * string, u16 integer) {
	while (*(string++) != '\0')
		;
	*string--;
	u8 temp[20] = { 0 };
	u8 * ptr = temp;

	if (integer == 0) {
		*string++ = '0';
		*string++ = '0';
	} else {

		while (integer) {
			*ptr = ((integer % 10) + '0');
			ptr++;
			integer /= 10;
		}

		if (ptr <= temp + 1) {
			*string++ = '0';
		}

		while ((ptr--) != temp) {
			*string++ = *ptr;
		}
	}
	*string = '\0';
}

void updateDisplayStrings() {
	if (TimeHour == 12 ){
		TimeHourToDisplay = TimeHour;
		TimeMode = 1; // PM
	}
	else if (TimeHour > 12) {
		TimeHourToDisplay = TimeHour - 12;
		TimeMode = 1; // PM
	}
	else
	{
		TimeHourToDisplay = TimeHour;
		TimeMode = 0; // AM
	}
	Date[0] = '\0';
	AppendIntegerToString(Date, DateDay);
	AppendChar(Date, '/');
	AppendIntegerToString(Date, DateMonth);
	AppendChar(Date, '/');
	AppendIntegerToString(Date, DateYear);
	Time[0] = '\0';
	AppendIntegerToString(Time, TimeHourToDisplay);
	AppendChar(Time, ':');
	AppendIntegerToString(Time, TimeMin);
	AppendChar(Time, ':');
	AppendIntegerToString(Time, TimeSec);
}

void AppendChar(u8 * string, u8 charToAppend)
{
	while (*(string++) != '\0')
		;
	*string--;
	*string++ = charToAppend;
	*string = '\0';
}

