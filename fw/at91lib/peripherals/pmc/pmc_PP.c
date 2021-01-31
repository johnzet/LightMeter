# 1 "C:/projects/Crossworks/HelloWorld/at91lib/peripherals/pmc/pmc.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:/projects/Crossworks/HelloWorld/at91lib/peripherals/pmc/pmc.c"
# 34 "C:/projects/Crossworks/HelloWorld/at91lib/peripherals/pmc/pmc.c"
# 1 "C:/projects/Crossworks/HelloWorld/at91lib/peripherals/pmc/pmc.h" 1
# 47 "C:/projects/Crossworks/HelloWorld/at91lib/peripherals/pmc/pmc.h"
extern void PMC_DisableProcessorClock(void);
extern void PMC_EnablePeripheral(unsigned int id);
extern void PMC_DisablePeripheral(unsigned int id);
extern void PMC_CPUInIdleMode(void);


extern void PMC_EnableAllPeripherals(void);

extern void PMC_DisableAllPeripherals(void);

extern unsigned int PMC_IsAllPeriphEnabled(void);

extern unsigned int PMC_IsPeriphEnabled(unsigned int id);
# 35 "C:/projects/Crossworks/HelloWorld/at91lib/peripherals/pmc/pmc.c" 2
# 1 "include/board.h" 1
# 65 "include/board.h"
# 1 "./include/AT91SAM7X256.h" 1
# 49 "./include/AT91SAM7X256.h"
typedef volatile unsigned int AT91_REG;




