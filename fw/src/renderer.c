/*
 * renderer.c
 *
 *  Created on: Nov 27, 2010
 *      Author: johnz
 */
#include <main.h>
#include <grapher.h>
#include "nokia_lcd_driver/nokialcd_driver.h"
#include "nokia_lcd_driver/nokialcd_font.h"


void _renderButtonBorder(int leftBG, int centerBG, int rightBG) {
    LCDFillBox(0x444,   0, 118,  41, 129);
    LCDFillBox(0x444,  44, 118,  85, 129);
    LCDFillBox(0x444,  88, 118, 129, 129);

    LCDFillBox(leftBG,     1, 119,  40, 128);
    LCDFillBox(centerBG,  45, 119,  84, 128);
    LCDFillBox(rightBG,   89, 119, 128, 128);
}

void renderHomeScreen() {
    int screenBG = 0xFFF;
    int leftBG = 0x888;
    int centerBG = 0x484;
    int rightBG = 0x844;
    LCDClearScreen(screenBG);
    _renderButtonBorder(leftBG, centerBG, rightBG);

    // buttons
    LCDDrawString("Run", 0x4F4, centerBG, 58, 120);
    LCDDrawString("Off", 0xF44, rightBG, 102, 120);

    // screen
    LCDDrawString("Light Meter", 0x000, screenBG, 30, 3);
    LCDDrawString("by", 0x000, screenBG, 57, 13);
    LCDDrawString("John Zehetner", 0x000, screenBG, 24, 23);

    LCDDrawString("Light intensity:", 0x000, screenBG, 0, 60);
}

void updateHomeScreen(float voltage, float lux, float percentRange) {
    int screenBG = 0xFFF;
    char buffer[30];

    sprintf(buffer, "Battery: %1.2fV", voltage);
    LCDDrawString(buffer, 0x000, screenBG, 0, 40);

    sprintf(buffer, "%.0f LUX      ", lux);
    LCDDrawString(buffer, 0x000, screenBG, 10, 70);

    sprintf(buffer, "(%.0f%% of Range)", percentRange);
    LCDDrawString(buffer, 0x000, screenBG, 10, 80);
}

void renderSimpleScreen(void) {
    int screenBG = 0xFFF;
    int leftBG = 0x888;
    int centerBG = 0x484;
    int rightBG = 0x844;
    LCDClearScreen(screenBG);
    _renderButtonBorder(leftBG, centerBG, rightBG);

    // buttons
    LCDDrawString("Page", 0x4F4, centerBG, 55, 120);
    LCDDrawString("Off", 0xF44, rightBG, 102, 120);

    // screen
    LCDDrawString("Sampling complete", 0x000, screenBG, 0, 3);

    char buffer[30];
    sprintf(buffer, "samples: %i", ADC_SAMPLE_BUFFER_LENGTH);
    LCDDrawString(buffer, 0x000, screenBG, 10, 10);

    sprintf(buffer, "rate: %ikHz", ADC_SAMPLING_FREQ/1000);
    LCDDrawString(buffer, 0x000, screenBG, 10, 20);

    if (fundamentalFrequency > 10.0 && fundamentalFrequency < (ADC_SAMPLING_FREQ / 2.0) && flickerPercent > 0.005) {
        LCDDrawString("Detected flicker:", 0x000, screenBG, 0, 40);

        LCDDrawString("Fundamental freq:", 0x000, screenBG, 0, 50);
        sprintf(buffer, "%.2fHz", fundamentalFrequency);
        LCDDrawString(buffer, 0x000, screenBG, 10, 60);

        LCDDrawString("Flicker percentage:", 0x000, screenBG, 0, 70);
        sprintf(buffer, "%.2f%%", flickerPercent);
        LCDDrawString(buffer, 0x000, screenBG, 10, 80);
    } else {
        LCDDrawString("No flicker detected", 0x000, screenBG, 0, 40);
    }
}

void renderGraphScreen(unsigned char domain, int pageIncrement) {
    LCDClearScreen(0x000);
    int leftBG = 0xDDD;
    int centerBG = 0x242;
    int rightBG = 0xDDD;
    _renderButtonBorder(leftBG, centerBG, rightBG);

    LCDDrawString("<<<", 0x000, leftBG, 5, 120);
    LCDDrawString("Page", 0x8F8, centerBG, 55, 120);
    LCDDrawString(">>>", 0x000, rightBG, 102, 120);

    renderGraph(domain, pageIncrement);
}
