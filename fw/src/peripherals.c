#include <board.h>
#include <AT91SAM7x256.h>
#include <main.h>
#include <pio/pio.h>
#include <usart/usart.h>
#include <adc/adc.h>
#include <tc/tc.h>
#include <ctl_api.h>
#include <assert.h>
#include <peripherals.h>


void configureBoard(void) {
    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_PIOA;
//    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_PIOB;

    // enable interrupts
    ctl_global_interrupts_enable();

#ifdef PRINTF_USES_USART
    // Configure USART0 and display startup trace
    configureUsart0();
#endif

    // Reset pin
    AT91C_BASE_PIOA->PIO_SODR   = 1<<2;     // Set PA2 to HIGH
    AT91C_BASE_PIOA->PIO_OER    = 1<<2;     // Configure PA2 as output

    // "On" pin
    AT91C_BASE_PIOA->PIO_CODR   = 1<<19;     // Set PA19 to LOW
    AT91C_BASE_PIOA->PIO_OER    = 1<<19;     // Configure PA19 as output
    
    // "LCD_BACK" pin
    AT91C_BASE_PIOA->PIO_CODR   = 1<<3;      // Set PA3 to LOW
    AT91C_BASE_PIOA->PIO_OER    = 1<<3;      // Configure PA3 as output

    // "BATSENSE" pin
    AT91C_BASE_PIOA->PIO_SODR   = 1<<4;      // Set PA4 to HIGH
    AT91C_BASE_PIOA->PIO_OER    = 1<<4;      // Configure PA4 as output
}

void configureSPI(void) {

    // chip select pin
    AT91C_BASE_PIOA->PIO_SODR   = 1<<12;     // Set PA12 to HIGH
    AT91C_BASE_PIOA->PIO_OER    = 1<<12;     // Configure PA12 as output

    // Init SPI0
    //set functionality to pins:
    //port0.12 -> NPCS0
    //port0.16 -> MISO
    //port0.17 -> MOSI
    //port0.18 -> SPCK
    AT91C_BASE_PIOA->PIO_PDR = 1<<12 | 1<<16 | 1<<17 | 1<<18;
    AT91C_BASE_PIOA->PIO_ASR = 1<<12 | 1<<16 | 1<<17 | 1<<18;
    AT91C_BASE_PIOA->PIO_BSR = 0;


    //enable the clock of SPI
    AT91C_BASE_PMC->PMC_PCER = 0x1 << AT91C_ID_SPI0;

    // SPI Control Register SPI_CR
    AT91C_BASE_SPI0->SPI_CR = AT91C_SPI_SWRST | AT91C_SPI_SPIEN; //Software reset, SPI Enable (0x81)
    AT91C_BASE_SPI0->SPI_CR = AT91C_SPI_SPIEN; //SPI Enable (0x01)
    // SPI Mode Register SPI_MR = 0xE0011
    AT91C_BASE_SPI0->SPI_MR =
      (AT91C_SPI_DLYBCS & (0 << 24)) | // Delay between chip selects (take default: 6 MCK // periods)
      (AT91C_SPI_PCS & (0xE << 16)) | // Peripheral Chip Select (selects SPI_NPCS0 or PA12)
      (AT91C_SPI_LLB & (0 << 7)) | // Local Loopback Enabled (disabled)
      (AT91C_SPI_MODFDIS & (1 << 4)) | // Mode Fault Detection (disabled)
      (AT91C_SPI_PCSDEC & (0 << 2)) | // Chip Select Decode (chip selects connected directly // to peripheral)
      (AT91C_SPI_PS & (0 << 1)) | // Peripheral Select (fixed)
      (AT91C_SPI_MSTR & (1 << 0)); // Master/Slave Mode (Master)
    // SPI Chip Select Register SPI_CSR[0] = 0x01010311
    AT91C_BASE_SPI0->SPI_CSR[0] =
      (AT91C_SPI_DLYBCT & (0x01 << 24)) | // Delay between Consecutive Transfers (32 MCK periods)
      (AT91C_SPI_DLYBS & (0x01 << 16)) | // Delay Before SPCK (1 MCK period)
      (AT91C_SPI_SCBR & (0x3 << 8)) | // Serial Clock Baud Rate (baudrate = MCK/3 = 48MHz/3 = 16Mhz)
      (AT91C_SPI_BITS & (AT91C_SPI_BITS_9)) | // Bits per Transfer (9 bits)
      (AT91C_SPI_CSAAT & (0x0 << 3)) | // Chip Select Active After Transfer
      (AT91C_SPI_NCPHA & (0x0 << 1)) | // Clock Phase (data captured on falling edge)
      (AT91C_SPI_CPOL & (0x01 << 0)); // Clock Polarity (inactive state is logic one)
}

