#include "msp430.h"
#include <LCDDriver.h>

void LCDInit();

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop WDT

    LCDInit();

    // Initialize the Display with "123456"
    showChar('1', 1);
    showChar('2', 2);
    showChar('3', 3);
    showChar('4', 4);
    showChar('5', 5);
    showChar('6', 6);


    char Letter = 'A';
    int i = 1;  // Position on the LCD
    unsigned int j = 0; // Delay Variable
    while(1)
    {
        if (i>6) // If we have reached the end of the display
        {
            i = 1; // Go back to position one
        }
        while (Letter < ('Z' + 1))  // Run through every capital letter
        {
            showChar(Letter, i);    // Display Current Letter
            Letter++;   // Increment Letter
            while (j < 25000)   // Delay Loop
            {
                j++;
            }
            j = 0;
        }
        Letter = 'A'; // Once a cycle is completed, reset letter to 'A'
        i++;    // Increment LCD Position

    }
    return 0;
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