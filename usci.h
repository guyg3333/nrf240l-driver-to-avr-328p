/*
 * usci.h
 *
 *  Created on: 19 срхїз 2016
 *      Author: etty
 */

#ifndef USCI_H_
#define USCI_H_

#include <avr/io.h>
#include <util/delay.h>


void spi_masterInit(void);
void spi_transmit(unsigned char cData);
unsigned char spi_exchange( unsigned char data );
void spi_slaveInit(void);
unsigned char spi_slaveReceive(void);

#define   SPI     (DDRB)
#define   MOSI    (DDB3)
#define   MISO    (DDB4)
#define   SCK     (DDB5)


#define   CE      (PB1)
#define   CSN     (PB2)


#endif /* USCI_H_ */