//------------------------------------------------------------------------------
/// Interrupt handler for the ADC. Signals that the conversion is finished by
/// setting a flag variable.
//------------------------------------------------------------------------------
void ISR_Adc(void)
{
    adcBuffer[adcSampleIndex++] = ADC_GetConvertedData(AT91C_BASE_ADC, ADC_LIGHT_CHANNEL);
    if (adcSampleIndex >= ADC_SAMPLE_BUFFER_LENGTH) {
        AT91C_BASE_AIC->AIC_IDCR = 1 << AT91C_ID_ADC;
        TC_Stop(AT91C_BASE_TC0);
    } else {
//        ctl_global_interrupts_enable();
    }
}

//------------------------------------------------------------------------------
/// Configures Timer Counter 0 (TC0) to generate timing signals for the ADC.
//------------------------------------------------------------------------------
void configureTc0(void)
{
    unsigned int tcclks = 2; // MCK / 32
    unsigned int rc = 150;  // 100 us period

    // Enable TC0 peripheral clock
    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_TC0;

    // Disable TC clock
    AT91C_BASE_TC0->TC_CCR = AT91C_TC_CLKDIS;

    // Disable interrupts
    AT91C_BASE_TC0->TC_IDR = 0xFFFFFFFF;

    // Clear status register
    AT91C_BASE_TC0->TC_SR;

    // Set mode
    AT91C_BASE_TC0->TC_CMR = tcclks | AT91C_TC_WAVESEL_UP_AUTO
                  | AT91C_TC_WAVE | AT91C_TC_ACPA_SET | AT91C_TC_ACPC_CLEAR;

    // set RC compare
    AT91C_BASE_TC0->TC_RC = rc;
    AT91C_BASE_TC0->TC_RA = rc/2;

    // TIOA0 output to PB23 for a test point
    AT91C_BASE_PIOB->PIO_ASR    = 1<<23;
    AT91C_BASE_PIOB->PIO_PDR    = 1<<23;
    AT91C_BASE_PIOB->PIO_MDER    = 1<<23;
}

//------------------------------------------------------------------------------
/// Interrupt handler for USART0. Increments the number of bytes received in the
/// current second and starts another transfer if the desired bps has not been
/// met yet.
//------------------------------------------------------------------------------
/// Maximum Bytes Per Second (BPS) rate that will be forced using the CTS pin.
//#define MAX_BPS             500
//void ISR_Usart0(void)
//{
//    unsigned int status;
//
//    // Read USART status
//    status = AT91C_BASE_US0->US_CSR;
//
//    // Receive buffer is full
//    if ((status & AT91C_US_RXBUFF) == AT91C_US_RXBUFF) {
//
//        bytesReceived += BUFFER_SIZE;
//
//        // Restart transfer if BPS is not high enough
//        if (bytesReceived < MAX_BPS) {
//
//            USART_ReadBuffer(AT91C_BASE_US0, pBuffer, BUFFER_SIZE);
//        }
//        // Otherwise disable interrupt
//        else {
//
//            AT91C_BASE_US0->US_IDR = AT91C_US_RXBUFF;
//        }
//    }
//}

