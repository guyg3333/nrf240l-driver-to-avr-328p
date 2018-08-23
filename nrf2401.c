/*
 * nrf2401.c
 *
 *  Created on: 19 срхїз 2016
 *      Author: etty
 */

// Include files
#include "nrf2401.h"
#include <util/delay.h>
#include "main.h"

unsigned char delay_us = 255;

/**************************************************************************************************
 * PUBLIC FUNCTIONS
 *************************************************************************************************/




 /**************************************************************************************************
 * PRIVATE FUNCTIONS
 *************************************************************************************************/
void nrf24_read( unsigned char address, unsigned char *ptr, unsigned char bytes )
{
	unsigned char i;

	_delay_us(delay_us);
	nrf24_csn_low;
	_delay_us(delay_us);
	spi_transmit( address);
	for( i = 0; i < bytes; i++ ){
		*ptr++ = spi_exchange( 0x00 );
	}
	nrf24_csn_high;


}


void nrf24_write( unsigned char address, unsigned char *ptr, unsigned char bytes )
{
	unsigned char i;
	_delay_us(delay_us);
	nrf24_csn_low;
	_delay_us(delay_us);
	spi_transmit(  0x20 | address );
	for( i = 0; i < (bytes-1); i++ )
	{
		spi_transmit( *ptr++ );
	}
	spi_transmit( *ptr );
	nrf24_csn_high;
}

unsigned char nrf24_get_payload_width(){

	unsigned char bytes;
	_delay_us(delay_us);
	nrf24_csn_low;
	_delay_us(delay_us);

	spi_transmit( R_RX_PL_WID );
	bytes =  spi_exchange( 0x00 );

	nrf24_csn_high;
	return bytes;
}

void nrf24_read_rx( unsigned char *ptr, unsigned char bytes)
{
	unsigned char i;


	_delay_us(delay_us);
	nrf24_ce_low;
	nrf24_csn_low;
	_delay_us(delay_us);

	spi_transmit( R_RX_PAYLOAD);

	for( i = 0; i < bytes; i++ ){
		*ptr++ = spi_exchange( 0x00 );
	}
	nrf24_csn_high;
	_delay_us(delay_us);
	nrf24_ce_high;
}

void nrf24_write_tx( unsigned char bytes, unsigned char *ptr )
{

	unsigned char i;

	_delay_us(delay_us);
	nrf24_csn_low;
	_delay_us(delay_us);

	spi_transmit(W_TX_PAYLOAD);
	for( i = 0; i < (bytes-1); i++ )
	{
		spi_transmit( *ptr++ );
	}
	spi_transmit( *ptr );

	nrf24_csn_high;
	_delay_us(delay_us);

	nrf24_ce_high;
	_delay_us(delay_us);

	nrf24_ce_low;

}

void nrf24_initalize(unsigned char ptype){



	unsigned char addres[5]; //address for the receiving node TX_ADDE
    addres[0] = 0x00;


    if(ptype){ // if master

    	printf("NRF24 master initalize\n");



#define MASK_TX_DR	(6)
#define MASK_TX_DS	(5)
#define MASK_MAX_RT	(4)
#define EN_CRC		(3)
#define CRCO		(2)
#define PWR_UP		(1)
#define PRIM_RX		(0)


    	nrf24_read(CONFIG,addres,1);
    	addres[0] |=  (1<<EN_CRC); //set PWR_UP low //Set PRIME_RX low
		addres[0] &=  ~((1<<PRIM_RX)|(1<<PWR_UP)|(1<<MASK_TX_DR)|(1<<MASK_TX_DS)|(1<<CRCO)); //set PWR_UP low //Set PRIME_RX low

		nrf24_write(CONFIG,addres,1);
		printf("CONFIG = %d \n",addres[0]);

		nrf24_read(CONFIG,addres,1);
		printf("CONFIG = %d \n",addres[0]);
    }

    else {

    	printf("NRF24 slave initalize\n");

    	nrf24_read(CONFIG,addres,1);
		addres[0] |=  (1<<PRIM_RX)|(1<<EN_CRC); //set PWR_UP low //Set PRIME_RX high
		addres[0] &=  ~((1<<PWR_UP)|(1<<MASK_TX_DR)|(1<<MASK_TX_DS)|(1<<CRCO)); ;
		nrf24_write(CONFIG,addres,1);

		nrf24_read(CONFIG,addres,1);
		printf("CONFIG = %d \n",addres[0]);

    }



	addres[0] =  0xbb; //set pipe 0 to be 0x bbbb
	addres[1] =  0xbb;
	addres[2] =  0xbb;
	addres[3] =  0xbb;
	addres[4] =  0xbb;

	nrf24_write(TX_ADDR,addres,5);
	nrf24_write(RX_ADDR_P0,addres,5);

	nrf24_read(TX_ADDR,addres,5);
	printf("TX_ADDR = %d %d %d %d %d \n",addres[0],addres[1],addres[2],addres[3],addres[4]);

	nrf24_read(RX_ADDR_P0,addres,5);
	printf("RX_ADDR_P0 = %d %d %d %d %d \n",addres[0],addres[1],addres[2],addres[3],addres[4]);


	nrf24_read(RF_SETUP,addres,1); // set 250 kb and set db -18 db power saver
	addres[0] = 0x24;
	nrf24_write(RF_SETUP,addres,1);

	nrf24_read(RF_SETUP,addres,1);
	printf("RF_SETUP = %d \n",addres[0]);


	addres[0] = 0x11; //RF channel frequency = 2400 + 100
	nrf24_write(RF_CH,addres,1);

	nrf24_read(RF_CH,addres,1);
	printf("RF_CH = %d \n",addres[0]);

	addres[0] = (1<<EN_DPL)|(1<<EN_DYN_ACK);
	nrf24_write(FEATURE,addres,1);

	nrf24_read(FEATURE,addres,1);
	printf("FEATURE = %d \n",addres[0]);

	nrf24_read(DYNPD,addres,1);
	addres[0] |= (1<<DPL_P0);  // set DPL_P0 in PTX mode for DPL
	nrf24_write(DYNPD,addres,1);

	nrf24_read(DYNPD,addres,1);
	printf("DYNPD = %d \n",addres[0]);


	nrf24_read(EN_AA,addres,1);
	addres[0] |= (1<<ENAA_P0);  // enable auto acknowledgment
	nrf24_write(EN_AA,addres,1);

	nrf24_read(EN_AA,addres,1);
	printf("EN_AA = %d \n",addres[0]);

	//addres[0] = 0x2f;  // Auto retransmit Count 10 and waite in rx mode for 900 us
	//nrf24_write(SETUP_RETR,addres,1);

	nrf24_read(SETUP_RETR,addres,1);
	addres[0] |= 0x10;
	nrf24_write(SETUP_RETR,addres,1);
	nrf24_read(SETUP_RETR,addres,1);
	printf("SETUP_RETR = %d \n",addres[0]);


	addres[0] = 0x03;  // set address width
	nrf24_write(SETUP_AW,addres,1);

	nrf24_read(SETUP_AW,addres,1);
	printf("SETUP_AW = %d \n",addres[0]);

	nrf24_read(CONFIG,addres,1);
	addres[0] |= (1<<PWR_UP); //set PWR_UP high
	nrf24_write(CONFIG,addres,1);

	nrf24_read(CONFIG,addres,1);
	printf("CONFIG = %d \n",addres[0]);

	if(!ptype)
		nrf24_ce_high;

	//load TX_PLD
	//configer
}















