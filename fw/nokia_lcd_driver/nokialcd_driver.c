#include "include/AT91SAM7X256.h"
#include "nokialcd_io.h"
#include "nokialcd_driver.h"
#include "nokialcd_controlcodes.h"
#include "nokialcd_font.h"

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif


//it's a simple delay
void Delay (unsigned long a) {

  volatile unsigned long d;

  d=a;
  while (--d!=0);
}

void LCDReset(void) {
    // reset the LCD
    Delay(1000);
    AT91C_BASE_PIOA->PIO_CODR   = 1<<2;     // Set PA2 to LOW
    Delay(1000);
    AT91C_BASE_PIOA->PIO_SODR   = 1<<2;     // Set PA2 to HIGH
    Delay(1000);
}

void configureLCD() {
    LCDReset();

    LCDCommand(EP_DISOFF);    // display off(EPSON)

    // Display control
    LCDCommand(EP_DISCTL);
    LCDData(0x0C); // P1: 0x00 = 2 divisions, switching period=8 (default)
    LCDData(0x20); // P2: 0x20 = nlines/4 - 1 = 132/4 - 1 = 32)
    LCDData(0x0C); // P3: 0x00 = no inversely highlighted lines
        LCDData(0x00);                        // dispersion

    // COM scan
    LCDCommand(EP_COMSCN);
    LCDData(1); // P1: 0x01 = Scan 1->80, 160<-81
    // Internal oscilator ON
    LCDCommand(EP_OSCON);
    // Sleep out
    LCDCommand(EP_SLPOUT);
    // Power control
    LCDCommand(EP_PWRCTR);
    LCDData(0x0f); // reference voltage regulator on, circuit voltage follower on, BOOST ON
    // Inverse display
    LCDCommand(EP_DISINV);
    // Data control
    LCDCommand(EP_DATCTL);
    LCDData(0x00); // P1: 0x01 = page address inverted, column address normal, address scan in column direction
    LCDData(0x00); // P2: 0x00 = RGB sequence (default value)
    LCDData(0x02); // P3: 0x02 = Grayscale -> 16 (selects 12-bit color, type A)
    // Voltage control (contrast setting)
    LCDCommand(EP_VOLCTR);
    LCDData(0x24); // P1 = 32 volume value (experiment with this value to get the best contrast)
    LCDData(0x3); // P2 = 3 resistance ratio (only value that works)


    LCDCommand(EP_NOP);    // nop(EPSON)

    LCDCommand(EP_PASET);   // page start/end ram
    LCDData(2);            // for some reason starts at 2
    LCDData(131);

    LCDCommand(EP_CASET);   // column start/end ram
    LCDData(0);
    LCDData(131);


    LCDCommand(EP_RAMWR);    // write some stuff (background)

    LCDCommand(EP_DISON);    // display on(EPSON)
}


static inline void LCDSetWindow(int x1, int y1, int x2, int y2) {
        LCDCommand(LCD_PASET);   // page start/end ram
        LCDData(y1 + LCD_Y_OFFSET);
        LCDData(y2 + LCD_Y_OFFSET);

        LCDCommand(LCD_CASET);   // column start/end ram
        LCDData(x1);
        LCDData(x2);
}

static inline void LCDBeginWrite() {
        LCDCommand(LCD_RAMWR);
}

void LCDWriteWindow(int x1, int y1, int x2, int y2) {
        LCDSetWindow(x1, y1, x2, y2);
        LCDBeginWrite();
}

inline void LCDWritePair(int c1, int c2) {
        LCDData(c1 >> 4);
        LCDData((c1<<4) | ((c2>>8) & 0x0f));
        LCDData(c2);
}

void LCDSetPixel(int color, int x, int y) {
        LCDWriteWindow(x, y, x, y);
        LCDWritePair(0, color);
}

void LCDDrawLine(int color, int x0, int y0, int x1, int y1) {

    int dy = y1 - y0;
    int dx = x1 - x0;
    int stepx, stepy;

    if (dy < 0) {
        dy = -dy;
        stepy = -1;
    } else {
        stepy = 1;
    }
    if (dx < 0) {
        dx = -dx;
        stepx = -1;
    } else {
        stepx = 1;
    }
    dy <<= 1;
    dx <<= 1;

    LCDSetPixel(color, x0, y0);
    if (dx > dy) {
        int fraction = dy - (dx >> 1);
        while (x0 != x1) {
            if (fraction >= 0) {
                y0 += stepy;
                fraction -= dx;
            }
            x0 += stepx;
            fraction += dy;
            LCDSetPixel(color, x0, y0);
        }
    } else {
        int fraction = dx - (dy >> 1);
        while (y0 != y1) {
            if (fraction >= 0) {
                x0 += stepx;
                fraction -= dy;
            }
            y0 += stepy;
            fraction += dx;
            LCDSetPixel(color, x0, y0);
        }
    }
}

void LCDFillBox(int color, int x1, int y1, int x2, int y2) {
        uint8_t c1 = color >> 4;
        uint8_t c2 = (color<<4) | ((color>>8) & 0x0f);
        uint8_t c3 = color;
        int num_words = ((x2-x1+1) * (y2-y1+1) + 1) / 2;

        LCDWriteWindow(x1, y1, x2, y2);
        for(int i=0; i<num_words; i++) {
                LCDData(c1);
                LCDData(c2);
                LCDData(c3);
        }
}

void LCDClearScreen(int color) {
        LCDFillBox(color, 0, 0, 129, 129);
}
