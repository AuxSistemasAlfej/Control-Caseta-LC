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
#include "Timers.h"
#include "ALFEJ_Acc.h"
//****************************************************************************//

//***************************** PIC18 Configs ********************************//

//****************************************************************************//

//*************************** Defines ****************************************//

//****************************************************************************//

//***************************** Variables ************************************//
//****************************************************************************//


void Timer_init(void){   
    TMR0H = Timer0_Int_Count << 8;  // TMR0H 255; 
    TMR0L = Timer0_Int_Count;       // TMR0L 121; 
    T0CON = 0x97;                   // T0PS 1:256; T08BIT 16-bit; T0SE Increment_hi_lo; T0CS FOSC/4; TMR0ON enabled; PSA assigned; 
    
    T0CONbits.T08BIT = Clear;          // Set Timer0 as 16bits mode
    T0CONbits.T0CS = Clear;            // Workin with the innternal clock
    T0CONbits.T0SE = Set;              // Increment on high-to-low transition on T0CKI pin
    T0CONbits.PSA = Clear;           // Timer0 prescaler is assigned
    T0CONbits.T0PS = Timer0_Prescale;  // Prescaler
    T0CONbits.TMR0ON = OFF;            // Enables Timer0
}
