/* 
 * File:   Usart.h
 * Author: giovanni
 *
 * Created on 8 novembre 2021, 15.30
 */

#ifndef USART_H
#define	USART_H

#include "includes.h"
/********************************** Macros **********************************/
#define UART_ENABLE_PORT() RCSTAbits.SPEN = 1
#define UART_DISABLE_PORT() RCSTAbits.SPEN = 0;
#define UART_ENABLE_TX() TXSTAbits.TXEN = 1;
#define UART_DISABLE_TX()  TXSTAbits.TXEN = 0
#define UART_ENABLE_RX() RCSTAbits.CREN = 1
#define UART_DISABLE_RX() RCSTAbits.CREN = 0

/**********************************DEFINES**********************************/

#define TX_shift_reg_empty TXSTAbits.TRMT
#define RX_INTERRUPT_FLAG PIR1bits.RCIF
#define RX_Framing_Error RCSTAbits.FERR
#define RX_Overrun_Error RCSTAbits.OERR
#define TX_INTERRUPT_ENABLE TXIE
#define RX_INTERRUPT_ENABLE RCIE
/**********************************CONSTANTS********************************/

#define _XTAL_FREQ 4000000
#define _BAUD_RATE 9600

void UART_init(void);
void UART_write(char c);
char UART_read(void);
_Bool UART_data_ready(void);
void UART_close(void);
_Bool UART_start_comm(void);
//void init_PORTS(void);

#endif	/* USART_H */



