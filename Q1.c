#include <msp430.h>

void gpioInit()
{
    P1OUT &= ~BIT0; // clear P1 output
    P1DIR |= BIT0; // setting P1 direction to output
    PM5CTL0 &= ~LOCKLPM5; // disabling high impedance mode
}

int main(void)
{
    WDTCTL = WDT_ADLY_250;                  // 250ms watchdog timer
    SFRIE1 |= WDTIE;                        // enable WDT interrupt

    gpioInit();


    __bis_SR_register(LPM0_bits | GIE);     // enabling interrupts
    __no_operation();                       // debug routine
}

// WDT interrupt
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) WDT_ISR (void)
#else
#error Compiler not supported!
#endif
{
    P1OUT ^= BIT0;                          // toggle LED on P1.0
}