typedef struct _AT91S_SYS {
 AT91_REG AIC_SMR[32];
 AT91_REG AIC_SVR[32];
 AT91_REG AIC_IVR;
 AT91_REG AIC_FVR;
 AT91_REG AIC_ISR;
 AT91_REG AIC_IPR;
 AT91_REG AIC_IMR;
 AT91_REG AIC_CISR;
 AT91_REG Reserved0[2];
 AT91_REG AIC_IECR;
 AT91_REG AIC_IDCR;
 AT91_REG AIC_ICCR;
 AT91_REG AIC_ISCR;
 AT91_REG AIC_EOICR;
 AT91_REG AIC_SPU;
 AT91_REG AIC_DCR;
 AT91_REG Reserved1[1];
 AT91_REG AIC_FFER;
 AT91_REG AIC_FFDR;
 AT91_REG AIC_FFSR;
 AT91_REG Reserved2[45];
 AT91_REG DBGU_CR;
 AT91_REG DBGU_MR;
 AT91_REG DBGU_IER;
 AT91_REG DBGU_IDR;
 AT91_REG DBGU_IMR;
 AT91_REG DBGU_CSR;
 AT91_REG DBGU_RHR;
 AT91_REG DBGU_THR;
 AT91_REG DBGU_BRGR;
 AT91_REG Reserved3[7];
 AT91_REG DBGU_CIDR;
 AT91_REG DBGU_EXID;
 AT91_REG DBGU_FNTR;
 AT91_REG Reserved4[45];
 AT91_REG DBGU_RPR;
 AT91_REG DBGU_RCR;
 AT91_REG DBGU_TPR;
 AT91_REG DBGU_TCR;
 AT91_REG DBGU_RNPR;
 AT91_REG DBGU_RNCR;
 AT91_REG DBGU_TNPR;
 AT91_REG DBGU_TNCR;
 AT91_REG DBGU_PTCR;
 AT91_REG DBGU_PTSR;
 AT91_REG Reserved5[54];
 AT91_REG PIOA_PER;
 AT91_REG PIOA_PDR;
 AT91_REG PIOA_PSR;
 AT91_REG Reserved6[1];
 AT91_REG PIOA_OER;
 AT91_REG PIOA_ODR;
 AT91_REG PIOA_OSR;
 AT91_REG Reserved7[1];
 AT91_REG PIOA_IFER;
 AT91_REG PIOA_IFDR;
 AT91_REG PIOA_IFSR;
 AT91_REG Reserved8[1];
 AT91_REG PIOA_SODR;
 AT91_REG PIOA_CODR;
 AT91_REG PIOA_ODSR;
 AT91_REG PIOA_PDSR;
 AT91_REG PIOA_IER;
 AT91_REG PIOA_IDR;
 AT91_REG PIOA_IMR;
 AT91_REG PIOA_ISR;
 AT91_REG PIOA_MDER;
 AT91_REG PIOA_MDDR;
 AT91_REG PIOA_MDSR;
 AT91_REG Reserved9[1];
 AT91_REG PIOA_PPUDR;
 AT91_REG PIOA_PPUER;
 AT91_REG PIOA_PPUSR;
 AT91_REG Reserved10[1];
 AT91_REG PIOA_ASR;
 AT91_REG PIOA_BSR;
 AT91_REG PIOA_ABSR;
 AT91_REG Reserved11[9];
 AT91_REG PIOA_OWER;
 AT91_REG PIOA_OWDR;
 AT91_REG PIOA_OWSR;
 AT91_REG Reserved12[85];
 AT91_REG PIOB_PER;
 AT91_REG PIOB_PDR;
 AT91_REG PIOB_PSR;
 AT91_REG Reserved13[1];
 AT91_REG PIOB_OER;
 AT91_REG PIOB_ODR;
 AT91_REG PIOB_OSR;
 AT91_REG Reserved14[1];
 AT91_REG PIOB_IFER;
 AT91_REG PIOB_IFDR;
 AT91_REG PIOB_IFSR;
 AT91_REG Reserved15[1];
 AT91_REG PIOB_SODR;
 AT91_REG PIOB_CODR;
 AT91_REG PIOB_ODSR;
 AT91_REG PIOB_PDSR;
 AT91_REG PIOB_IER;
 AT91_REG PIOB_IDR;
 AT91_REG PIOB_IMR;
 AT91_REG PIOB_ISR;
 AT91_REG PIOB_MDER;
 AT91_REG PIOB_MDDR;
 AT91_REG PIOB_MDSR;
 AT91_REG Reserved16[1];
 AT91_REG PIOB_PPUDR;
 AT91_REG PIOB_PPUER;
 AT91_REG PIOB_PPUSR;
 AT91_REG Reserved17[1];
 AT91_REG PIOB_ASR;
 AT91_REG PIOB_BSR;
 AT91_REG PIOB_ABSR;
 AT91_REG Reserved18[9];
 AT91_REG PIOB_OWER;
 AT91_REG PIOB_OWDR;
 AT91_REG PIOB_OWSR;
 AT91_REG Reserved19[341];
 AT91_REG PMC_SCER;
 AT91_REG PMC_SCDR;
 AT91_REG PMC_SCSR;
 AT91_REG Reserved20[1];
 AT91_REG PMC_PCER;
 AT91_REG PMC_PCDR;
 AT91_REG PMC_PCSR;
 AT91_REG Reserved21[1];
 AT91_REG PMC_MOR;
 AT91_REG PMC_MCFR;
 AT91_REG Reserved22[1];
 AT91_REG PMC_PLLR;
 AT91_REG PMC_MCKR;
 AT91_REG Reserved23[3];
 AT91_REG PMC_PCKR[4];
 AT91_REG Reserved24[4];
 AT91_REG PMC_IER;
 AT91_REG PMC_IDR;
 AT91_REG PMC_SR;
 AT91_REG PMC_IMR;
 AT91_REG Reserved25[36];
 AT91_REG RSTC_RCR;
 AT91_REG RSTC_RSR;
 AT91_REG RSTC_RMR;
 AT91_REG Reserved26[5];
 AT91_REG RTTC_RTMR;
 AT91_REG RTTC_RTAR;
 AT91_REG RTTC_RTVR;
 AT91_REG RTTC_RTSR;
 AT91_REG PITC_PIMR;
 AT91_REG PITC_PISR;
 AT91_REG PITC_PIVR;
 AT91_REG PITC_PIIR;
 AT91_REG WDTC_WDCR;
 AT91_REG WDTC_WDMR;
 AT91_REG WDTC_WDSR;
 AT91_REG Reserved27[5];
 AT91_REG VREG_MR;
} AT91S_SYS, *AT91PS_SYS;





