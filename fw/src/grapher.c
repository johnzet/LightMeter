#include <main.h>
#include "nokia_lcd_driver/nokialcd_driver.h"
#include "nokia_lcd_driver/nokialcd_font.h"
#include <grapher.h>
#include <renderer.h>

#ifdef PRINTF_USES_USART
#include <stdio.h>          // printf goes to crossworks.c
#else
#include <__debug_stdio.h>  // printf goes to dbg
#endif



void renderAxes(char unsigned domain, int page) {
//    int bg = 0x000;
    int fg = 0xFFF;

    // "y" axis
    LCDDrawLine(fg, 10, 10, 10, 106);
    LCDDrawLine(fg, 10, 10, 12, 13);
    LCDDrawLine(fg, 10, 10, 8, 13);

    // "x" axis
    LCDDrawLine(fg, 9, 106, 129, 106);
    LCDDrawLine(fg, 126, 104, 129, 106);
    LCDDrawLine(fg, 126, 108, 129, 106);

    // draw x-axis tick marks
    for (int i=0; i<=11; i++) {
        LCDDrawLine(
            0xF00,
            i * 10 + 10,
            (i == 5 || i == 10)? 102 : 104,
            i * 10 + 10,
            108);
    }

    // vertical markers for 60Hz and 120Hz
//    if (domain == FREQUENCY_DOMAIN && page == 0) {
//        int x60Hz = 6; // 5kHz over 512 buckets
//        int x120Hz = 2 * x60Hz;
//        LCDDrawLine(0x088, x60Hz + 10, 10, x60Hz + 10, 104);
//        LCDDrawLine(0x088, x120Hz + 10, 10, x60Hz + 10, 104);
//    }
}

void labelAxes(char unsigned domain, int page) {
    int bg = 0x000;
    int fg = 0xFFF;
    char buffer[10];

    // "y" axis
    LCDDrawString("0", fg, bg, 2, 97);

    // "x" axis
    if (domain == TIME_DOMAIN) {
        sprintf(buffer, "%imS", page * 20);
        LCDDrawString(buffer, fg, bg, 10, 108);
        sprintf(buffer, "%imS", page * 20 + 10);
        LCDDrawString(buffer, fg, bg, 45, 108);
        sprintf(buffer, "%imS", page * 20 + 20);
        LCDDrawString(buffer, fg, bg, 95, 108);
    } else { // freq domain
        sprintf(buffer, "%ikHz", page);
        LCDDrawString(buffer, fg, bg, 10, 108);
        sprintf(buffer, "%.1fkHz", page + 0.5);
        LCDDrawString(buffer, fg, bg, 45, 108);
        sprintf(buffer, "%ikHz", page + 1);
        LCDDrawString(buffer, fg, bg, 95, 108);
    }
}
void renderGraph(unsigned char domain, int pageIncrement) {
    int bg = 0x000;
    int fg = 0xFFF;

    static int page;
    if (pageIncrement == 0) {
        page = 0;
    } else {
        page += pageIncrement;
        if (page < 0) {
            page = 0;
        } else if (page > 4) {
            page = 4;
        }
    }

    // title
    if (domain == TIME_DOMAIN) {
        LCDDrawString("Time Domain", fg, bg, 30, 1);
    } else {
        LCDDrawString("Frequency Domain", fg, bg, 15, 1);
    }

    renderAxes(domain, page);
    labelAxes(domain, page);

    int lastX = 0;
    int lastY = 0;

    double fftPeakVal = 0;
    if (domain == FREQUENCY_DOMAIN) {
        // find the FFT data peak value
        for (int i=0; i<ADC_SAMPLE_BUFFER_LENGTH/2; i++) {
            if (fftRe[i] > fftPeakVal) {
                fftPeakVal = fftRe[i];
            }
        }
    }

    for (int i=0; i<120; i++) {
        if (page == 4 && i >= 100) {
            // at the end of the buffer
            break;
        }
        int x = i + 10;
        int y = 0;
        if (domain == TIME_DOMAIN) {
            y = adcBuffer[i * 2 + (page * 100)] * 95.0 / 1024.0;
        } else {
            y = fftRe[i + (page * 100)] * 95.0 / fftPeakVal;
            if (y > 95) {
                y = 95;
            }
        }
        if (lastX > 0 && lastY > 0) {
            LCDDrawLine(fg, lastX, 106 - lastY, x, 106 - y);
        }
        lastX = x;
        lastY = y;
    }
}

