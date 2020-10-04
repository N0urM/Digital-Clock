/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 20/8/2020                                   */
/* Vesion: 1.0                                         */
/* File  : PB_INTERFACE.h                              */
/*******************************************************/ 
#ifndef     PB_INTERFACE_H
#define     PB_INTERFACE_H

typedef enum
{
    PB_MINIUTE,
    PB_HOUR,
    PB_RESET,
}tPB;

typedef enum
{
    PB_RELEASED,
    PB_PRE_PRESSED,
    PB_PRESSED,
    PB_PRE_RELEASED
}tPB_State;


void PB_Init(t_PORT cpy_port ,t_PIN cpy_pin ,tPB pb, tPB_State initial_state);
void PB_Update(void);
tPB_State PB_GetState(tPB pb);

#endif  // End Of File
