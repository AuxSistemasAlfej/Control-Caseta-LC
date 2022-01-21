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
#include "interrupt.h"
#include "ALFEJ_Acc.h"
#include "Timers.h"
#include "GPIO.h"
#include "UART.h"
#include "ADC.h"
//****************************************************************************//

//***************************** PIC18 Configs ********************************//
//*****************************//

//*************************** Defines ****************************************//

//****************************************************************************//

//***************************** Variables ************************************//
unsigned char Data_In = 0;
unsigned int i_adc_sharp= 0, pila1 = 0, pila2 = 0,i_gera=0,Street_Door_Close = 1,In_Door_Close = 1;
float media=0;
unsigned int datos_in[80],datos_street[80], cuantos_in = 0,cuantos_street = 0;
int suma = 0, in_low = 480,in_high=560,timer=0;
//****************************************************************************//

void Interrupciones(void){
    /*Interupciones*/
    IPEN = Enable;   //Habilitador Global
    GIEH = Enable;   //Declaracion de Alta Prioridad
    GIEL = Enable;   //Dclaracion de Baja Prioridad
    
    /*ADC*/
    ADIE = Disable;  //Its enable when the app is opended
    ADIF = 0;
    ADIP = 0; //
    
    /*TIMER0*/
    TMR0IE = Enable;    //Habilitador global TIMER
    TMR0IF = Clear;
    TMR0IP = Low;    //Declaracion de Baja prioridad

    /*TIMER1*/
    TMR1IE = Enable;    //Habilitador global TIMER
    TMR1IF = Clear;
    TMR1IP = Low;    //Declaracion de Baja prioridad
    
    /*INT0*/
    INT0IE = Enable;    //habilitador global y simpre es Alta prioridad
    INT0IF = Disable;   //habilitador global y simpre es Alta prioridad
    INTEDG0 = Enable;   //Detecta Flanco de bajada. 0

    /*INT1*/
    INT1IE = Enable;    //habilitador global y simpre es Alta prioridad
    INT1IF = Disable;   //habilitador global y simpre es Alta prioridad
    INTEDG1 = Enable;   //Detecta Flanco de bajada. 0

    /*TX*/
    TX1IE = Disable;    // habilitador global
    TX1IP = Disable;     // Declaracion de Baja prioridad
    TX1IF = Disable;    // Declaracion de Baja prioridad

    /*RX*/
    RC1IE = Enable;    // habilitador global
    RC1IP = Disable;     // Declaracion de Baja prioridad
    RC1IF = Disable;    // Declaracion de Baja prioridad Recepcion2020
}

__interrupt(high_priority) void ISC_High(void){ //Interrupcion de alta Prioridad nuevo formato

    /*Close Gate control*/
    /**************************************************************************/
    if(INT0IE && INT0IF){
        for(unsigned int i = 0; i<= 1000; i++){asm("nop");}
        if(INT0IE && INT0IF){
            for(unsigned int i = 0; i<= 60000; i++){asm("nop");}
            if(Sens_porton2){
                INT0IF = 0;
                INT1IE = 0;
                INT1IF = 0;
            
                Motor1 = 1;
                //Porton1_En = Set;
                for(unsigned int count = 0; count <= 10000; count++){asm("nop");}
                Motor1 = 0;
                //Porton1_En = Clear;
            }
        }
    }
    /**************************************************************************/
    
    /**************************************************************************/
    if (INT1IE && INT1IF){
        for(unsigned int i = 0; i<= 1000; i++){asm("nop");}
        if (INT1IE && INT1IF){
            for(unsigned int i = 0; i<= 60000; i++){asm("nop");}
            if(Sens_porton1){
                INT1IF = 0;
                INT0IE = 0;
                INT0IF = 0;
                
                Motor2 = 1;
                //Porton2_En = Set;
                for(unsigned int count = 0; count <= 10000; count++){asm("nop");}
                Motor2 = 0;
                //Porton2_En = Clear;
                
                //for(unsigned int count = 0; count <= 50000; count++){asm("nop");}
            }       
           
        }
    }
    /**************************************************************************/
    
    for(double i = 0; i<= 30000; i++){asm("nop");}
    INT0IE = 1;
    INT1IE = 1;
    
    /*Timer for counting time for doors*/
    /**************************************************************************/
    if( TMR0IE && TMR0IF )//Contador de Timer0
    {
        TMR0H = Timer0_Int_Count << 8;  // TMR0H 255; 
        TMR0L = Timer0_Int_Count;       // TMR0L 121; 
        TMR0IF = 0;
    }
    
}

