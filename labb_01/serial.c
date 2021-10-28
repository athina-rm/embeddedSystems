#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"

#define FOSC 16000000 //clock speed
#define BAUD 38400  //baud rate

//configures USART0 to tx 8N1 in 38400 baud rate
void uart_init(void){
    UCSR0C &=~(1<<UMSEL01 & 1<<UMSEL00);//UMSELn bit in USART control and status register C (UCSRnC) selects asynchronous operation with 00
    
    //sets the baud rate
    unsigned int ubrr =(FOSC/(16*BAUD))-1;
    UBRR0H =(unsigned char) (ubrr>>8);
    UBRR0L=(unsigned char) ubrr;

    // sets frame format 8N1
    UCSR0C &= ~(1<<USBS0); //1 stop bit during transmission
    UCSR0C |=1<<UCSZ01 | 1<<UCSZ00; //8-bits data
    UCSR0C &= ~(1<<UMSEL00 & 1<<UMSEL01);//no parity
    //frame format used by the USART is set by the UCSZn2:0(character size-no.of data bits/frame), UPMn1:0 (parity mode)and USBSn(stop bit select) bits in UCSRnB and UCSRnC.  

    UCSR0B=(1<<RXEN0)|(1<<TXEN0);//enabling the transmitter and the receiver
}

//checks and decides which character to send to the uart
void uart_putchar(char chr)
{
    if (chr=='\n'){         
        uart_tx('\r');         //to send "\r\n" instead of '\n'
    }
    uart_tx(chr);        
}

//transmits the character
void uart_tx(char chr){
    //data register empty (UDREn) flag bit is set when the transmit buffer is empty and indicates it is ready to receive new data.
    while((UCSR0A &(1<<UDRE0))==0){
        //buffer is neither empty nor ready
    }
    UDR0=chr;                       //UDR0-USART I/O Data Register 
}

//transmits a string to serial port
void uart_putstr(const char *str){
    for(int i=0;str[i]!='\0';i++){          //to iterate from character in 0 position to end of the string
        uart_putchar(str[i]);               //tranmits the character       
    }
}

//gets the character rxvd in USART Data register
char uart_getchar(void){
    while (!(UCSR0A & (1<<RXC0))){}
/* Get and return received data from buffer */
    return UDR0;
}

//echos each character rxvd to the screen
void uart_echo(void){
    uart_putchar(uart_getchar());
}