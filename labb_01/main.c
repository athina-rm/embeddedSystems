#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

void main (void) {	
	uart_init();					//initialises settings serial interface 
	DDRB |= 1<<DDB1;				//sets bit 1 of Data Direction Register of Port  B so that pin 9 is output	
	PORTB |= 1<<PB1;				//keeps the blue Led OFF		

	while(1){
		/*PORTB ^= 1<<PIN1;			//alternately writes 0 and 1 to pin 9 to make the LED blink
		_delay_ms(500);
		uart_putchar('a');			
		uart_putchar('\n');
		uart_putstr("Athina\n");*/
		uart_echo();
	}
}