typedef struct _AT91S_AIC {
 AT91_REG AIC_SMR[32];
 AT91_REG AIC_SVR[32];
 AT91_REG AIC_IVR;
 AT91_REG AIC_FVR;
 AT91_REG AIC_ISR;
 AT91_REG AIC_IPR;
 AT91_REG AIC_IMR;
 AT91_REG AIC_CISR;
 AT91_REG Reserved0[2];
 AT91_REG AIC_IECR;
 AT91_REG AIC_IDCR;
 AT91_REG AIC_ICCR;
 AT91_REG AIC_ISCR;
 AT91_REG AIC_EOICR;
 AT91_REG AIC_SPU;
 AT91_REG AIC_DCR;
 AT91_REG Reserved1[1];
 AT91_REG AIC_FFER;
 AT91_REG AIC_FFDR;
 AT91_REG AIC_FFSR;
} AT91S_AIC, *AT91PS_AIC;
# 261 "./include/AT91SAM7X256.h"
typedef struct _AT91S_PDC {
 AT91_REG PDC_RPR;
 AT91_REG PDC_RCR;
 AT91_REG PDC_TPR;
 AT91_REG PDC_TCR;
 AT91_REG PDC_RNPR;
 AT91_REG PDC_RNCR;
 AT91_REG PDC_TNPR;
 AT91_REG PDC_TNCR;
 AT91_REG PDC_PTCR;
 AT91_REG PDC_PTSR;
} AT91S_PDC, *AT91PS_PDC;
# 284 "./include/AT91SAM7X256.h"
typedef struct _AT91S_DBGU {
 AT91_REG DBGU_CR;
 AT91_REG DBGU_MR;
 AT91_REG DBGU_IER;
 AT91_REG DBGU_IDR;
 AT91_REG DBGU_IMR;
 AT91_REG DBGU_CSR;
 AT91_REG DBGU_RHR;
 AT91_REG DBGU_THR;
 AT91_REG DBGU_BRGR;
 AT91_REG Reserved0[7];
 AT91_REG DBGU_CIDR;
 AT91_REG DBGU_EXID;
 AT91_REG DBGU_FNTR;
 AT91_REG Reserved1[45];
 AT91_REG DBGU_RPR;
 AT91_REG DBGU_RCR;
 AT91_REG DBGU_TPR;
 AT91_REG DBGU_TCR;
 AT91_REG DBGU_RNPR;
 AT91_REG DBGU_RNCR;
 AT91_REG DBGU_TNPR;
 AT91_REG DBGU_TNCR;
 AT91_REG DBGU_PTCR;
 AT91_REG DBGU_PTSR;
} AT91S_DBGU, *AT91PS_DBGU;
# 354 "./include/AT91SAM7X256.h"
typedef struct _AT91S_PIO {
 AT91_REG PIO_PER;
 AT91_REG PIO_PDR;
 AT91_REG PIO_PSR;
 AT91_REG Reserved0[1];
 AT91_REG PIO_OER;
 AT91_REG PIO_ODR;
 AT91_REG PIO_OSR;
 AT91_REG Reserved1[1];
 AT91_REG PIO_IFER;
 AT91_REG PIO_IFDR;
 AT91_REG PIO_IFSR;
 AT91_REG Reserved2[1];
 AT91_REG PIO_SODR;
 AT91_REG PIO_CODR;
 AT91_REG PIO_ODSR;
 AT91_REG PIO_PDSR;
 AT91_REG PIO_IER;
 AT91_REG PIO_IDR;
 AT91_REG PIO_IMR;
 AT91_REG PIO_ISR;
 AT91_REG PIO_MDER;
 AT91_REG PIO_MDDR;
 AT91_REG PIO_MDSR;
 AT91_REG Reserved3[1];
 AT91_REG PIO_PPUDR;
 AT91_REG PIO_PPUER;
 AT91_REG PIO_PPUSR;
 AT91_REG Reserved4[1];
 AT91_REG PIO_ASR;
 AT91_REG PIO_BSR;
 AT91_REG PIO_ABSR;
 AT91_REG Reserved5[9];
 AT91_REG PIO_OWER;
 AT91_REG PIO_OWDR;
 AT91_REG PIO_OWSR;
} AT91S_PIO, *AT91PS_PIO;





typedef struct _AT91S_CKGR {
 AT91_REG CKGR_MOR;
 AT91_REG CKGR_MCFR;
 AT91_REG Reserved0[1];
 AT91_REG CKGR_PLLR;
} AT91S_CKGR, *AT91PS_CKGR;
# 429 "./include/AT91SAM7X256.h"
typedef struct _AT91S_PMC {
 AT91_REG PMC_SCER;
 AT91_REG PMC_SCDR;
 AT91_REG PMC_SCSR;
 AT91_REG Reserved0[1];
 AT91_REG PMC_PCER;
 AT91_REG PMC_PCDR;
 AT91_REG PMC_PCSR;
 AT91_REG Reserved1[1];
 AT91_REG PMC_MOR;
 AT91_REG PMC_MCFR;
 AT91_REG Reserved2[1];
 AT91_REG PMC_PLLR;
 AT91_REG PMC_MCKR;
 AT91_REG Reserved3[3];
 AT91_REG PMC_PCKR[4];
 AT91_REG Reserved4[4];
 AT91_REG PMC_IER;
 AT91_REG PMC_IDR;
 AT91_REG PMC_SR;
 AT91_REG PMC_IMR;
} AT91S_PMC, *AT91PS_PMC;
# 493 "./include/AT91SAM7X256.h"
typedef struct _AT91S_RSTC {
 AT91_REG RSTC_RCR;
 AT91_REG RSTC_RSR;
 AT91_REG RSTC_RMR;
} AT91S_RSTC, *AT91PS_RSTC;
# 525 "./include/AT91SAM7X256.h"
typedef struct _AT91S_RTTC {
 AT91_REG RTTC_RTMR;
 AT91_REG RTTC_RTAR;
 AT91_REG RTTC_RTVR;
 AT91_REG RTTC_RTSR;
} AT91S_RTTC, *AT91PS_RTTC;
# 548 "./include/AT91SAM7X256.h"
typedef struct _AT91S_PITC {
 AT91_REG PITC_PIMR;
 AT91_REG PITC_PISR;
 AT91_REG PITC_PIVR;
 AT91_REG PITC_PIIR;
} AT91S_PITC, *AT91PS_PITC;
# 569 "./include/AT91SAM7X256.h"
typedef struct _AT91S_WDTC {
 AT91_REG WDTC_WDCR;
 AT91_REG WDTC_WDMR;
 AT91_REG WDTC_WDSR;
} AT91S_WDTC, *AT91PS_WDTC;
# 594 "./include/AT91SAM7X256.h"
typedef struct _AT91S_VREG {
 AT91_REG VREG_MR;
} AT91S_VREG, *AT91PS_VREG;







