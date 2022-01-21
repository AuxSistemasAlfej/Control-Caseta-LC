/*
 * File:   Control_Acceso.c
 * Author: Ing. Jorge Cervantes
 *
 * Created on March 06 2021, 18:09hrs
 */
//*************************** General Includes *******************************//
#include <xc.h>
#include "pic18f25k80.h"
#include <stdio.h>
#include <stdlib.h>
//****************************************************************************//

//************************* Projects Includes ********************************//
//****************************************************************************//

//***************************** PIC18 Configs ********************************//
//****************************************************************************//

//*************************** Defines ****************************************//
#define Timer0_Prescale 0x07    // Timer0 Prescaler
//****************************************************************************//

//***************************** Variables ************************************//
unsigned int Timer0_Int_Count = 57721;  // Number of count for interruption at 1 seg.
unsigned int timer0ReloadVal = 57721 ;  // Reload variable

//****************************************************************************//


void Timer_init(void);