
/********************************************************/
/* Author : Nourhan Mansour                             */
/* Date   : 4/10/2020                                   */
/* Version: 1.0                                         */
/* File   : DigitalClock.h                              */
/********************************************************/
#ifndef DIGITALCLOCK_PRIVATE_H
#define DIGITALCLOCK_PRIVATE_H

// Private functions
void AppendIntegerToString(u8 * string, u16 integer);
void AppendChar(u8 * string, u8 charToAppend);
void UpdateTime(void);
void updateDisplayStrings(void);

// Private variables
u8 Date[20] = { 0 };
u8 Time[20] = { 0 };
const u8 * Weekday[7] = { "Saturday", "Sunday", "Monday", "Tuesday",
		"Wednesday", "Thursday", "Friday" };
const u8 Monthdays[15] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
u8 TimeHourToDisplay;

#endif // End Of File