typedef struct _AT91S_MC {
 AT91_REG MC_RCR;
 AT91_REG MC_ASR;
 AT91_REG MC_AASR;
 AT91_REG Reserved0[21];
 AT91_REG MC_FMR;
 AT91_REG MC_FCR;
 AT91_REG MC_FSR;
} AT91S_MC, *AT91PS_MC;
# 684 "./include/AT91SAM7X256.h"
typedef struct _AT91S_SPI {
 AT91_REG SPI_CR;
 AT91_REG SPI_MR;
 AT91_REG SPI_RDR;
 AT91_REG SPI_TDR;
 AT91_REG SPI_SR;
 AT91_REG SPI_IER;
 AT91_REG SPI_IDR;
 AT91_REG SPI_IMR;
 AT91_REG Reserved0[4];
 AT91_REG SPI_CSR[4];
 AT91_REG Reserved1[48];
 AT91_REG SPI_RPR;
 AT91_REG SPI_RCR;
 AT91_REG SPI_TPR;
 AT91_REG SPI_TCR;
 AT91_REG SPI_RNPR;
 AT91_REG SPI_RNCR;
 AT91_REG SPI_TNPR;
 AT91_REG SPI_TNCR;
 AT91_REG SPI_PTCR;
 AT91_REG SPI_PTSR;
} AT91S_SPI, *AT91PS_SPI;
# 766 "./include/AT91SAM7X256.h"
typedef struct _AT91S_USART {
 AT91_REG US_CR;
 AT91_REG US_MR;
 AT91_REG US_IER;
 AT91_REG US_IDR;
 AT91_REG US_IMR;
 AT91_REG US_CSR;
 AT91_REG US_RHR;
 AT91_REG US_THR;
 AT91_REG US_BRGR;
 AT91_REG US_RTOR;
 AT91_REG US_TTGR;
 AT91_REG Reserved0[5];
 AT91_REG US_FIDI;
 AT91_REG US_NER;
 AT91_REG Reserved1[1];
 AT91_REG US_IF;
 AT91_REG Reserved2[44];
 AT91_REG US_RPR;
 AT91_REG US_RCR;
 AT91_REG US_TPR;
 AT91_REG US_TCR;
 AT91_REG US_RNPR;
 AT91_REG US_RNCR;
 AT91_REG US_TNPR;
 AT91_REG US_TNCR;
 AT91_REG US_PTCR;
 AT91_REG US_PTSR;
} AT91S_USART, *AT91PS_USART;
# 861 "./include/AT91SAM7X256.h"
typedef struct _AT91S_SSC {
 AT91_REG SSC_CR;
 AT91_REG SSC_CMR;
 AT91_REG Reserved0[2];
 AT91_REG SSC_RCMR;
 AT91_REG SSC_RFMR;
 AT91_REG SSC_TCMR;
 AT91_REG SSC_TFMR;
 AT91_REG SSC_RHR;
 AT91_REG SSC_THR;
 AT91_REG Reserved1[2];
 AT91_REG SSC_RSHR;
 AT91_REG SSC_TSHR;
 AT91_REG Reserved2[2];
 AT91_REG SSC_SR;
 AT91_REG SSC_IER;
 AT91_REG SSC_IDR;
 AT91_REG SSC_IMR;
 AT91_REG Reserved3[44];
 AT91_REG SSC_RPR;
 AT91_REG SSC_RCR;
 AT91_REG SSC_TPR;
 AT91_REG SSC_TCR;
 AT91_REG SSC_RNPR;
 AT91_REG SSC_RNCR;
 AT91_REG SSC_TNPR;
 AT91_REG SSC_TNCR;
 AT91_REG SSC_PTCR;
 AT91_REG SSC_PTSR;
} AT91S_SSC, *AT91PS_SSC;
# 965 "./include/AT91SAM7X256.h"
typedef struct _AT91S_TWI {
 AT91_REG TWI_CR;
 AT91_REG TWI_MMR;
 AT91_REG Reserved0[1];
 AT91_REG TWI_IADR;
 AT91_REG TWI_CWGR;
 AT91_REG Reserved1[3];
 AT91_REG TWI_SR;
 AT91_REG TWI_IER;
 AT91_REG TWI_IDR;
 AT91_REG TWI_IMR;
 AT91_REG TWI_RHR;
 AT91_REG TWI_THR;
} AT91S_TWI, *AT91PS_TWI;
# 1012 "./include/AT91SAM7X256.h"
typedef struct _AT91S_PWMC_CH {
 AT91_REG PWMC_CMR;
 AT91_REG PWMC_CDTYR;
 AT91_REG PWMC_CPRDR;
 AT91_REG PWMC_CCNTR;
 AT91_REG PWMC_CUPDR;
 AT91_REG PWMC_Reserved[3];
} AT91S_PWMC_CH, *AT91PS_PWMC_CH;
# 1041 "./include/AT91SAM7X256.h"
typedef struct _AT91S_PWMC {
 AT91_REG PWMC_MR;
 AT91_REG PWMC_ENA;
 AT91_REG PWMC_DIS;
 AT91_REG PWMC_SR;
 AT91_REG PWMC_IER;
 AT91_REG PWMC_IDR;
 AT91_REG PWMC_IMR;
 AT91_REG PWMC_ISR;
 AT91_REG Reserved0[55];
 AT91_REG PWMC_VR;
 AT91_REG Reserved1[64];
 AT91S_PWMC_CH PWMC_CH[4];
} AT91S_PWMC, *AT91PS_PWMC;
# 1078 "./include/AT91SAM7X256.h"
typedef struct _AT91S_UDP {
 AT91_REG UDP_NUM;
 AT91_REG UDP_GLBSTATE;
 AT91_REG UDP_FADDR;
 AT91_REG Reserved0[1];
 AT91_REG UDP_IER;
 AT91_REG UDP_IDR;
 AT91_REG UDP_IMR;
 AT91_REG UDP_ISR;
 AT91_REG UDP_ICR;
 AT91_REG Reserved1[1];
 AT91_REG UDP_RSTEP;
 AT91_REG Reserved2[1];
 AT91_REG UDP_CSR[6];
 AT91_REG Reserved3[2];
 AT91_REG UDP_FDR[6];
 AT91_REG Reserved4[3];
 AT91_REG UDP_TXVC;
} AT91S_UDP, *AT91PS_UDP;
# 1162 "./include/AT91SAM7X256.h"
typedef struct _AT91S_TC {
 AT91_REG TC_CCR;
 AT91_REG TC_CMR;
 AT91_REG Reserved0[2];
 AT91_REG TC_CV;
 AT91_REG TC_RA;
 AT91_REG TC_RB;
 AT91_REG TC_RC;
 AT91_REG TC_SR;
 AT91_REG TC_IER;
 AT91_REG TC_IDR;
 AT91_REG TC_IMR;
} AT91S_TC, *AT91PS_TC;
# 1293 "./include/AT91SAM7X256.h"
typedef struct _AT91S_TCB {
 AT91S_TC TCB_TC0;
 AT91_REG Reserved0[4];
 AT91S_TC TCB_TC1;
 AT91_REG Reserved1[4];
 AT91S_TC TCB_TC2;
 AT91_REG Reserved2[4];
 AT91_REG TCB_BCR;
 AT91_REG TCB_BMR;
} AT91S_TCB, *AT91PS_TCB;
# 1326 "./include/AT91SAM7X256.h"
typedef struct _AT91S_CAN_MB {
 AT91_REG CAN_MB_MMR;
 AT91_REG CAN_MB_MAM;
 AT91_REG CAN_MB_MID;
 AT91_REG CAN_MB_MFID;
 AT91_REG CAN_MB_MSR;
 AT91_REG CAN_MB_MDL;
 AT91_REG CAN_MB_MDH;
 AT91_REG CAN_MB_MCR;
} AT91S_CAN_MB, *AT91PS_CAN_MB;
# 1369 "./include/AT91SAM7X256.h"
typedef struct _AT91S_CAN {
 AT91_REG CAN_MR;
 AT91_REG CAN_IER;
 AT91_REG CAN_IDR;
 AT91_REG CAN_IMR;
 AT91_REG CAN_SR;
 AT91_REG CAN_BR;
 AT91_REG CAN_TIM;
 AT91_REG CAN_TIMESTP;
 AT91_REG CAN_ECR;
 AT91_REG CAN_TCR;
 AT91_REG CAN_ACR;
 AT91_REG Reserved0[52];
 AT91_REG CAN_VR;
 AT91_REG Reserved1[64];
 AT91S_CAN_MB CAN_MB0;
 AT91S_CAN_MB CAN_MB1;
 AT91S_CAN_MB CAN_MB2;
 AT91S_CAN_MB CAN_MB3;
 AT91S_CAN_MB CAN_MB4;
 AT91S_CAN_MB CAN_MB5;
 AT91S_CAN_MB CAN_MB6;
 AT91S_CAN_MB CAN_MB7;
 AT91S_CAN_MB CAN_MB8;
 AT91S_CAN_MB CAN_MB9;
 AT91S_CAN_MB CAN_MB10;
 AT91S_CAN_MB CAN_MB11;
 AT91S_CAN_MB CAN_MB12;
 AT91S_CAN_MB CAN_MB13;
 AT91S_CAN_MB CAN_MB14;
 AT91S_CAN_MB CAN_MB15;
} AT91S_CAN, *AT91PS_CAN;
# 1467 "./include/AT91SAM7X256.h"
typedef struct _AT91S_EMAC {
 AT91_REG EMAC_NCR;
 AT91_REG EMAC_NCFGR;
 AT91_REG EMAC_NSR;
 AT91_REG Reserved0[2];
 AT91_REG EMAC_TSR;
 AT91_REG EMAC_RBQP;
 AT91_REG EMAC_TBQP;
 AT91_REG EMAC_RSR;
 AT91_REG EMAC_ISR;
 AT91_REG EMAC_IER;
 AT91_REG EMAC_IDR;
 AT91_REG EMAC_IMR;
 AT91_REG EMAC_MAN;
 AT91_REG EMAC_PTR;
 AT91_REG EMAC_PFR;
 AT91_REG EMAC_FTO;
 AT91_REG EMAC_SCF;
 AT91_REG EMAC_MCF;
 AT91_REG EMAC_FRO;
 AT91_REG EMAC_FCSE;
 AT91_REG EMAC_ALE;
 AT91_REG EMAC_DTF;
 AT91_REG EMAC_LCOL;
 AT91_REG EMAC_ECOL;
 AT91_REG EMAC_TUND;
 AT91_REG EMAC_CSE;
 AT91_REG EMAC_RRE;
 AT91_REG EMAC_ROV;
 AT91_REG EMAC_RSE;
 AT91_REG EMAC_ELE;
 AT91_REG EMAC_RJA;
 AT91_REG EMAC_USF;
 AT91_REG EMAC_STE;
 AT91_REG EMAC_RLE;
 AT91_REG EMAC_TPF;
 AT91_REG EMAC_HRB;
 AT91_REG EMAC_HRT;
 AT91_REG EMAC_SA1L;
 AT91_REG EMAC_SA1H;
 AT91_REG EMAC_SA2L;
 AT91_REG EMAC_SA2H;
 AT91_REG EMAC_SA3L;
 AT91_REG EMAC_SA3H;
 AT91_REG EMAC_SA4L;
 AT91_REG EMAC_SA4H;
 AT91_REG EMAC_TID;
 AT91_REG EMAC_TPQ;
 AT91_REG EMAC_USRIO;
 AT91_REG EMAC_WOL;
 AT91_REG Reserved1[13];
 AT91_REG EMAC_REV;
} AT91S_EMAC, *AT91PS_EMAC;
# 1616 "./include/AT91SAM7X256.h"
typedef struct _AT91S_ADC {
 AT91_REG ADC_CR;
 AT91_REG ADC_MR;
 AT91_REG Reserved0[2];
 AT91_REG ADC_CHER;
 AT91_REG ADC_CHDR;
 AT91_REG ADC_CHSR;
 AT91_REG ADC_SR;
 AT91_REG ADC_LCDR;
 AT91_REG ADC_IER;
 AT91_REG ADC_IDR;
 AT91_REG ADC_IMR;
 AT91_REG ADC_CDR0;
 AT91_REG ADC_CDR1;
 AT91_REG ADC_CDR2;
 AT91_REG ADC_CDR3;
 AT91_REG ADC_CDR4;
 AT91_REG ADC_CDR5;
 AT91_REG ADC_CDR6;
 AT91_REG ADC_CDR7;
 AT91_REG Reserved1[44];
 AT91_REG ADC_RPR;
 AT91_REG ADC_RCR;
 AT91_REG ADC_TPR;
 AT91_REG ADC_TCR;
 AT91_REG ADC_RNPR;
 AT91_REG ADC_RNCR;
 AT91_REG ADC_TNPR;
 AT91_REG ADC_TNCR;
 AT91_REG ADC_PTCR;
 AT91_REG ADC_PTSR;
} AT91S_ADC, *AT91PS_ADC;
# 1723 "./include/AT91SAM7X256.h"
typedef struct _AT91S_AES {
 AT91_REG AES_CR;
 AT91_REG AES_MR;
 AT91_REG Reserved0[2];
 AT91_REG AES_IER;
 AT91_REG AES_IDR;
 AT91_REG AES_IMR;
 AT91_REG AES_ISR;
 AT91_REG AES_KEYWxR[4];
 AT91_REG Reserved1[4];
 AT91_REG AES_IDATAxR[4];
 AT91_REG AES_ODATAxR[4];
 AT91_REG AES_IVxR[4];
 AT91_REG Reserved2[35];
 AT91_REG AES_VR;
 AT91_REG AES_RPR;
 AT91_REG AES_RCR;
 AT91_REG AES_TPR;
 AT91_REG AES_TCR;
 AT91_REG AES_RNPR;
 AT91_REG AES_RNCR;
 AT91_REG AES_TNPR;
 AT91_REG AES_TNCR;
 AT91_REG AES_PTCR;
 AT91_REG AES_PTSR;
} AT91S_AES, *AT91PS_AES;
# 1802 "./include/AT91SAM7X256.h"
typedef struct _AT91S_TDES {
 AT91_REG TDES_CR;
 AT91_REG TDES_MR;
 AT91_REG Reserved0[2];
 AT91_REG TDES_IER;
 AT91_REG TDES_IDR;
 AT91_REG TDES_IMR;
 AT91_REG TDES_ISR;
 AT91_REG TDES_KEY1WxR[2];
 AT91_REG TDES_KEY2WxR[2];
 AT91_REG TDES_KEY3WxR[2];
 AT91_REG Reserved1[2];
 AT91_REG TDES_IDATAxR[2];
 AT91_REG Reserved2[2];
 AT91_REG TDES_ODATAxR[2];
 AT91_REG Reserved3[2];
 AT91_REG TDES_IVxR[2];
 AT91_REG Reserved4[37];
 AT91_REG TDES_VR;
 AT91_REG TDES_RPR;
 AT91_REG TDES_RCR;
 AT91_REG TDES_TPR;
 AT91_REG TDES_TCR;
 AT91_REG TDES_RNPR;
 AT91_REG TDES_RNCR;
 AT91_REG TDES_TNPR;
 AT91_REG TDES_TNCR;
 AT91_REG TDES_PTCR;
 AT91_REG TDES_PTSR;
} AT91S_TDES, *AT91PS_TDES;
# 66 "include/board.h" 2
# 36 "C:/projects/Crossworks/HelloWorld/at91lib/peripherals/pmc/pmc.c" 2
# 1 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/__debug_stdio.h" 1 3 4
# 14 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/__debug_stdio.h" 3 4
# 1 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/__cross_studio_io.h" 1 3 4
# 11 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/__cross_studio_io.h" 3 4
# 1 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 1 3 4
# 14 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
# 1 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/__crossworks.h" 1 3 4
# 22 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/__crossworks.h" 3 4
typedef __builtin_va_list __va_list;
# 15 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 2 3 4
# 51 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
void *debug_fopen(const char *filename, const char *mode);
# 60 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_fflush(void *stream);
# 69 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
void debug_fclose(void *stream);
# 88 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_fprintf(void *stream, const char *format, ...);
# 107 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_printf(const char *format, ...);
# 126 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_fscanf(void *stream, const char *format, ...);
# 145 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_scanf(const char *format, ...);
# 156 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_getchar(void);
# 166 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
char *debug_gets(char *s);
# 180 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_geti(int *i);
# 194 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_getu(unsigned *u);
# 208 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_getl(long *l);
# 222 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_getul(unsigned long *ul);
# 232 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_getf(float *f);
# 242 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_getd(double *);
# 256 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_getll(long long *ll);
# 270 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_getull(unsigned long long *ull);






