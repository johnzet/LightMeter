/* Martin Thomas 5/2009 */

#include <stdio.h>
#include "dbgu/dbgu.h"
#include "comm.h"

#define USARTx USART1

int comm_test (void)
{
	return DBGU_IsRxReady();
}

unsigned char comm_get (void)
{
	while( !comm_test() ) { ; }
	return DBGU_GetChar();
}

void comm_put (unsigned char d)
{
	DBGU_PutChar(d);
}

void comm_init (void)
{
	// already done in main.c
}


