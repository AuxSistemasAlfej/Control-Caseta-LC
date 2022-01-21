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
#include "UART.h"
#include "ALFEJ_Acc.h"
//****************************************************************************//

//***************************** PIC18 Configs ********************************//
//****************************************************************************//

//*************************** Defines ****************************************//
//****************************************************************************//

//***************************** Variables ************************************//
  
//****************************************************************************//



void UART_init (void){  
    TXSTA1 = 0b00100100;    //ASINCRONO, ALTA VELOCIDAD, TSR FULL, RC6
    RCSTA1 = 0b10010000;    //ASINCRONO, 8BITS, NO FERMING ERROR, NO OVER RUN ERROR, RC7
    BAUDCON1bits.BRG16 = 0; //PARA PODER DETERMINAR LA BAUD RATE (9600BPS)
    SPBRG1 = 51;            //VALOR DE N PARA 9615BPS
    
    /*TXSTA1 = 0b00100100;    //ASINCRONO, ALTA VELOCIDAD, TSR FULL, RC6
    RCSTA1 = 0b10010000;    //ASINCRONO, 8BITS, NO FERMING ERROR, NO OVER RUN ERROR, RC7
    BAUDCON1bits.BRG16 = 0;   // 8-bit Baud Rate Generator
    SPBRG1 = BaudRateTimer0;        // For Baud Rate Formula go to page 343
    */
}

unsigned char UART1_Read(void) {

    while (!PIR1bits.RC1IF) {
        if (RCSTA1bits.OERR) {
            RCSTA1bits.OERR = 0;
            RCSTA1bits.CREN = 0;
            RCSTA1bits.CREN = 1;
        }
    }
    PIR1bits.RC1IF = 0;
    
    /*
    if(PIR1bits.RC1IF){
        if(RCSTA1bits.OERR){
            RCSTA1bits.CREN = 0;
            RCSTA1bits.CREN=1;
        }
    }
    */

    return RCREG1;
}