int debug_fgetc(void *stream);
# 288 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
char *debug_fgets(char *s, int n, void *stream);
# 297 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_fputc(int c, void *stream);
# 307 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_fputs(const char *s, void *stream);
# 316 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_putchar(int c);
# 325 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_puts(const char *);
# 336 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_fread(void *ptr, int size, int nobj, void *stream);
# 347 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_fwrite(void *ptr, int size, int nobj, void *stream);
# 364 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_fseek(void *stream, long offset, int origin);
# 373 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
long debug_ftell(void *stream);







void debug_rewind(void *stream);
# 390 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_filesize(void *stream);






void debug_clearerr(void *stream);






int debug_feof(void *stream);






int debug_ferror(void *stream);







int debug_kbhit(void);







int debug_getch(void);
# 436 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
void debug_runtime_error(const char *error);







void debug_break(void);






void debug_exit(int result);







unsigned long debug_time(unsigned long *ptr);
# 501 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_vfprintf(void *stream, const char *format, __va_list);







int debug_vprintf(const char *format, __va_list);







int debug_vfscanf(void *stream, const char *format, __va_list);







int debug_vscanf(const char *format, __va_list);







int debug_ungetc(int c, void *stream);






int debug_fgetpos(void *stream, long *pos);






int debug_fsetpos(void *stream, const long *pos);







