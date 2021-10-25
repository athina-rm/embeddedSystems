#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

void main (void) {	
	DDRB |= 1<<PINB1;		//sets bit 1 of Data Direction Register of Port  B so that pin 9 is output
	while(1){
		PORTB ^= 1<<PINB1;		//alternately writes 0 and 1 to pin 9
		_delay_ms(500);		
	}	
}
