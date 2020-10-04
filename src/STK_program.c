/********************************************************/ 
/* Author : Nourhan Mansour                             */
/* Date   : 6/9/2020                                    */
/* Version: 2.2                                         */
/* File   : STK_program.c                               */
/********************************************************/ 

// 1- include Libraries 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// 2- include interface file of needed lower layers

// 3- include driver files
#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"



void STK_voidInit(void)
{
    CLR_BIT(STK -> CTRL , STK_CTRL_ENABLE);             // Stop Timer
    CLR_BIT(STK -> CTRL , STK_CTRL_TICKINT);            // Disable interrupt

    #if STK_CLK == SYS_CLK 
        SET_BIT(STK -> CTRL , STK_CTRL_CLKSPURCE);      // No prescalar - Use system Clock (AHB clock)
    
    #elif STK_CLK == SYS_CLK_DIV8
        CLR_BIT(STK -> CTRL , STK_CTRL_CLKSPURCE);      // With prescalar - Use system Clock/8 (AHB clock /8)
    
    #endif

}

void STK_voidStopTimer()
{
    CLR_BIT(STK -> CTRL , STK_CTRL_ENABLE);                 // Stop Timer
    CLR_BIT(STK -> CTRL , STK_CTRL_TICKINT);                // Disable interrupt

}


void STK_voidSetBusyWait(u32 cpy_Ticks )
{
    STK-> LOAD = cpy_Ticks;                                 // Load Value
    CLR_BIT(STK -> CTRL , STK_CTRL_TICKINT);                // Disable interrupt
    SET_BIT(STK -> CTRL , STK_CTRL_ENABLE);                 // Enable Timer
    while( ! GET_BIT(STK -> CTRL , STK_CTRL_COUNTFLAG) );   // Wait for Flag 
}



u32 STK_u32GetRemainingTime()
{
    u32 ret = STK -> VAL;                                   // Get current value
    return ret;
}

u32 STK_u32GetElapsedTime(void){
    u32 loadVal = STK -> LOAD;                              // Get value in the load Register
    u32 currentVal = STK -> VAL;                            // Get curretn value
    u32 ret = loadVal - currentVal;
    return ret;
}


void STK_voidSetIntervalSingle (u32 copy_ticks , void (*func)(void) )
{
    CLR_BIT(STK -> CTRL , STK_CTRL_ENABLE);             // Stop Timer
    STK -> VAL = 0;                                     // Reset value
    STK_functionCallBack = func;                        // Assign Call_Back
    STK -> LOAD = copy_ticks;                           // Load Value
    SET_BIT(STK -> CTRL , STK_CTRL_ENABLE);             // Enable Timer
    SET_BIT(STK -> CTRL , STK_CTRL_TICKINT);            // Enable interrupt
    PeriodicFlag = 0;                                   // Not Periodic
     
}

void STK_voidSetIntervalPeriodic(u32 copy_ticks , void (*func)(void) )
{
    STK_functionCallBack = func;                        // Assign Call_Back
    STK -> LOAD = copy_ticks;                           // Load Value
    SET_BIT(STK -> CTRL , STK_CTRL_ENABLE);             // Enable Timer
    SET_BIT(STK -> CTRL , STK_CTRL_TICKINT);            // Enable interrupt
    PeriodicFlag = 1;                                   // Periodic function
}

void SysTick_Handler(void)
{
    STK_functionCallBack();

    if (PeriodicFlag == 0 )
    {
        STK_voidStopTimer();
    }
}