void *debug_freopen(const char *filename, const char *mode, void *stream);







void debug_perror(const char *s);
# 572 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_remove(const char *filename);
# 582 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_rename(const char *oldfilename, const char *newfilename);







void *debug_tmpfile(void);
# 599 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
char *debug_tmpnam(char *str);







char *debug_getenv(char *name);







int debug_system(char *command);
# 624 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
int debug_getargs(unsigned bufsize, unsigned char *buf);
# 636 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
void debug_loadsymbols(const char *filename, void *address, const char *breaksymbol);
# 645 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/cross_studio_io.h" 3 4
void debug_unloadsymbols(const char *filename);







int debug_enabled(void);
# 12 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/__cross_studio_io.h" 2 3 4
# 15 "C:/Program Files (x86)/Rowley Associates Limited/CrossWorks for ARM 2.0/include/__debug_stdio.h" 2 3 4
# 37 "C:/projects/Crossworks/HelloWorld/at91lib/peripherals/pmc/pmc.c" 2
# 90 "C:/projects/Crossworks/HelloWorld/at91lib/peripherals/pmc/pmc.c"
void PMC_DisableProcessorClock(void)
{
    ((AT91PS_PMC) 0xFFFFFC00)->PMC_SCDR = ((unsigned int) 0x1 << 0);
    while ((((AT91PS_PMC) 0xFFFFFC00)->PMC_SCSR & ((unsigned int) 0x1 << 0)) != ((unsigned int) 0x1 << 0));
}