__interrupt(low_priority) void ISC_Low(void){ //Interrupcion de Baja Prioridad Nuevo formato
    
    if(ADIE && ADIF){
        ADIF = 0;
        
        ADON = 0;
        ADCON0 = 0x00;
        ADON = 1;
        GO_DONE=1;
        for(int i=0;i<12;i++){asm("nop"); }// Wait 1 Cycle  
        pila1 = ADRESL + (ADRESH<<8); 
        datos_in[i_gera] = pila1;

        ADON = 0;
        ADCON0 = 0x04;
        ADON = 1;
        GO_DONE=1;
        for(int i=0;i<12;i++){asm("nop"); }// Wait 1 Cycle  
        pila2 = ADRESL + (ADRESH<<8); 
        datos_street[i_gera] = pila2;
        GO_DONE = 0;
        i_gera++;
        timer += 1;
        
        if(i_gera >= 100){
            isDoorClosed();
        }
        else if(timer > 5000){
            Sirena_Enable = LOW_TOR;
        }
            GO_DONE = 1;
    }
    
    if(TX1IE && TX1IF){
        
    }
    
    if(RC1IE && RC1IF){
        //RC1IF = 0;   //Se Apaga la Bandera
        Data_In = UART1_Read();
        RC1IF = 0; 
        timer = 0;
        
        if(Data_In == 0xFF){ // Application is requesting a set ready
            OutDoor = Enable;
            InDoor = Enable;
            ADON = 1;
            ADIE = 1;    
            
        }
        else if(Data_In == 0xF0){ // Application is requesting open outside door
            OutDoor = Enable;
            InDoor = Disable;
            Sirena_Enable = HIGH_TOR;    
        }
        else if(Data_In == 0x0F){ // Application is requesting open inside door
            OutDoor = Disable;
            InDoor = Enable;
            Sirena_Enable = HIGH_TOR;
        }
        else if(Data_In == 0xAA){ // Application is requesting open inside door
            OutDoor = Disable;
            InDoor = Disable;
        }
        else if(Data_In == 0xCC){ //RESET PIC 
            for(int i=0;i<1200;i++){asm("nop"); }
            asm("reset");
            for(int i=0;i<1200;i++){asm("nop"); }
        }
        else if(Data_In == 0xEE){ //Shutdown app
            for(int i=0;i<1200;i++){asm("nop"); }
            Sirena_Enable = LOW_TOR;
            GreenLight_Enable = LOW_TOR;
            RedLight_Enable = LOW_TOR;
            
            OutDoor = Disable;
            InDoor = Disable;
  
            ADON = 0;
            ADIE = 0;   
        }
        Data_In = 0;
    }
    
}

unsigned int shellSort(unsigned int arr[], int n){
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2){
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < n; i += 1){
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            unsigned int temp = arr[i];
 
            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;           
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
             
            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
    return 0;
}

void isDoorClosed(void){
    suma = 0;
      
    if(i_gera >= 80){      
           shellSort(datos_in, sizeof(datos_in)/sizeof(datos_in[0]));
           shellSort(datos_street, sizeof(datos_street)/sizeof(datos_street[0]));
           
           //Puerta adentro
           media = datos_in[40];
            if(media > 650 && media < 780){
                cuantos_in += 1;
                
                if(cuantos_in > 50){
                    In_Door_Close = 1;//Cerrada
                }
                else{
                    In_Door_Close = 0;//Abierta
                }
            }
            else{
                cuantos_in = 0;
            }
           
            //Puerta calle
            media = datos_street[40];
            if(media > 580 && media < 680){
                cuantos_street += 1;
                
                if(cuantos_street > 50){
                    Street_Door_Close = 1; //Cerrada
                }
                else{
                    Street_Door_Close = 0;//Abierta
                }
            }
            else{
                cuantos_street = 0;
            }
            i_gera = 0; 
        }
        
        if(!Street_Door_Close || !In_Door_Close){
            GreenLight_Enable = LOW_TOR;
            RedLight_Enable = HIGH_TOR;
            Sirena_Enable = LOW_TOR;
        } 
        else if(Street_Door_Close && In_Door_Close){
            GreenLight_Enable = HIGH_TOR;
            RedLight_Enable = LOW_TOR;
        }
}