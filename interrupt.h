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


//****************************************************************************//

//***************************** Variables ************************************//
 
//****************************************************************************//
void Interrupciones(void);
void isDoorClosed(void);