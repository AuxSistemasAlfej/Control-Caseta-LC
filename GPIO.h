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

#define Sens_porton1 RA2
#define Sens_porton2 RA3
#define OutDoor RA6
#define InDoor RA7

#define Porton1_En LATB0
#define Porton2_En LATB1

#define Sirena_Enable RC0
#define GreenLight_Enable RC1
#define RedLight_Enable RC2
#define Motor1 RC4
#define Motor2 RC5
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


void GPIO_init(void);