void PMC_EnablePeripheral(unsigned int id)
{


    if ((((AT91PS_PMC) 0xFFFFFC00)->PMC_PCSR & (1 << id)) == (1 << id)) {

        debug_printf("PMC_EnablePeripheral: clock of peripheral"
                   " %u is already enabled\n\r",
                   id);
    }
    else {

        ((AT91PS_PMC) 0xFFFFFC00)->PMC_PCER = 1 << id;
    }
}







void PMC_DisablePeripheral(unsigned int id)
{


    if ((((AT91PS_PMC) 0xFFFFFC00)->PMC_PCSR & (1 << id)) != (1 << id)) {

        debug_printf("PMC_DisablePeripheral: clock of peripheral"
                   " %u is not enabled\n\r",
                   id);
    }
    else {

        ((AT91PS_PMC) 0xFFFFFC00)->PMC_PCDR = 1 << id;
    }
}





void PMC_EnableAllPeripherals(void)
{
    ((AT91PS_PMC) 0xFFFFFC00)->PMC_PCER = 0x3FFFFFFC;
    while( (((AT91PS_PMC) 0xFFFFFC00)->PMC_PCSR & 0x3FFFFFFC) != 0x3FFFFFFC);
    debug_printf("Enable all periph clocks\n\r");
}





void PMC_DisableAllPeripherals(void)
{
    ((AT91PS_PMC) 0xFFFFFC00)->PMC_PCDR = 0x3FFFFFFC;
    while((((AT91PS_PMC) 0xFFFFFC00)->PMC_PCSR & 0x3FFFFFFC) != 0);
    debug_printf("Disable all periph clocks\n\r");
}




unsigned int PMC_IsAllPeriphEnabled(void)
{
    return (((AT91PS_PMC) 0xFFFFFC00)->PMC_PCSR == 0x3FFFFFFC);
}




unsigned int PMC_IsPeriphEnabled(unsigned int id)
{
    return (((AT91PS_PMC) 0xFFFFFC00)->PMC_PCSR & (1 << id));
}



void PMC_CPUInIdleMode(void)
{
    PMC_DisableProcessorClock();



}
