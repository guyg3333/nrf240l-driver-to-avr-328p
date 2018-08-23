/*
 * main.c
 *
 *  Created on: 22 срхїз 2016
 *      Author: etty
 */
#include "usci.h"
#include "nrf2401.h"
#include <avr/io.h>
#include "stdio.h"
#include <avr/delay.h>
#include "main.h"
//#include <avr/iom328p.h>

#define can_select    (PORTB &= ~(1<<PORTB2)) // GUY
#define can_deselect  (PORTB |= (1<<PORTB2)) //


int main(void){

stdout = &mystdout; 	// setup our stdio stream
USART_Init(MYUBRR);
spi_masterInit();

printf("\n"
"========================\n"
" BBBBB   GGGGG   RRRRR\n"
" BB   B GGG      RR   R\n"
" BBBBB  GG  GGG  RRRRR\n"
" BB   B GGG  GG  RR   R\n"
" BBBBB   GGGGG   RR   R\n"
"========================\n");

int boolian;
unsigned char buffer[100]; //set buffer
unsigned char byets=0;
boolian = YesNoQ( "Set Prime mode","PTR","PRC");

	if(boolian) {
			nrf24_initalize(1);
			nrf24_ce_low;
			while(1){ // TX mode

					nrf24_read(STATUS,buffer,1); // clear status register
					printf("STATUS = %d \n",buffer[0]);
					nrf24_read(STATUS,buffer,1); // clear status register
					nrf24_write(STATUS,buffer,1);
					nrf24_read(STATUS,buffer,1); // clear status register
					printf("STATUS = %d \n",buffer[0]);

					nrf24_read(FIFO_STATUS,buffer,1);
					printf("FIFO_STATUS = %d \n",buffer[0]);

					nrf24_write(FLUSH_TX,buffer,0); // FLUSH TX
					nrf24_read(FIFO_STATUS,buffer,1);
					printf("FIFO_STATUS = %d \n",buffer[0]);

					byets = loadString(buffer,"enter data to send\n");  //write payload to TX_FIFO

					nrf24_write_tx(byets,buffer);//
					nrf24_read(STATUS,buffer,1);
					byets = 0;

					while((!(buffer[0]&(1<<TX_DS)))&&!(byets==50))  // while TX_DS != 1
					{
						nrf24_read(STATUS,buffer,1);
						byets++;
						_delay_us(10);
					}
					if(byets==50) printf("massige error\n");
					else printf("massige ok\n");
					nrf24_read(STATUS,buffer,1);
					printf("STATUS = %d \n",buffer[0]);
					nrf24_write(STATUS,buffer,1);

			}//while
	}// master
	else { //slave

		nrf24_initalize(0);
		nrf24_ce_low;
		_delay_us(10);


		nrf24_read(FIFO_STATUS,buffer,1); // FLUSH RX
		printf("FIFO_STATUS = %d \n",buffer[0]);

		nrf24_read(STATUS,buffer,1);
		printf("STATUS = %d \n",buffer[0]);

		nrf24_read(STATUS,buffer,1);
		nrf24_write(STATUS,buffer,1);
		nrf24_read(STATUS,buffer,1);
		printf("STATUS = %d \n",buffer[0]);


		nrf24_write(FLUSH_RX,buffer,0); // FLUSH
		nrf24_read(FIFO_STATUS,buffer,1); // FLUSH
		printf("FIFO_STATUS = %d \n",buffer[0]);
		nrf24_ce_high;
		_delay_us(130);


			while(1){

				nrf24_read(STATUS,buffer,1);
				if((buffer[0]&(1<<RX_DR)))

				{
					byets = nrf24_get_payload_width();
					nrf24_read_rx(buffer,byets);

					for(int j=0;j<byets;j++)
						 ptinrHEX(buffer[j]);
					printf("\n");

							nrf24_write(FLUSH_RX,buffer,0); // FLUSH RX
							nrf24_read(STATUS,buffer,1);
							nrf24_write(STATUS,buffer,1);
				}//if
			}//while
	}//else
}//main











