/* Copyright (c) 2009, Martin Thomas, 3BSD-license */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "board.h"
#include "utility/led.h"

#include "main.h"
#include "comm.h"
#include "term_io.h"
#include "misc_test_term.h"
#include "rtc.h"
#include "ff.h"

#include "uart1.h"
#include "dcc_stdio.h"

// command-line input-buffer
#define INBUF_MAX 20
static char inbuf[INBUF_MAX];
static int inbuf_idx;

static void help(void)
{
	xputs("l              LED toggle\n");
	xputs("l 0|1          LED off/on\n");
	xputs("t              Show RTC time\n");
	xputs("t y m d h m s  Set RTC time\n");
	xputs("d              delay_ms test\n");
	xputs("u              uart1 echo test\n");
	xputs("c              DCC test\n");
	xputs("x              Exit\n");
}

bool misc_test_term(void)
{
	static bool notenter; /* inverted to avoid use of .data (here .bss) */
	static bool showprompt;
	bool retval;
	char *ptr;
	long p1; // , p2;
	RTC_t rtc;
	uint32_t i, s;

	retval = true;

	if (!notenter) {
		notenter = true;
		xputs("\nMisc test terminal (h for help)\n");
		inbuf_idx = 0;
		showprompt = true;
	}

	if (showprompt) {
		xputs(">");
		showprompt = false;
	}

	if (get_line_r(inbuf, INBUF_MAX, &inbuf_idx)) {
		ptr = inbuf;
		switch (*ptr++) {
		case 'x':
			notenter = false;
			retval = false;
			break;
		case 'h':
			help();
			break;
		case 'l':
			if (xatoi(&ptr, &p1)) {
				if (p1) {
					LED_Set(1);
				} else {
					LED_Clear(1);
				}
			} else {
				LED_Toggle(1);
			}
			break;
		case 'd':
			for (i = 0; i < 10; i++ ) {
				LED_Toggle(1);
				delay_ms(100);
				LED_Toggle(1);
				delay_ms(100);
			}
			break;
		case 't':
			if (xatoi(&ptr, &p1)) {
				rtc.year = (uint16_t) p1;
				xatoi(&ptr, &p1);
				rtc.month = (uint8_t) p1;
				xatoi(&ptr, &p1);
				rtc.mday = (uint8_t) p1;
				xatoi(&ptr, &p1);
				rtc.hour = (uint8_t) p1;
				xatoi(&ptr, &p1);
				rtc.min = (uint8_t) p1;
				if (!xatoi(&ptr, &p1))
					break;
				rtc.sec = (uint8_t) p1;
				rtc_settime(&rtc);
			}
			rtc_gettime(&rtc);
			xprintf("%u/%u/%u %02u:%02u:%02u\n", rtc.year, rtc.month, rtc.mday,
					rtc.hour, rtc.min, rtc.sec);
			break;
		case 'u':
			xprintf("UART1 echo, this blocks - send e to UART0 to exit");
			uart1_init( 115200, BOARD_MCK );
			i = 0;
			do {
				if (uart1_kbhit()) {
					i = uart1_getc();
					uart1_putc('<');
					uart1_putc(i);
					uart1_putc('>');
				}
				s = uart1_getstate();
				if ( s & UART_BUFFER_OVERFLOW ) {
					xprintf("Buffer overflow\n");
				}
				if ( s & UART_FRAME_ERROR ) {
					xprintf("Frame Error\n");
				}
				if ( s & UART_OVERRUN_ERROR ) {
					xprintf("Overrun Error\n");
				}
				delay_ms(100);
				xprintf(".");
			} while (i != 'e');
			xprintf("\n");
			break;
		case 'c':
			xprintf("enable OpenOCD: target_request debugmsgs enable \n");
			xprintf("enable gdb/OpenOCD: monitor target_request debugmsgs enable \n");
			xprintf("Send to DCC start\n");
			dbg_write_str("Hello World via DCC");
			xprintf("Send to DCC end\n");
			break;
		default:
			xprintf("syntax error\n");
			break;
		}
		inbuf_idx = 0;
		showprompt = true;
	}

	return retval;
}
