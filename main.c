#include <msp430.h> 

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR=BIT0;
	P1SEL=0;
	P1REN=0;
	P1OUT=0;

	TA0CTL=TASSEL__ACLK;
	TA0R=0;
    TA0CTL|=MC_3;


	while(1)
	{
        if(P1OUT==0)
            TA0CCR0=8192;
        else
            TA0CCR0=49152;

	    if((TA0CTL&TAIFG)==TAIFG)
	            {
	                 P1OUT^=BIT0;

	                TA0CTL&=~TAIFG;
	            }
	}

}
