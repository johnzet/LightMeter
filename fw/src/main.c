
//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <board.h>
#include <AT91SAM7x256.h>
#include <main.h>
#include <pio/pio.h>
#include <usart/usart.h>
#include <adc/adc.h>
#include <tc/tc.h>
#include <ctl_api.h>
#include <assert.h>

#include "nokia_lcd_driver/nokialcd_driver.h"
#include "nokia_lcd_driver/nokialcd_font.h"

#include <FFT.h>
#include <peripherals.h>
#include <grapher.h>
#include <renderer.h>
#include <sampleAndCalc.h>

//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------
enum states {HOME, SAMPLE_AND_CALC, SIMPLE_SCREEN, TIME_SCREEN, FREQ_SCREEN, OFF};
unsigned int state = HOME;

// for button de-bouncing
float lastButtonPressTime = 0.0;
float lastScreenUpdateTime = 0.0;
unsigned char buttonsAreActive = 1;

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

void checkButtonState(void){
    unsigned int mask = BUTTON_LEFT | BUTTON_CENTER | BUTTON_RIGHT;
    unsigned char nonePressed = (AT91C_BASE_PIOA->PIO_PDSR & mask) == mask;

    if (nonePressed) {
        if (getTimerSeconds() - lastButtonPressTime > 0.2) {
            buttonsAreActive = 1;
        }
    } else {
        lastButtonPressTime = getTimerSeconds();
    }
}

unsigned char isLeftPressed(void) {
    unsigned char pressed = ((AT91C_BASE_PIOA->PIO_PDSR &  BUTTON_LEFT) == 0);
    if (pressed && buttonsAreActive) {
        buttonsAreActive = 0;
        return 1;
    }
    return 0;
}

unsigned char isCenterPressed(void) {
    unsigned char pressed = ((AT91C_BASE_PIOA->PIO_PDSR &  BUTTON_CENTER) == 0);
    if (pressed && buttonsAreActive) {
        buttonsAreActive = 0;
        return 1;
    }
    return 0;
}

unsigned char isRightPressed(void) {
    unsigned char pressed = ((AT91C_BASE_PIOA->PIO_PDSR &  BUTTON_RIGHT) == 0);
    if (pressed && buttonsAreActive) {
        buttonsAreActive = 0;
        return 1;
    }
    return 0;
}

void turnOn(void) {
     AT91C_BASE_PIOA->PIO_CODR = 1<<19;  // Set PA19 to LOW
}

void turnOff(void) {
    LCDReset();
    AT91C_BASE_PIOA->PIO_SODR = 1<<19;  // Set PA19 to HIGH
}

void turnLcdOn(void) {
    AT91C_BASE_PIOA->PIO_SODR = 1<<3;  // Set PA3 to HIGH
}

void turnLcdOff(void) {
    AT91C_BASE_PIOA->PIO_CODR = 1<<3;  // Set PA3 to LOW
}

void enableBatteryMeasurement(void) {
    AT91C_BASE_PIOA->PIO_CODR = 1<<4;  // Set PA4 to LOW
}

void disableBatteryMeasurement(void) {
    AT91C_BASE_PIOA->PIO_SODR = 1<<4;  // Set PA4 to HIGH
}


//------------------------------------------------------------------------------
//         MAIN
//------------------------------------------------------------------------------
int main(void)
{
//    testFft();

    configureBoard();
    turnOn();
    configureRTT();
    configureTc0();
    configureSPI();
    configureLCD();
    enableBatteryMeasurement();
    turnLcdOn();

    // print header
    printf("\n\n\n");
    printf("-- Light Meter by John Zehetner %s --\n", "V1.0");
    printf("-- %s\n", "Hardware: Olimex SAM7-EX256");
    printf("-- Compiled: %s %s --\n", __DATE__, __TIME__);

    state = HOME;
    renderHomeScreen();

    lastButtonPressTime = getTimerSeconds();
    lastScreenUpdateTime = getTimerSeconds();

    // main event loop
    while(1) {

        if (getTimerSeconds() - lastButtonPressTime > 60.0) {
            state = OFF;
        }

        checkButtonState();

        int sample;

        switch(state) {
          case(HOME):
            if (getTimerSeconds() - lastScreenUpdateTime > 0.5) {
                sample = getLightSample();
                double lux = convertRawSampleToLux(sample);
                float percentRange = sample/10.24;
                updateHomeScreen(getVoltage(), lux, percentRange);
                lastScreenUpdateTime = getTimerSeconds();
            }
            if (isCenterPressed()) {
                LCDDrawString("Sampling...", 0x000, 0xFFF, 40, 100);
                configureAdcLightBuffer();
                sampleAndCalc();
                renderSimpleScreen();
                state = SIMPLE_SCREEN;
            } else if (isRightPressed()) {
                state = OFF;
            }
            break;
          case(SAMPLE_AND_CALC):
            state = SIMPLE_SCREEN;
            renderSimpleScreen();
            if (isRightPressed()) {
                state = OFF;
            }
            break;
          case(SIMPLE_SCREEN):
            if (isCenterPressed()) {
                state = TIME_SCREEN;
                renderGraphScreen(TIME_DOMAIN, 0);
            } else if (isRightPressed()) {
                state = OFF;
            }
            break;
          case(TIME_SCREEN):
            if (isLeftPressed()) {
                renderGraphScreen(TIME_DOMAIN, -1);
            } else if (isCenterPressed()) {
                state = FREQ_SCREEN;
                renderGraphScreen(FREQUENCY_DOMAIN, 0);
            } else if (isRightPressed()) {
                renderGraphScreen(TIME_DOMAIN, 1);
            }
            break;
          case(FREQ_SCREEN):
            if (isLeftPressed()) {
                renderGraphScreen(FREQUENCY_DOMAIN, -1);
            } else if (isCenterPressed()) {
                state = SIMPLE_SCREEN;
                renderSimpleScreen();
            } else if (isRightPressed()) {
                renderGraphScreen(FREQUENCY_DOMAIN, 1);
            }
            break;
          case(OFF):
          default:
            turnLcdOff();
            disableBatteryMeasurement();
            turnOff();
            break;
        }
    }
}


