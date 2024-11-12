//Alternate LEDs from Off, Green, and Red

#include <msp430.h>

#include "libTimer.h"

#include "led.h"


void redState();
void greenState();
void offState();

int main(void) {
  // p1 output pins for green and red leds
  P1DIR |= LEDS;

  configureClocks();
  enableWDTInterrupts();
 
  or_sr(0x18);/* CPU off, GIE on */
}

void redState(){
  
  P1OUT |= LED_RED;
  P1OUT &= ~LED_GREEN;
 
}

void greenState(){

  P1OUT |= LED_GREEN;

  P1OUT &= ~LED_RED;
  
}

void offState(){
  
  P1OUT &= ~LED_RED;

  P1OUT &= ~LED_GREEN;
}

int secCount = 0;

void
__interrupt_vec(WDT_VECTOR) WDT(){
  secCount++;
  
  if(secCount >= 250){
    redState();
  }
  if(secCount >= 500){
    greenState();
  }
  if(secCount >= 750){
    secCount = 0;
    offState();
  }
}
