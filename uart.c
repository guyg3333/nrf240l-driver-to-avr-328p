/*
 * uart.c
 *
 *  Created on: 24 срхїз 2016
 *      Author: etty
 */

#include "uart.h"


void USART_Init( unsigned int ubrr)
{
/*Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/*Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) )
;
/* Put data into buffer, sends the data */
UDR0 = data;
}

unsigned char USART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) )
;
/* Get and return received data from buffer */
return UDR0;
}

unsigned char usart_kbhit(void) {
    //return nonzero if char waiting polled version
    unsigned char b;
    b=0;
    if(UCSR0A & (1<<RXC0)) b=1;
    return b;
}
void usart_pstr(unsigned char *s) {
    // loop through entire string
    while (*s) {
    	USART_Transmit(*s);
        s++;
    }
}



int usart_putchar_printf(unsigned char var, FILE *stream) {
    if (var == '\n') USART_Transmit('\r');
    USART_Transmit(var);
    return 0;
}

int loadString(unsigned char* buffer,char* MASSEGE){

	unsigned char c='\0';
			printf(MASSEGE);
			int i = 0;
			while(c!='\r')
			{
				c = '\0';
				c = USART_Receive();
				if((c!='\0')&(c!='\r')) {
					printf("%c",c);
					i++;
					*buffer++ = c;}
			}
				printf("\n");
				return i;
	 }//loadString


int YesNoQ( char* MASSEGE,char* yes, char*no){

	unsigned char c='\0';
			printf(MASSEGE);
			printf("\nPress Y for "); printf(yes); printf(" and N for "); printf(no); printf("\n\n");
			while(1){
				c = USART_Receive();
				if((c=='y')|(c=='Y')) return 1;
				if((c=='n')|(c=='N')) return 0;
			}//while
	 }//YesNoQ


void USART_Flush( void )
{
unsigned char dummy;
while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}

void ptinrHEX( char hex){

	unsigned char temp[2];
	temp[1] = (hex)&(0x0F);
	temp[0] = (hex>>4)&(0x0F);

	for(int i=0;i<2;i++)
	{
		switch(temp[i])
		{
		case 10:  temp[i] ='A'; break;
		case 11:  temp[i] ='B'; break;
		case 12:  temp[i] ='C'; break;
		case 13:  temp[i] ='D'; break;
		case 14:  temp[i] ='E'; break;
		case 15:  temp[i] ='F'; break;

		default : temp[i] += 48; break;
		}//switch

	}//for
	printf("%c%c ",temp[0],temp[1]);
}







