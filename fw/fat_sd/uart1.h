#ifndef UART1_H_
#define UART1_H_

#define UART1_WITH_FIFO  1

#include <stdint.h>
#include "usart/usart.h"

#ifndef EOF
#define EOF (-1)
#endif

#if UART1_WITH_FIFO
/// Size of the circular receive buffer, must be power of 2
#ifndef UART1_RX_BUFFER_SIZE
#define UART1_RX_BUFFER_SIZE 128
#endif
/// Size of the circular transmit buffer, must be power of
#ifndef UART1_TX_BUFFER_SIZE
#define UART1_TX_BUFFER_SIZE 128
#endif
#endif

/// error-codes returned by uart1_getstate
#define UART_FRAME_ERROR      0x0800              /* Framing Error by UART       */
#define UART_OVERRUN_ERROR    0x0400              /* Overrun condition by UART   */
#define UART_BUFFER_OVERFLOW  0x0200              /* receive ringbuffer overflow */


void uart1_init(uint32_t bps, uint32_t mainclock);
int uart1_putc(int c);
int uart1_getc(void);
int uart1_kbhit(void);
uint32_t uart1_getstate(void);

#endif /* UART1_H_ */
