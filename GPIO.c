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
#include "GPIO.h"
#include "ALFEJ_Acc.h"
//****************************************************************************//

//***************************** PIC18 Configs ********************************//
//****************************************************************************//

//*************************** Defines ****************************************//
//****************************************************************************//

//***************************** Variables ************************************//

//****************************************************************************//

//******************************* GPIO_init **********************************//
//  RA0 = Sharp1          ->     Input
//  RA1 = Sharp2          ->     Input
//  RA2 = Sens_porton1    ->     Input
//  RA3 = Sens_porton2    ->     Input
//  RA6 = DoorOut         ->     Output
//  RA7 = DoorIn          ->     Output
////////////////////////////////////////////////////////////////////////////////
//  RB0 = Porton_Caseta   ->     Input
//  RB1 = Porton_Pared    ->     Input
//  RB6 = PGC             ->     N/A
//  RB1 = PGD             ->     N/A
////////////////////////////////////////////////////////////////////////////////
//  RC0 = SirenaEnable    ->     Output
//  RC1 = GreenLigthEnable->     Output
//  RC2 = RedLigthEnable  ->     Output
//  RC4 = Motor1 -- PARED ->     Output
//  RC5 = Motor2 -- CASETA->     Output
//  RC6 = Tx Pic18        ->     Output
//  RC7 = Rx Pic18        ->     Intput
////////////////////////////////////////////////////////////////////////////////
//  RE3 = MCLR            ->     N/A


void GPIO_init(void){
    /*GPIO*/
    
    /*PORT A*/
    
    TRISA0 = Input;
    ANSEL0 = ON;
    
    TRISA1 = Input;
    ANSEL1 = ON;
    
    TRISA2 = Input;
    ANSEL2 = OFF;
    
    TRISA3 = Input;
    ANSEL3 = OFF;
    
    TRISA6 = Output;
    OutDoor = Low;
    
    TRISA7 = Output;
    InDoor = Low;
    
    /* PORT B */
    TRISB0 = Input;
    ANSEL10 = OFF;
    
    TRISB1 = Input;
    ANSEL8 = OFF;
    
    /* PORT C */
    TRISC0 = Output;
    Sirena_Enable = LOW_TOR;
    
    TRISC1 = Output;
    GreenLight_Enable = LOW_TOR;
    
    TRISC2 = Output;
    RedLight_Enable = LOW_TOR;
    
    TRISC4 = Output;
    Motor1 = Low;
    
    TRISC5 = Output;
    Motor2 = Low;
    
    TRISC6 = Output;
    TRISC7 = Input;
}
