/*
 * File:   main.c
 * Author: Andy
 *
 * Created on September 9, 2024, 12:15 PM
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = EXTRCIO   // Oscillator Selection bits (RCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

void system_init(void);

void process_io(void);

unsigned char input_lines;
unsigned char masked_input;
unsigned char output_lines_pos;
unsigned char output_lines_neg;
unsigned char master_tally;
unsigned char raw_input;

void main(void) {
    
    system_init();
    
    while(1) {
        
        process_io();
        
    }
    
    
//    return;
}

void system_init(void){
    
    PORTA = 0;
    TRISA = 0x20;
    
    PORTB = 0;
    TRISB = 0xf0;
    
    PORTC = 0;
    TRISC = 0xf0;
    
    raw_input = 0;
    masked_input = 0;
    output_lines_pos = 0;
    output_lines_neg = 0;
    master_tally = 0;
 
}





void process_io(void){
    
    //grab the console inputs
    raw_input = (PORTC & 0xf0);
    //set the positive outputs
    output_lines_pos = raw_input;
    output_lines_neg = ~output_lines_pos;
    
    
    if(output_lines_neg) {
        master_tally = 1;
    } else {
        master_tally = 0;
    }
    
    
    
    
    
}

//PORTC 4, 5, 6, 7 inputs from console
//PORTC 0, 1, 2, 3 positive logic outputs
//PORTB 4, 5, 6, 7 negative logic outputs
//PORTA5, main tally out

/*
   PORTA = 0;
    LATA = 0;
    ANSELA = 0;
    TRISA = 0xff;
    
    WPUA = 0x23;
    
    //PortB
    PORTB = 0x00;
    LATB = 0x00;
    ANSELB = 0x00;
    TRISB = 0x70;
    
    //PortC
    PORTC = 0x00;
    LATC = 0x00;
    ANSELC = 0x00;
    TRISC = 0x38;
    
    
    TRISC &= 0x80;
    
    ANSELC &= 0x80;
    
    WPUC = 0x78;
    
 
 
 
 */