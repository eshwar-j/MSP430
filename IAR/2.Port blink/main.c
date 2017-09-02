/*----------------------------------------------------------------------------
 * Author : Eshwar Jorvekar
 * Created on 20 June, 2017
 * Note(s):
 *----------------------------------------------------------------------------*/
 
 #include "msp430g2553.h"

volatile unsigned int i; // volatile to prevent optimization

void main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
P1DIR |= 0xff; // Set P1 to output direction


for (;;)
{
P1OUT ^= 0xff; // Toggle P1.0 using exclusive-OR
i = 5000; // Delay
do (i--);
while (i != 0);
}
}