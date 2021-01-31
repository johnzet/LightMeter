#ifndef MAIN_H_
#define MAIN_H_

#define BOARD_ADC_FREQ              6000000
#define ADC_SAMPLING_FREQ           10000
#define ADC_LIGHT_CHANNEL           4
#define ADC_BAT_CHANNEL             5
#define ADC_SAMPLE_BUFFER_LENGTH    1024
// ADC reference voltage (ADVREF pin) - Reduced from 3.3v by leakage current through 1.5k filter resistor
#define ADVREF                      3.029

short int adcBuffer[ADC_SAMPLE_BUFFER_LENGTH];
double sample[ADC_SAMPLE_BUFFER_LENGTH];
double fftRe[ADC_SAMPLE_BUFFER_LENGTH];
double fftIm[ADC_SAMPLE_BUFFER_LENGTH];
unsigned int adcSampleIndex;

double fundamentalMagnitude;
double fundamentalFrequency;
double totalMagnitude;
double flickerPercent;

#ifdef PRINTF_USES_USART
#include <stdio.h>          // printf goes to crossworks.c
#else
#include <__debug_stdio.h>  // printf goes to dbg
#endif

#endif
