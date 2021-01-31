#include <main.h>
#ifdef PRINTF_USES_USART
#include <stdio.h>          // printf goes to crossworks.c
#else
#include <__debug_stdio.h>  // printf goes to dbg
#endif
#include <math.h>

static double PI = 3.14159265359;
void fft(int n, double x[], double y[]);

void applyBlackmanWindowFunction() {
    // Blackman window
    // w(n)=0.42-0.5cos{(2*PI*n)/(N-1)}+0.08cos{(4*PI*n)/(N-1)};
    for (int i=0; i<ADC_SAMPLE_BUFFER_LENGTH; i++) {
        int n = ADC_SAMPLE_BUFFER_LENGTH;
        fftRe[i] = fftRe[i] *
            (0.42 - 0.5 * cos(2*PI*i/(n-1)) + 0.08 * cos(4*PI*i/(n-1)));
    }
}

double getBlackmanCoherentGain() {
    return 0.42;
}

void convertComplexBufferToScaledMagnitude() {
    for (int i=0; i<ADC_SAMPLE_BUFFER_LENGTH/2; i++) {
        double mag = hypot(fftRe[i], fftIm[i]);
        fftRe[i] = mag / (getBlackmanCoherentGain() * ADC_SAMPLE_BUFFER_LENGTH/2);
        fftIm[i] = 0;
    }
}

void getFundamentalIndex(void) {
    fundamentalMagnitude = 0.0;
    fundamentalFrequency = 0.0;
    totalMagnitude = 0.0;
    unsigned short fundamentalIndex = 0;
    for (int i=3; i<ADC_SAMPLE_BUFFER_LENGTH/2; i++) {
        if (fftRe[i] > fundamentalMagnitude) {
            fundamentalMagnitude = fftRe[i];
            fundamentalIndex = i;
        }
    }

    if (fundamentalMagnitude < 1.0) {
        fundamentalMagnitude = 0.0;
        fundamentalFrequency = 0.0;
        totalMagnitude = 0.0;
    }

    for (unsigned int harmonic = 1; harmonic <= 5; harmonic++) {

        if ((fundamentalIndex * harmonic) >= (ADC_SAMPLE_BUFFER_LENGTH/2 -1)) {
            break;
        }

        // parabolic interpolation of fundamental
        double y0 = fftRe[harmonic * (fundamentalIndex-1)];
        double y1 = fftRe[harmonic * (fundamentalIndex)];
        double y2 = fftRe[harmonic * (fundamentalIndex+1)];
        double freqOffset = 0.5*((y0-y2)/(y0-2*y1+y2));
        double mag = (pow(y0,2)-8*y0*y1-2*y0*y2+pow(y2,2)-8*y1*y2+16*pow(y1,2))/(-8*(y0-2*y1+y2));
        if (harmonic == 1) {
            fundamentalMagnitude = mag;
            // fundamental frequency = (sampleFreq/#samples) * FFT freqPt
            fundamentalFrequency = (((double)ADC_SAMPLING_FREQ)/((double)ADC_SAMPLE_BUFFER_LENGTH)) * (((double)fundamentalIndex) + freqOffset);
        }
        totalMagnitude += fabs(mag);
    }
}

double findAverage() {
    double sum = 0.0;
    for (int i=0; i<(ADC_SAMPLE_BUFFER_LENGTH/2); i++) {
        sum += fftRe[i];
    }
    return sum / (ADC_SAMPLE_BUFFER_LENGTH/2);
}

void normalizeTo(double average) {
    for (int i=0; i<ADC_SAMPLE_BUFFER_LENGTH; i++) {
        fftRe[i] -= average;
    }
}

void testFft() {
    // fill buffer
    for (int i=0; i<ADC_SAMPLE_BUFFER_LENGTH; i++) {
        double freq = 60.0;
        int n  = ADC_SAMPLING_FREQ / freq ;
        adcBuffer[i] = 511 + floor(50*fabs(sin((i%n)*2.0*PI/n)));
        sample[i] = adcBuffer[i]; //convertRawSampleToLux(adcBuffer[i]);
        fftRe[i] = sample[i];
        fftIm[i] = 0.0;
    }

    int average = findAverage();

    normalizeTo(average);

    applyBlackmanWindowFunction();

    // compute FFT
    printf("Starting FFT...\n");
    fft(ADC_SAMPLE_BUFFER_LENGTH, fftRe, fftIm);

    convertComplexBufferToScaledMagnitude();

    // get magnitude of FFT and find fundamental
    getFundamentalIndex();

    // show results
//    printf("Index   SampleRaw    SampleLux     FftReal      FftImaginary\n");
//    for(int i=0; i<ADC_SAMPLE_BUFFER_LENGTH/2; i++) {
//        printf("%i, %i, %f, %f, %f\n", i, adcBuffer[i], sample[i], fftRe[i], fftIm[i]);
//    }
    printf("\n\nFundamental peak of %f at %fHz\n",
        fundamentalMagnitude, fundamentalFrequency);

    printf("\nFundamental magnitude is %f%% of average (%f)\n",
        100 * fundamentalMagnitude / average, average);
    printf("\nTotal magnitude is %f%% of average (%f)\n",
        100 * totalMagnitude / average, average);
}