#ifdef PRINTF_USES_USART
//------------------------------------------------------------------------------
/// Configures USART0 in hardware handshaking mode, asynchronous, 8 bits, 1 stop
/// bit, no parity, 115200 baud and enables its transmitter and receiver.
//------------------------------------------------------------------------------
void configureUsart0(void)
{
    unsigned int mode = AT91C_US_NBSTOP_1_BIT
                        | AT91C_US_PAR_NONE
                        | AT91C_US_CHRL_8_BITS
                        | AT91C_US_CLKS_CLOCK
                        | AT91C_US_USMODE_NORMAL;

    // Enable the peripheral clock in the PMC
    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_US0;

    // Enable tx and rx pins
    AT91C_BASE_PIOA->PIO_PDR    = AT91C_PA0_RXD0 | AT91C_PA1_TXD0;
    AT91C_BASE_PIOA->PIO_ASR    = AT91C_PA0_RXD0 | AT91C_PA1_TXD0;
    AT91C_BASE_PIOA->PIO_PPUDR  = AT91C_PA0_RXD0 | AT91C_PA1_TXD0;

    // Reset and disable receiver & transmitter
    AT91C_BASE_US0->US_CR = AT91C_US_RSTRX | AT91C_US_RSTTX
                   | AT91C_US_RXDIS | AT91C_US_TXDIS;

    // Configure mode
    AT91C_BASE_US0->US_MR = mode;

    // disable all interrupts
    AT91C_BASE_US0->US_IDR = 0xFFFFFFFF;

    // Configure baudrate
    AT91C_BASE_US0->US_BRGR = (BOARD_MCK / 115200) / 16;

    // Enable receiver & transmitter
    USART_SetTransmitterEnabled(AT91C_BASE_US0, 1);
    USART_SetReceiverEnabled(AT91C_BASE_US0, 1);
}
#endif

void configureAdcLightBuffer(void) {

    // turn on the adc clock
    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_ADC;

    // reset adc
    AT91C_BASE_ADC->ADC_CR = AT91C_ADC_SWRST;

    ADC_Initialize( AT91C_BASE_ADC,
                    AT91C_ID_ADC,
                    AT91C_ADC_TRGEN_EN,
                    AT91C_ADC_TRGSEL_TIOA0,
                    AT91C_ADC_SLEEP_NORMAL_MODE,
                    AT91C_ADC_LOWRES_10_BIT,
                    BOARD_MCK,
                    BOARD_ADC_FREQ,
                    10,
                    1200);

    // Disable the interrupt first
    AT91C_BASE_AIC->AIC_IDCR = 1 << AT91C_ID_ADC;

    // Configure mode and handler
    AT91C_BASE_AIC->AIC_SMR[AT91C_ID_ADC] = AT91C_AIC_SRCTYPE_INT_POSITIVE_EDGE | 4;
    AT91C_BASE_AIC->AIC_SVR[AT91C_ID_ADC] = (unsigned int)ISR_Adc;

    // Clear interrupt
    AT91C_BASE_AIC->AIC_ICCR = 1 << AT91C_ID_ADC;

    // channel enable
    AT91C_BASE_ADC->ADC_CHER = (1 << ADC_LIGHT_CHANNEL);

    // enable interrupt
    AT91C_BASE_AIC->AIC_IECR = 1 << AT91C_ID_ADC;

    // enable the ADC EOC interrupt
    AT91C_BASE_ADC->ADC_IDR = 0xFFFFFFFF;
    AT91C_BASE_ADC->ADC_IER = 1 << ADC_LIGHT_CHANNEL;
}

void configureAdcSingleSample(unsigned char channel) {


    // turn on the adc clock
    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_ADC;

    // reset adc
    AT91C_BASE_ADC->ADC_CR = AT91C_ADC_SWRST;

    ADC_Initialize( AT91C_BASE_ADC,
                    AT91C_ID_ADC,
                    AT91C_ADC_TRGEN_DIS,
                    AT91C_ADC_TRGSEL_TIOA0,
                    AT91C_ADC_SLEEP_NORMAL_MODE,
                    AT91C_ADC_LOWRES_10_BIT,
                    BOARD_MCK,
                    BOARD_ADC_FREQ,
                    10,
                    1200);

    // Disable the interrupt
    AT91C_BASE_AIC->AIC_IDCR = 1 << AT91C_ID_ADC;

    // Clear interrupt
    AT91C_BASE_AIC->AIC_ICCR = 1 << AT91C_ID_ADC;

    // channel enable
    AT91C_BASE_ADC->ADC_CHER = (1 << channel);
}

void configureRTT(void) {
    // tenths of a second timer
    unsigned int prescale = 3277; // 32768 / 10 rounded to nearest int
    AT91C_BASE_RTTC->RTTC_RTMR = prescale  | AT91C_RTTC_RTTRST;
}

// Returns seconds with tenth second precision
float getTimerSeconds(void) {
    return AT91C_BASE_RTTC->RTTC_RTVR / 10.0;
}

