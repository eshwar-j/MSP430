/*----------------------------------------------------------------------------
 * Author : Eshwar Jorvekar
 * Created on 22 June, 2017
 * Note(s):
 *----------------------------------------------------------------------------*/
 
 
#include "msp430g2553.h"

void main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

     P1DIR |= (BIT0 + BIT1);		//P1.23 as input SW, other pins not affected

     while(1)
     {
        P1OUT |= BIT0;	//set P0.1 high
	__delay_cycles(1000);
        P1OUT &= ~BIT0;		//set P0.1 low
     }
}