/*
 * GccApplication9.c
 * Author : emmae
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define baud 9600
#define UBRRVAL ((F_CPU/16/baud) -1) //formula de calucul catr de repede sa scoata bitii pe linie 

void uart_init(void){
	UBRR0H = (unsigned char)(UBRRVAL >> 8);  //scrierea baud ului de pe 16 biti pe 8 biti
	UBRR0L = (unsigned char)UBRRVAL;		 //scrierea baud ului de pe 16 biti pe 8 biti
	UCSR0B = (1 << TXEN0);					 //activarea registrului care controleaza principalele functii ale UART0
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //formatul datelor e pe 8 biti
}
void uart_putc(char c){				 
		while(!(UCSR0A & (1 << UDRE0)))		//(UCSR0A & (1 << UDRE0))- UDRE0=1 adica registrul de date este gol si pregatit sa primeasca un nou caracter;  
											//negarea inseamna ca asteapta pana cand bufferul este gol
		;                                   //se asteapta
		UDR0 = c;                           //primeste caracter cand UDRE0 e 1
	}	

void uart_puts(const char *s){              //const char *s- adresa unui sir care se termina in \0
	while(*s)                               //while caracterul citit nu e sfarsitul sirului
	uart_putc(*s++);                        //transmite sirul carcater cu caracter 
}



int main(void)
{
	uart_init();
	uart_puts("Embedded Systems Course\r\n");
	
    
    while (1) 
    {
		uart_putc('A');
		_delay_ms(1000);
    }
}

