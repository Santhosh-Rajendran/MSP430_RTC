#include <msp430.h> 

/*
 * main.c
 */
#define _25MS_COUNT		 (0x4E20)
#define _1_SEC_COUNT	 (50)

unsigned int count = 0;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TimerA_Interrupt(void)
{
	count++;
	if(count >= _1_SEC_COUNT)
	{
		P1OUT ^= 0x41;
		count = 0;
	}
}


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
    
    P1DIR = 0x41;
    P1OUT = 0x00;
    
    TACTL = TASSEL_2 + MC_3;
    TACCR0 = _25MS_COUNT;
	TACCTL0	  = CCIE;

    __bis_SR_register(GIE);
    
    for(;;)
    {

    }

}
