/*
 * uart1.c
 * AT91SAM USART driver with FIFO-Buffer (non PDC)
 *  Created on: 11.09.2009
 *      Author: Martin Thomas
 *              - partly inspired by Peter Fleury's AVR UART library (pre-GPL)
 *              - partly based on example-code from the Atmel at91lib
 *      License: 3BSD
 */


#include "board.h"
#include "pio/pio.h"
#include "pmc/pmc.h"
#include "aic/aic.h"
#include "uart1.h"

/// default timeout - just a loop counter no physical unit
#define UART1_TIMEOUT_DEFAULT  10000


#if UART1_WITH_FIFO

#define UART1_RX_BUFFER_MASK ( UART1_RX_BUFFER_SIZE - 1)
#define UART1_TX_BUFFER_MASK ( UART1_TX_BUFFER_SIZE - 1)

#if ( UART1_RX_BUFFER_SIZE & UART1_RX_BUFFER_MASK )
#error RX buffer size is not a power of 2
#endif
#if ( UART1_TX_BUFFER_SIZE & UART1_TX_BUFFER_MASK )
#error TX buffer size is not a power of 2
#endif

static volatile uint8_t  UART1_TxBuf[UART1_TX_BUFFER_SIZE];
static volatile uint8_t  UART1_RxBuf[UART1_RX_BUFFER_SIZE];
static volatile uint32_t UART1_TxHead;
static volatile uint32_t UART1_TxTail;
static volatile uint32_t UART1_RxHead;
static volatile uint32_t UART1_RxTail;
static volatile uint32_t UART1_LastRxError;

//------------------------------------------------------------------------------
/// Interrupt handler for USART1.
//------------------------------------------------------------------------------
void ISR_Usart1(void)
{
	uint32_t status, tmphead, data, lastRxError;

	lastRxError = UART1_LastRxError;
	status = AT91C_BASE_US1->US_CSR;

	if ((status & AT91C_US_FRAME) == AT91C_US_FRAME) {
		lastRxError |= UART_FRAME_ERROR;
		AT91C_BASE_US1->US_CR = AT91C_US_RSTSTA;
	}

	if ((status & AT91C_US_OVRE) == AT91C_US_OVRE) {
		lastRxError |= UART_OVERRUN_ERROR;
		AT91C_BASE_US1->US_CR = AT91C_US_RSTSTA;
	}

	if ((status & AT91C_US_RXBUFF) == AT91C_US_RXBUFF) {
		data = AT91C_BASE_US1->US_RHR;
		tmphead = (UART1_RxHead + 1) & UART1_RX_BUFFER_MASK;
		if (tmphead == UART1_RxTail) {
			lastRxError |= UART_BUFFER_OVERFLOW;
		} else {
			UART1_RxHead = tmphead;
			UART1_RxBuf[tmphead] = data;
		}
	}

	UART1_LastRxError = lastRxError;
}
#endif /* UART1_WITH_FIFO */

//------------------------------------------------------------------------------
/// Configures USART1.
/// \param baudrate     Baudrate at which the USART should operate (in Hz).
/// \param masterClock  Frequency of the system master clock (in Hz).
//------------------------------------------------------------------------------
void uart1_init(uint32_t bps, uint32_t mainclock)
{
	const Pin pins[] = {PIN_USART1_TXD, PIN_USART1_RXD};

	PIO_Configure(pins, PIO_LISTSIZE(pins));
	PMC_EnablePeripheral(AT91C_ID_US1);
	AT91C_BASE_US1->US_IDR = 0xFFFFFFFF;
	USART_Configure(AT91C_BASE_US1, USART_MODE_ASYNCHRONOUS, bps, mainclock);

#if UART1_WITH_FIFO
	UART1_TxHead = 0;
	UART1_TxTail = 0;
	UART1_RxHead = 0;
	UART1_RxTail = 0;
	UART1_LastRxError = 0;

	AIC_ConfigureIT(AT91C_ID_US1, 0, ISR_Usart1);
	AIC_EnableIT(AT91C_ID_US1);
	AT91C_BASE_US1->US_IER = AT91C_US_RXRDY | AT91C_US_FRAME | AT91C_US_OVRE;
#endif

	USART_SetTransmitterEnabled(AT91C_BASE_US1, 1);
	USART_SetReceiverEnabled(AT91C_BASE_US1, 1);
}

//------------------------------------------------------------------------------
/// Sends character to USART1, returns EOF on timeout or character on success.
/// \param c character to send.
//------------------------------------------------------------------------------
int uart1_putc(int c)
{
	uint32_t timeOut = UART1_TIMEOUT_DEFAULT;
	uint8_t c8;

	while ((AT91C_BASE_US1->US_CSR & AT91C_US_TXEMPTY) == 0) {
		if (timeOut == 0) {
			return EOF;
		}
		timeOut--;
	}

	c8 = (uint8_t)c;
	AT91C_BASE_US1->US_THR = c8;
	return c8;
}

//------------------------------------------------------------------------------
/// Reads character to USART1, returns EOF on timeout (no char)
/// or character on success.
//------------------------------------------------------------------------------
int uart1_getc(void)
{
	uint32_t timeOut = UART1_TIMEOUT_DEFAULT;
	int retval;

#if UART1_WITH_FIFO
	uint32_t tmptail;

	while (timeOut && (UART1_RxHead == UART1_RxTail)) {
		timeOut--;
	}

	if ( timeOut ) {
		// not time-outed - character in receive buffer
		tmptail = (UART1_RxTail + 1) & UART1_RX_BUFFER_MASK;
		UART1_RxTail = tmptail;
		retval = UART1_RxBuf[tmptail];
	} else {
		retval = EOF;
	}

#else
	while ( timeOut && (AT91C_BASE_US1->US_CSR & AT91C_US_RXRDY) == 0) {
		timeOut--;
	}

	if ( timeOut ) {
		retval = (uint8_t)AT91C_BASE_US1->US_RHR;
	} else {
		retval = EOF;
	}

#endif /* UART1_WITH_FIFO */

	return retval;
}

//------------------------------------------------------------------------------
/// Checks if character is available on USART1, returns nonzero if character
/// is available.
//------------------------------------------------------------------------------
int uart1_kbhit(void)
{
#if UART1_WITH_FIFO
	return (UART1_RxHead == UART1_RxTail) ? 0 : 1;
#else
	return (AT91C_BASE_US1->US_CSR & AT91C_US_RXRDY) ? 1 : 0;
#endif
}

//------------------------------------------------------------------------------
/// Get and reset UART1 status.
//------------------------------------------------------------------------------
uint32_t uart1_getstate(void)
{
	uint32_t retval;

	retval = UART1_LastRxError;
	UART1_LastRxError = 0;

	return retval;
}

