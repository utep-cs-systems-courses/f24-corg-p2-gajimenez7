//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

short led_on = 0;

void toggle_greenLED(){
  if(led_on){
    led_on = 0;
    P1OUT &= ~LED_GREEN;
  }else{
    led_on = 1;
    P1OUT |= LEG_GREEN;
  }
}

int wcount_0 = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  wcount_0++;
  if(wcount_0 == 250){
    wcount_0 = 0;
    toggle_greenLED();
  }
} 
