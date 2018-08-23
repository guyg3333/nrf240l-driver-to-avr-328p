/*
 * nrf2401.h
 *
 *  Created on: 19 срхїз 2016
 *      Author: etty
 */

#ifndef NRF2401_H_
#define NRF2401_H_

#include "usci.h"

/******************************************************************************/
/* Legacy Header File                                                         */
/* Not recommended for use in new projects.                                   */
/* Please use the msp430.h file or the device specific header file            */
/******************************************************************************/

/********************************************************************
*
* Standard register and bit definitions for the atmg328p microcontroller
*
* This file supports assembler and C development for
* atmg328p devices.
*
*
********************************************************************/












#define CONFIG        (0x00u)  /* Configeration Register  */

#define MASK_TX_DR	(6)
#define MASK_TX_DS	(5)
#define MASK_MAX_RT	(4)
#define EN_CRC		(3)
#define CRCO		(2)
#define PWR_UP		(1)
#define PRIM_RX		(0)




#define TX_ADDR		(0x10u)   /*Transmit address */




/************************************************************
* NRF24 spi interface commends
************************************************************/

#define NRF24_WRITE (6)
#define R_RX_PAYLOAD (0x61)
#define W_TX_PAYLOAD (0xa0)
#define R_RX_PL_WID (0x60)
#define W_ACK_PAYLOAD (0xa0)  // 1010PPP PIPE
#define FIFO_STATUS_comaand (0x11)
#define FLUSH_TX (0xE1)
#define FLUSH_RX (0xE2)
#define W_TX_PAYLOAD_NO_ACK (0xb0)





//#define nrf24_csn_low   (PORTB &= ~(1<<PB1))
//#define nrf24_csn_high  (PORTB |= (1<<PB1))
//#define nrf24_ce_low     (PORTB &= ~(1<<PB0))
//#define nrf24_ce_high    (PORTB |= (1<<PB0))

#define nrf24_csn_low   (PORTB &= ~(1<<PB0))
#define nrf24_csn_high  (PORTB |= (1<<PB0))
#define nrf24_ce_low     (PORTD &= ~(1<<PD7))
#define nrf24_ce_high    (PORTD |= (1<<PD7))




/************************************************************
* NRF24 Air data rate
************************************************************/

#define RF_SETUP      (0x06u)  /*   */
#define RF_PWR        (1)
#define RF_DR_HIGH    (3)
#define PLL_LOCK      (4)
#define RF_DR_LOW     (5)
#define CONT_WAVE     (7)


/************************************************************
* NRF24 RF channel frequency
************************************************************/

#define RF_CH      (0x05u)  /* */
#define rf_channel  (100) /* F_0 = 2400 + RF_CH */

/************************************************************
* NRF24 RF Dynamic Payload
************************************************************/

#define FEATURE (0x1du) /* */

#define EN_DYN_ACK    (0)
#define EN_ACK_PAY    (1)
#define EN_DPL        (2)

#define DYNPD (0x1cu) /* enable dynamic payload length*/
#define DPL_P0    (0)
#define DPL_P1    (1)
#define DPL_P2    (2)
#define DPL_P3    (3)
#define DPL_P4    (4)
#define DPL_P5    (5)

/************************************************************
* NRF24 Auto Acknowledgment
************************************************************/

#define EN_AA (0x01u) /* */
#define ENAA_P0    (0)
#define ENAA_P1    (1)
#define ENAA_P2    (2)
#define ENAA_P3    (3)
#define ENAA_P4    (4)
#define ENAA_P5    (5)

/************************************************************
* NRF24 Auto Retransmission
************************************************************/

#define SETUP_RETR (0x04u) /* */
#define ARD    (7)
#define ARC    (3)


/************************************************************
* NRF24 receive address data pipe
************************************************************/

#define RX_ADDR_P0 (0x0a)
#define RX_ADDR_P1 (0x0b)
#define RX_ADDR_P2 (0x0c)
#define RX_ADDR_P3 (0x0d)
#define RX_ADDR_P4 (0x0e)
#define RX_ADDR_P5 (0x0f)

void nrf24_read( unsigned char address, unsigned char *ptr, unsigned char bytes );
void nrf24_write( unsigned char address, unsigned char *ptr, unsigned char bytes );
void nrf24_read_rx( unsigned char *ptr, unsigned char bytes);
void nrf24_write_tx( unsigned char bytes, unsigned char *ptr );
void nrf24_master_initalize();
void nrf24_slave_initalize();
void nrf24_basic_slave_initalize();
void nrf24_basic_master_initalize();
void nrf24_initalize(unsigned char ptype);
unsigned char nrf24_get_payload_width();

/************************************************************
* NRF24 enable RX address data pipe
************************************************************/
#define EN_RXADDR (0x02)
#define ERX_P5	(5)
#define ERX_P4	(4)
#define ERX_P3	(3)
#define ERX_P2	(2)
#define ERX_P1	(1)
#define ERX_P0	(0)

/************************************************************
* NRF24 setup of address width
************************************************************/
#define SETUP_AW	(0x03)

/************************************************************
* NRF24 STAUS
************************************************************/
#define STATUS	(0x07u)
#define RX_DR	(6)
#define TX_DS	(5)
#define MAX_RT	(4)
#define RX_P_NO	(3)
#define TX_FULL	(0)

/************************************************************
* NRF24 FIFO_STATUS
************************************************************/
#define FIFO_STATUS	(0x17)
#define TX_REUSE	(6)
//#define TX_FULL		(5)
#define TX_EMPTY	(4)
#define RX_FULL		(1)
#define RX_EMPTY	(0)

/************************************************************
* NRF24 RX_PW_P0
************************************************************/

#define RX_PW_P0	(0x11)




#endif /* NRF2401_H_ */
