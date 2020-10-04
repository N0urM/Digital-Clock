
/********************************************************/
/* Author : Nourhan Mansour                             */
/* Date   : 4/10/2020                                   */
/* Version: 1.0                                         */
/* File   : DigitalClock.h                              */
/********************************************************/
#ifndef DIGITALCLOCK_CONFIG_H
#define DIGITALCLOCK_CONFIG_H

/**** Global Variables ****/
// Set initial Time values
u8 DateDay   = 4;
u8 DateMonth = 10;
u16 DateYear = 2020;

u8 TimeHour = 23;
u8 TimeMin  = 59;
u8 TimeSec  = 50;
u8 TimeMode = 0;  // 0 = AM , 1 = PM

u8 DayNameIndex = 1;

#endif // End Of File
