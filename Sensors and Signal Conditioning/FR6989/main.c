#include <msp430.h> 
#include "LCDDriver.h"

/**
 * main.c
 */

void LCDInit();
void PrepGPIO();

const int convertToASCII = 48; //Add this to a number to convert to ASCII character

int adcReading;
int d_four, d_three, d_two, d_one;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	PM5CTL0 &= ~LOCKLPM5;

	LCDInit();

	//Configure LED
	PrepGPIO();
	P1DIR |= BIT0;
	P9DIR |= BIT7;
	
	//Configure ADC input
	P1DIR |= BIT3;
	P1SEL0 |= BIT3;
	P1SEL1 |= BIT3;

	// Configure ADC12
	    ADC12CTL0 = ADC12SHT0_2 | ADC12ON;      // Sampling time, S&H=16, ADC12 on
	    ADC12CTL1 = ADC12SHP;                   // Use sampling timer
	    ADC12CTL2 |= ADC12RES_2;                // 12-bit conversion results
	    ADC12MCTL0 |= ADC12INCH_3;              // A3 ADC input select; Vref=AVCC
	    ADC12IER0 |= ADC12IE0;                  // Enable ADC conv complete interrupt

	    while (1)
	    {
	        __delay_cycles(1000);
	        ADC12CTL0 |= ADC12ENC | ADC12SC;    // Start sampling/conversion

	        __bis_SR_register(LPM0_bits | GIE); // LPM0, ADC12_ISR will force exit
	        __no_operation();                   // For debugger
	    }

	return 0;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC12_VECTOR))) ADC12_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG))
    {
        case ADC12IV_NONE:        break;    // Vector  0:  No interrupt
        case ADC12IV_ADC12OVIFG:  break;    // Vector  2:  ADC12MEMx Overflow
        case ADC12IV_ADC12TOVIFG: break;    // Vector  4:  Conversion time overflow
        case ADC12IV_ADC12HIIFG:  break;    // Vector  6:  ADC12BHI
        case ADC12IV_ADC12LOIFG:  break;    // Vector  8:  ADC12BLO
        case ADC12IV_ADC12INIFG:  break;    // Vector 10:  ADC12BIN
        case ADC12IV_ADC12IFG0:             // Vector 12:  ADC12MEM0 Interrupt
        	adcReading = ADC12MEM0;
        	d_four = (int)(adcReading/1000);
        	adcReading = adcReading % 1000;
        	d_three = (int)(adcReading/100);
        	adcReading = adcReading % 100;
        	d_two = (int)(adcReading/10);
        	d_one = adcReading % 10;
        	showChar(d_four + convertToASCII, 3);
        	showChar(d_three + convertToASCII, 4);
        	showChar(d_two + convertToASCII, 5);
        	showChar(d_one + convertToASCII, 6);
            if (ADC12MEM0 >= 0x7ff)         // ADC12MEM0 = A1 > 0.5AVcc?
                P1OUT |= BIT0;              // P1.0 = 1
            else
                P1OUT &= ~BIT0;             // P1.0 = 0
            __delay_cycles(1600000);
                // Exit from LPM0 and continue executing main
                __bic_SR_register_on_exit(LPM0_bits);
            break;
        default: break;
    }
}


void PrepGPIO()
{
    P1DIR = 0xFF; P2DIR = 0xFF;
    P1REN = 0xFF; P2REN = 0xFF;
    P1OUT = 0x00; P2OUT = 0x00;
}


void LCDInit()
{
    PJSEL0 = BIT4 | BIT5;                   // For LFXT

    // Initialize LCD segments 0 - 21; 26 - 43
    LCDCPCTL0 = 0xFFFF;
    LCDCPCTL1 = 0xFC3F;
    LCDCPCTL2 = 0x0FFF;

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Configure LFXT 32kHz crystal
    CSCTL0_H = CSKEY >> 8;                  // Unlock CS registers
    CSCTL4 &= ~LFXTOFF;                     // Enable LFXT
    do
    {
      CSCTL5 &= ~LFXTOFFG;                  // Clear LFXT fault flag
      SFRIFG1 &= ~OFIFG;
    }while (SFRIFG1 & OFIFG);               // Test oscillator fault flag
    CSCTL0_H = 0;                           // Lock CS registers

    // Initialize LCD_C
    // ACLK, Divider = 1, Pre-divider = 16; 4-pin MUX
    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;

    // VLCD generated internally,
    // V2-V4 generated internally, v5 to ground
    // Set VLCD voltage to 2.60v
    // Enable charge pump and select internal reference for it
    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN;

    LCDCCPCTL = LCDCPCLKSYNC;               // Clock synchronization enabled

    LCDCMEMCTL = LCDCLRM;                   // Clear LCD memory
    //Turn LCD on
    LCDCCTL0 |= LCDON;
}
