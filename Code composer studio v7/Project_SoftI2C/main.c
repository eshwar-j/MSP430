/*----------------------------------------------------------------------------
 * Author : Eshwar Jorvekar
 * Created on 22 June, 2017
 * Note(s): Implements I2C using GPIOs(bit bang)
 *----------------------------------------------------------------------------*/

#include "msp430g2210.h"

#define SDA BIT2
#define SCL BIT5

void delay();
void init_i2c();
void i2c_start();
void i2c_stop();
void i2c_repeated_start();
void i2c_send_byte(unsigned char byte);
void i2c_ack();
void i2c_nack();

//void i2c_read_byte();

void main(void)
{
unsigned char i,tmp;        // Variable to be used in for loop
  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
init_i2c();
delay(10);
i2c_start();
i2c_send_byte(0xA0);
i2c_stop();

while(1);       //
}

// initialize i2c----------------------------------------------------------------
void init_i2c()
{
  P1DIR |= (SDA + SCL); // Set P2.2 and P2.5 to output direction
}

// i2c start condition----------------------------------------------------------------

void i2c_start()
{
  P1OUT |= (SDA + SCL);
  __delay_cycles(5);
  P1OUT &= ~SDA;      // SDA=1->0 while SCL=1
}

// i2c repeated start condition----------------------------------------------------------------

void i2c_repeated_start()
{
  P1OUT &= ~SCL;
  P1OUT |= SDA;
  __delay_cycles(5);
  P1OUT |= SCL;
  P1OUT &= ~SDA;
}

void i2c_send_byte(unsigned char byte)
{
    int i,tmp;
    for(i=0;i<8;i++)        // Repeat for every bit
    {
      P1OUT &= ~SCL;
      __delay_cycles(1);
      tmp=(((byte<<i)&0x80)?(P1OUT|=SDA):(P1OUT&=~SDA));  // Place data bit value on SDA pin depending on 0 or 1 bit
      __delay_cycles(1);
      P1OUT |= SCL;      // Toggle SCL pin so that slave can latch data bit
      __delay_cycles(1);
    }

    // Get ACK from slave
    P1OUT &= ~SCL;
    P1OUT |= SDA;
    __delay_cycles(1);
    P1OUT |= SCL;
    __delay_cycles(1);
}

// i2c stop condition----------------------------------------------------------------
void i2c_stop()
{
  P1OUT |= ~(SDA + SCL);
  __delay_cycles(5);
  P1OUT |= (SDA + SCL);      // SDA=0->1 while SCL=1
}

// i2c ack condition----------------------------------------------------------------
void i2c_ack()
{
  P1OUT &= ~(SCL + SDA);
  __delay_cycles(5);
  P1OUT |= SCL;
}

// i2c nack condition----------------------------------------------------------------
void i2c_nack()
{
  P1OUT &= ~SCL;
  P1OUT |= SDA;
  __delay_cycles(5);
  P1OUT |= SCL;
}

// generate some delay----------------------------------------------------------------
void delay(unsigned int count)
{
  int i,j;
  for(i=0;i<count;i++)
    for(j=0;j<1275;j++);
}

