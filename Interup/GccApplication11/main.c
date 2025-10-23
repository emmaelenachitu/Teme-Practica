/*
 * GccApplication11.c
 * Author : emmae
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define baud 9600
#define UBRRVAL ((F_CPU/16/baud) - 1)

// Buffer pentru transmitere/recep?ie
volatile char received_char = 0;  // stocheaz? caracterul primit

// Initializare UART
void uart_init(void){
    UBRR0H = (unsigned char)(UBRRVAL >> 8);
    UBRR0L = (unsigned char)UBRRVAL;
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); // TX, RX si RX Interrupt
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
}

// Transmitere caracter (polling)
void uart_putc(char c){
    while(!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

// Transmitere sir
void uart_puts(const char *s){
    while(*s)
        uart_putc(*s++);
}

// ISR pentru receptionare UART
ISR(USART0_RX_vect){
	received_char = UDR0;      // citeste caracterul din buffer
	uart_putc(received_char);  // echo inapoi
}


int main(void){
    uart_init();
    sei();  // enable global interrupts

    uart_puts("UART Reception Interrupt Example\r\n");

    while(1){}
    
}
