#include <msp430.h>

void main(void)
{
WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1SEL &= (~BIT1); // Set P1.0 SEL for GPIO
    P1DIR |= BIT1; // Set P1.0 as Output
    P1OUT |= BIT1; // Set P1.0 HIGH

    TACTL = TASSEL_2 + ID_3 + MC_1 + TACLR; // select SMCLK at 1000HZ, up mode and clear TA

    TA0CCR0 = 31299; //  Period
    TA0CCR1 = 6249; // Duty Cycle

    //CLK Configurations
    TA0CCTL0 |= CCIE;
    TA0CCTL1 |= CCIE;
    TA0CCTL0 &=~CCIFG;
    TA0CCTL1 &=~CCIFG;

    _enable_interrupt();

    while(1);

}

#pragma vector = TIMER0_A0_VECTOR       //define the interrupt service vector
__interrupt void TA0_ISR (void)    // interrupt service routine
{
//output high voltage
P1OUT |=BIT1;
TA0CCTL0 &=~CCIFG;
}
#pragma vector = TIMER0_A1_VECTOR       //define the interrupt service vector
__interrupt void TA1_ISR (void)    // interrupt service routine
{
//Turn off voltage output
P1OUT &=~BIT1;
TA0CCTL1 &=~CCIFG;
}

