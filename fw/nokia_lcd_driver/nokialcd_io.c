#include "include/AT91SAM7X256.h"
/*
 * nokialcd_io.c
 *
 *  Created on: Dec 5, 2009
 *      Author: John Zehetner
 */

void LCDSend9Bit(unsigned int data){

  // Wait for the transfer to complete
  while((AT91C_BASE_SPI0->SPI_SR & AT91C_SPI_TXEMPTY) == 0);

  AT91C_BASE_SPI0->SPI_TDR = data;
}
