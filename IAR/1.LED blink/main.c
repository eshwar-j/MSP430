/*----------------------------------------------------------------------------
 * Author : Eshwar Jorvekar
 * Created on 19 June, 2017
 * Note(s):
 *----------------------------------------------------------------------------*/
 
 #include "msp430g2553.h"

volatile unsigned int i; // volatile to prevent optimization

void main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
P1DIR |= 0x01; // Set P1.0 to output direction

for (;;)
{
P1OUT ^= 0x01; // Toggle P1.0 using exclusive-OR
i = 5000; // Delay
do (i--);
while (i != 0);
}
}