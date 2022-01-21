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
#include "ALFEJ_Acc.h"
#include "UART.h"
#include "Timers.h"
#include "GPIO.h"
#include "ADC.h"
#include "interrupt.h"

//***************************** PIC18 Configs ********************************//
#pragma config XINST = OFF      //PERMITE DEBUGEAR 
#pragma config SOSCSEL = DIG    //PUERTO C COMO DIGITAL
#pragma config WDTEN = OFF      //TIMER
#pragma config MCLRE = OFF      //MASTER CLEAR
//****************************************************************************//

//*************************** Defines ****************************************//

//****************************************************************************//

//***************************** Variables ************************************// 

//****************************************************************************//


void main(void) {
    
    GPIO_init();        // Pin configuration
    Timer_init();       // Set Timer 0 for 1seg. flag
    UART_init();        // Enable UART Port 9600bit/s
    Interrupciones();   // Interruptions configuration
    ADC0_Init();
    
                  
    while(1){
        GO_DONE = 1;  
    }
}

