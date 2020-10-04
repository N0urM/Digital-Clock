/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 20/8/2020                                   */
/* Vesion: 1.0                                         */
/* File  : PB_PRIVATE.h                                */
/*******************************************************/ 
#ifndef     PB_PRIVATE_H
#define     PB_PRIVATE_H




typedef struct
{
    u8 samples[NUMBER_OF_SAMPLE];
    tPB_State state;
    t_PORT port;
    t_PIN pin;
}tPB_Info;

#endif  // End Of File
