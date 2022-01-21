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
#include "ADC.h"
#include "ALFEJ_Acc.h"
#include "GPIO.h"

//****************************************************************************//

//***************************** PIC18 Configs ********************************//

//****************************************************************************//

//*************************** Defines ****************************************//

//****************************************************************************//

//***************************** Variables ************************************//

//****************************************************************************//


void ADC0_Init(void){   
    ADCON1=0;                 // 5v to 0v  
    ADCON0=0;                 //AN0, godone = 0, ADON = 0.
     
    ADCON2bits.ADFM = 1;      //Right justified
    ADCON2bits.ACQT = 0b111;  //Acquisition time
    ADCON2bits.ADCS = 0b110;  //64Mhz/64 -> 1us
    
    ADON=1;
    GO_DONE = 1;
}

