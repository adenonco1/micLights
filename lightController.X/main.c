/*
 * File:   main.c
 * Author: Andy
 *
 * Created on September 9, 2024, 12:15 PM
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
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
void init_timer0(void);

unsigned char positive_out;
unsigned char negative_out;
unsigned char raw_input;

void main(void) {
    
    system_init();
    
    init_timer0();
    
    while(1) {
        
        while((INTCON & 0x04) == 0);
        
        process_io();               //should fire this every 32.5mS
        
        //clear the TMR0 int flag
        INTCON &= ~0x04;
    }
}

void system_init(void){
    
    //to do: set PB pull ups
    
    PORTA = 0;
    ANSEL = 0;
    TRISA = 0x00;
    
    PORTB = 0;
    TRISB = 0xf0;
    
    PORTC = 0;
    ANSEL = 0;
    TRISC = 0x00;
    
    //globally enable pull ups
    OPTION_REG &= ~0x80;
    
    raw_input = 0;
    positive_out = 0;
    negative_out = 0; 
}

void init_timer0(void){
    
    OPTION_REG &= ~0x20;    //timer0 set prescaler input to Fosc/4
    
    OPTION_REG &= ~0x08;    //Set prescaler input
    
    OPTION_REG |= 0x07;     //set PSA0, 1 and 2 high. Prescaler = 256
    OPTION_REG &= ~0x01;
}

void process_io(void){
    
    //grab the console inputs
    raw_input = (PORTB & 0xf0);     //active low
    
    positive_out = raw_input;
    negative_out = (~(positive_out >> 4)) & 0x0f;
    //negative_out = (negative_out & 0x0f);
    
    PORTC = (positive_out | negative_out);
        
    if(positive_out == 0xf0) {
        //master_tally = 1;
        PORTA &= ~0x20;
    } else {
        //master_tally = 0;
        PORTA |= 0x20;
    }
}

//PORTC 4, 5, 6, 7 negative logic outputs
//PORTC 0, 1, 2, 3 positive logic outputs
//PORTB 4, 5, 6, 7 console inputs
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