/*
 * peripherals.h
 *
 *  Created on: Nov 27, 2010
 *      Author: johnz
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

void configureBoard(void);

//------------------------------------------------------------------------------
/// Interrupt handler for the ADC. Signals that the conversion is finished by
/// setting a flag variable.
//------------------------------------------------------------------------------
void ISR_Adc(void);

//------------------------------------------------------------------------------
/// Configures Timer Counter 0 (TC0) to generate timing signals for the ADC.
//------------------------------------------------------------------------------
void configureTc0(void);

//------------------------------------------------------------------------------
/// Interrupt handler for USART0. Increments the number of bytes received in the
/// current second and starts another transfer if the desired bps has not been
/// met yet.
//------------------------------------------------------------------------------
/// Maximum Bytes Per Second (BPS) rate that will be forced using the CTS pin.
//#define MAX_BPS             500
//void ISR_Usart0(void);

//------------------------------------------------------------------------------
/// Configures USART0 in hardware handshaking mode, asynchronous, 8 bits, 1 stop
/// bit, no parity, 115200 baud and enables its transmitter and receiver.
//------------------------------------------------------------------------------
void configureUsart0(void);

void configureAdcSingleSample(unsigned char channel);

void configureAdcLightBuffer(void);

void configureRTT(void);

void configureSPI(void);

void configureLCD(void);

float getTimerSeconds(void);


#endif