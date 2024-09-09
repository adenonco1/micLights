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
void pins_init(void);
void read_input_pins(void);
void process_io(void);

unsigned char input_lines;
unsigned char masked_input;
unsigned char output_lines_pos;
unsigned char output_lines_neg;
unsigned char master_tally;
unsigned char raw_input;

void main(void) {
    
    system_init();
    
    pins_init();
    
    while(1) {
        
        read_input_pins();
        
        process_io();
        
    }
    
    
//    return;
}

void system_init(void){
     
 
}

void pins_init(void){
        
}

void read_input_pins(void) {
    raw_input = PORTA;
    masked_input = (raw_input & 0x0f);
}

void process_io(void) {
    
    masked_input = (raw_input & 0x0f);
    if(masked_input){
        master_tally = 0x01;
    }
    
    
}