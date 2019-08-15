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

	TA0CTL=TASSEL__ACLK; //Este registro elige la fuente de reloj que se requiere
	TA0R=0; //El contador inicia en 0
    TA0CTL|=MC_3; // Se elige modo de conteo en este caso up/down(Modo 3)


	while(1)
	{
        if(P1OUT==0) //Si el led está apagado
            TA0CCR0=8192; // El contador llegará hasta este valor
        else         //Si el led está encendido
            TA0CCR0=49152; // EL contador llegará hasta este valor

	    if((TA0CTL&TAIFG)==TAIFG) // Si Se lanza la bandera de interrupcion(EL contador llegó al valor de TA0CCR0)
	            {
	                 P1OUT^=BIT0; // El led conmutará

	                TA0CTL&=~TAIFG; // La banderá se pondrá a 0
	            }
	}

}
