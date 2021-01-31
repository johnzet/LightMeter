/* ----------------------------------------------------------------------------
 *         Martin Thomas Software Engineering
 * ----------------------------------------------------------------------------
   Copyright (c) 2009, Martin Thomas (Skeleton from Atmel's Softpack 1.5 demos)

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------- */

#define VERSION_STRING "V1.1.9 9/2009"


//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include <string.h>

#include "board_memories.h"
#include "board.h"
#include "aic/aic.h"
#include "pio/pio.h"
#include "dbgu/dbgu.h"
#include "pit/pit.h"
#include "utility/assert.h"
#include "utility/led.h"
#include "utility/trace.h"

#include "diskio.h"
#include "ff_test_term.h"
#include "rtc.h"
#include "misc_test_term.h"

//------------------------------------------------------------------------------
//         Local types
//------------------------------------------------------------------------------
typedef enum { APPSTATE_FF_TERM, APPSTATE_TESTMENU } AppState;

//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------
static volatile uint32_t timestamp;
static volatile uint32_t second_tick;

//------------------------------------------------------------------------------
//         Local defines
//------------------------------------------------------------------------------
/// PIT period value in µseconds. - do not change
#define PIT_PERIOD          1000

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Handler for PIT interrupt. Increments the timestamp counter.
/// called every PIT_PERIOD
//------------------------------------------------------------------------------
__attribute__ ((section (".ramfunc")))  static void ISR_Pit(void)
{
	static unsigned int prescLED, prescDTP, mscount;
	unsigned int incr;

	// Read the PIT status register and handle if flag set
	if ( PIT_GetStatus() & AT91C_PITC_PITS ) {

		ff_test_term_timerproc(); /* <--- n.b.: for fat_test_term to be called every ms */

		if ( prescLED++ >= 500 ) {
			prescLED = 0;
			LED_Toggle(0);
		}

		if ( prescDTP++ >= 10 ) {
			prescDTP = 0;
			disk_timerproc(); /* <--- n.b.: for FAT-Module to be called every 10ms */
		}

		// Read the PIVR to acknowledge interrupt and get number of ticks
		incr = (PIT_GetPIVR() >> 20);

		// update timestamp
		timestamp += incr;

		// update second-counter
		mscount += incr;
		if ( mscount >= 1000) {
			second_tick++;
			mscount -= 1000;
		}
	}
}

//------------------------------------------------------------------------------
/// Configure the periodic interval timer to generate an interrupt every
/// millisecond.
//------------------------------------------------------------------------------
static void ConfigurePit(void)
{
    // Initialize the PIT to the desired frequency
    PIT_Init(PIT_PERIOD, BOARD_MCK / 1000000);

    // Configure interrupt on PIT
    AIC_DisableIT(AT91C_ID_SYS);
    AIC_ConfigureIT(AT91C_ID_SYS, AT91C_AIC_PRIOR_LOWEST, ISR_Pit);
    AIC_EnableIT(AT91C_ID_SYS);
    PIT_EnableIT();

    timestamp = 0;

    // Enable the pit
    PIT_Enable();
}

//------------------------------------------------------------------------------
/// Configure LEDs #1 and #2 (cleared by default).
//------------------------------------------------------------------------------
static void ConfigureLeds(void)
{
    LED_Configure(0);
    LED_Configure(1);
}

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

uint32_t RTC_GetCounter(void)
{
	return second_tick;
}

void RTC_SetCounter(uint32_t val)
{
	second_tick = val;
}

void delay_ms(uint32_t ms)
{
	uint32_t s, d;

	s = timestamp;
	do {
		d = (uint32_t)(timestamp - s);
	} while ( d < ms );
}

//------------------------------------------------------------------------------
/// Main function
//------------------------------------------------------------------------------
int main(void)
{
	AppState appState = APPSTATE_FF_TERM;
	// AppState appState = APPSTATE_TESTMENU;

	TRACE_CONFIGURE(DBGU_STANDARD, 115200, BOARD_MCK);

	printf("\nAT91SAM7S Demo Application by Martin Thomas\n" VERSION_STRING "\n");
	printf("-- Compiled: %s %s\n", __DATE__, __TIME__);
	printf("-- for Board " BOARD_NAME "\n");

#if 1
	BOARD_RemapFlash();
	if ( BOARD_GetRemap() ) {
		printf("-- re-mapped to RAM, o.k.\n");
	} else {
		printf("-- not re-mapped, re-mapping... ");
		AT91C_BASE_MC->MC_RCR = AT91C_MC_RCB;
		if ( BOARD_GetRemap() ) {
			printf("o.k.\n");
		} else {
			printf("failed\n");
		}
	}
#endif

	// Configuration
	ConfigureLeds();
	ConfigurePit();

	rtc_init();

	while ( 1 ) {
		switch ( appState ) {
			case APPSTATE_FF_TERM:
				/* ff_test_term is not reentrant, blocks until exit */
				if ( !ff_test_term() ) {
					appState = APPSTATE_TESTMENU;
				}
				break;
			case APPSTATE_TESTMENU:
				/* misc_test_term is fully reentrant, main-loop keeps running
				 * but may be throttled by time-consuming routines */
				if ( !misc_test_term() ) {
					appState = APPSTATE_FF_TERM;
				}
				break;
			default:
				appState = APPSTATE_TESTMENU;
				break;
		}
	}

	return 0;
}
