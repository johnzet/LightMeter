#include <main.h>
#include <board.h>
#include <peripherals.h>
#include <FFT_Util.h>
#include <tc/tc.h>
#include <math.h>

void fft(int n, double x[], double y[]);

/*
 * sampleAndCalc.c
 *
 *  Created on: Nov 27, 2010
 *      Author: johnz
 */

void adc_fillSampleBuffer(void) {

    configureAdcLightBuffer();

    adcSampleIndex = 0;

    TC_Start(AT91C_BASE_TC0);

    unsigned int counter = 0;
    while (adcSampleIndex < ADC_SAMPLE_BUFFER_LENGTH) {
        // continue to wait for samples to come in
        counter++;
    }
    counter++;

}

void printSampleBuffer(void) {
    printf("\nSample, Value\n");

    for (int i=0; i<ADC_SAMPLE_BUFFER_LENGTH; i++) {
        printf("%i,      %i\n", i, adcBuffer[i]);
    }
}
int getAdcSample(int channel) {
    configureAdcSingleSample(channel);

    // Start ADC conversion
    AT91C_BASE_ADC->ADC_CR = AT91C_ADC_START;

    /* Wait for the conversion to complete*/
    while ((AT91C_BASE_ADC->ADC_SR & (1<<channel | AT91C_ADC_DRDY )) == 0);
    return  AT91C_BASE_ADC->ADC_LCDR;
}

int getLightSample(void) {
    return getAdcSample(ADC_LIGHT_CHANNEL);
}

float getVoltage(void) {
    int sample = getAdcSample(ADC_BAT_CHANNEL);
    return (sample/1024.0) * ADVREF;
}

double convertRawSampleToLux(short int sample) {
    // rLoad of 56k gives a line from 0.55V@10LUX to 2.8V@100kLUX
    double rLoad = 56000.0;

    double sampleV = ADVREF * (sample /1024.0);  // ADVREF ref, 10-bit ADC, 56k rLoad, max 50uA
    double sampleI = sampleV / rLoad;

    // Derived from the Avago APDS-9007 data sheet:
    double sampleLux = pow(10, sampleI / 1e-5);

    return sampleLux;
}

void sampleAndCalc(void) {
    // fill buffer
    adc_fillSampleBuffer();

    for (int i=0; i<ADC_SAMPLE_BUFFER_LENGTH; i++) {
        sample[i] = convertRawSampleToLux(adcBuffer[i]);
        fftRe[i] = sample[i];
        fftIm[i] = 0.0;
    }

    double average = findAverage();

    normalizeTo(average);

    applyBlackmanWindowFunction();

    // compute fft
    printf("Starting FFT...\n");
    fft(ADC_SAMPLE_BUFFER_LENGTH, fftRe, fftIm);

    convertComplexBufferToScaledMagnitude();

    // get magnitude of FFT and find fundamental
    getFundamentalIndex();

    flickerPercent = 100.0 * totalMagnitude / average;

    // show results
//    printf("Index   SampleRaw    SampleLux     FftReal      FftImaginary\n");
//    for(int i=0; i<ADC_SAMPLE_BUFFER_LENGTH/2; i++) {
//        printf("%i, %i, %f, %f, %f\n", i, adcBuffer[i], sample[i], fftRe[i], fftIm[i]);
//    }
//    printf("\n\nFundamental peak of %f at %fHz\n",
//        fundamentalMagnitude, fundamentalFrequency);
//
//    printf("\nFundamental magnitude is %f%% of average (%f)\n",
//        100 * fundamentalMagnitude / average, average);
//    printf("\nTotal magnitude is %f%% of average (%f)\n",
//        100 * totalMagnitude / average, average);
}

