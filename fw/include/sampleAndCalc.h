/*
 * sampleAndCalc.h
 *
 *  Created on: Nov 27, 2010
 *      Author: johnz
 */

#ifndef SAMPLEANDCALC_H_
#define SAMPLEANDCALC_H_

void adc_fillSampleBuffer(void);
int getLightSample(void);
float getVoltage(void);
double convertRawSampleToLux(short int sample);
void sampleAndCalc(void);

#endif /* SAMPLEANDCALC_H_ */
