/*
 * File:   main.c
 * Author: Basema, Michelle, Vincent
 *
 * Created on: USE THE INFORMATION FROM THE HEADER MPLAB X IDE GENERATES FOR YOU
 */

// FBS
#pragma config BWRP = OFF               // Table Write Protect Boot (Boot segment may be written)
#pragma config BSS = OFF                // Boot segment Protect (No boot program Flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Code Flash Write Protection bit (General segment may be written)
#pragma config GCP = OFF                // General Segment Code Flash Code Protection bit (No protection)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Select (Fast RC oscillator (FRC))
#pragma config IESO = OFF               // Internal External Switch Over bit (Internal External Switchover mode disabled (Two-Speed Start-up disabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = ON            // CLKO Enable Configuration bit (CLKO output disabled; pin functions as port I/O)
#pragma config POSCFREQ = HS            // Primary Oscillator Frez  quency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8 MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary oscillator configured for high-power operation)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor Selection (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (WDT prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected; windowed WDT disabled)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware; SBOREN bit disabled)
#pragma config PWRTEN = ON              // Power-up Timer Enable bit (PWRT enabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Default location for SCL1/SDA1 pins)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (1.8V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (MCLR pin enabled; RA5 input pin disabled)

// FICD
#pragma config ICS = PGx2               // ICD Pin Placement Select bits (PGC2/PGD2 are used for programming and debugging the device)

// FDS
#pragma config DSWDTPS = DSWDTPSF       // Deep Sleep Watchdog Timer Postscale Select bits (1:2,147,483,648 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select bit (DSWDT uses LPRC as reference clock)
#pragma config RTCOSC = SOSC            // RTCC Reference Clock Select bit (RTCC uses SOSC as reference clock)
#pragma config DSBOREN = ON             // Deep Sleep Zero-Power BOR Enable bit (Deep Sleep BOR enabled in Deep Sleep)
#pragma config DSWDTEN = ON             // Deep Sleep Watchdog Timer Enable bit (DSWDT enabled)

// #pragma config statements should precede project file includes.

#include <xc.h>
#include <p24F16KA101.h>
#include <stdio.h>

/**
 * You might find it useful to add your own #defines to improve readability here
 */

int main(void) {
  
    AD1PCFG = 0xFFFF; /* keep this line as it sets I/O pins that can also be analog to be digital */
    
    
    // inputs: RB7, RB4, RA4
    TRISBbits.TRISB7 = 1; // set RB7 as input
    TRISBbits.TRISB4 = 1; // set RB4 as input
    TRISAbits.TRISA4 = 1; // set RA4 as input
        
    TRISBbits.TRISB9 = 0; // set RB9 as output
    
    CNPU2bits.CN23PUE = 1; // RB7 pull up low active (if pressed it is 0))
    CNPU1bits.CN1PUE = 1; // RB4 pull up low active (if pressed it is 0))
    CNPU1bits.CN0PUE = 1; // RA4 pull up low active (if pressed it is 0))
    while(1){
      
        while(PORTBbits.RB7==0) { // Check if the PB1 is pressed
            if(PORTBbits.RB4 == 0){ // Check if PB2 is pressed while PB1 is pressed (Both PB1 and PB2 are pressed)
               LATBbits.LATB9 =1; // When both buttons are pressed, LED turns on.
               break;
            }
            
            if(PORTAbits.RA4 == 0){ //Check if PB3 is pressed while PB1 is pressed (Both PB1 and PB3 are pressed)
                LATBbits.LATB9 =1; // When both buttons are pressed, LED turns on.
                break;
            }
            
            LATBbits.LATB9 =1; // When only one button (PB1 in this case) is pressed, LED turns on but for a certain amount of time
            for(long int i=0; i<214285; i++){ // LED on for 0.75 seconds. Calculation for the upperbound for i is in the report.
               Nop();  // Nothing happens just keep the LED ON for 0.75 seconds by looping.
            }
            LATBbits.LATB9 =0; // After the delay for LED ON, it is now off for certain amount of time, making look like it is blinking.
            for(long int i=0; i<214285; i++){ // LED off for 0.75 seconds
               Nop(); // Nothing happens just keep the LED OFF for 0.75 seconds by looping.
            }
            
       
        }
        while(PORTBbits.RB4==0) { // Check if the PB2 is pressed
            if(PORTBbits.RB7 == 0){ // Check if PB1 is pressed while PB2 is pressed (Both PB1 and PB2 are pressed)
                LATBbits.LATB9 =1;  // When both buttons are pressed, LED turns on.
                break; // After turning on the LED, it will now exit the while loop and return to the state where no buttons are pressed (LED OFF) 
            }            
            if(PORTAbits.RA4 == 0){ // Check if PB3 is pressed while PB2 is pressed (Both PB2 and PB3 are pressed)
                LATBbits.LATB9 =1;  // When both buttons are pressed, LED turns on.
                break;
            }
            
            LATBbits.LATB9 =1; // When only one button (PB2 in this case) is pressed, LED turns on but for a certain amount of time
            for(long int i=0; i<571428; i++){ // LED on for 2 seconds
                Nop(); // Nothing happens just keep the LED on for 2seconds by looping.
            }
            LATBbits.LATB9 =0; // After the delay for LED ON, it is now off for certain amount of time, making look like it is blinking.
            for(long int i=0; i<571428; i++){ // LED off for 2 seconds
                Nop(); // Nothing happens just keep the LED off for 2seconds by looping.
            }
        }
        
        
        while(PORTAbits.RA4==0) { // Check if the PB3 is pressed
            if(PORTBbits.RB4 == 0){ // Check if PB2 is pressed while PB3 is pressed (Both PB3 and PB2 are pressed)
                LATBbits.LATB9 =1;  // When both buttons are pressed, LED turns on.
                break;
            }
            
            if(PORTBbits.RB7 == 0){ // Check if PB1 is pressed while PB3 is pressed (Both PB1 and PB3 are pressed)
                LATBbits.LATB9 =1;  // When both buttons are pressed, LED turns on.
                break;
            }
            
            LATBbits.LATB9 =1; // When only one button (PB3 in this case) is pressed, LED turns on but for a certain amount of time
            for(long int i=0; i<1428571; i++){ //LED on for 5 seconds
                Nop(); // Nothing happens just keep the LED on for 2seconds by looping.
            }
            LATBbits.LATB9 =0; // After the delay for LED ON, it is now off for certain amount of time, making look like it is blinking.
            for(long int i=0; i<1428571; i++){ //LED off for 5 seconds
                Nop(); // Nothing happens just keep the LED off for 2seconds by looping.
            }
            
        } 
               
    
    } 
    while(PORTAbits.RA4==1 && PORTBbits.RB4==1 && PORTBbits.RB7==1){
        LATBbits.LATB9 =0;} // when none of the buttons are pressed, LED should always be OFF
    return 0;
} 
