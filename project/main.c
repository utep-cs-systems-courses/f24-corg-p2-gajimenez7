#include <msp430.h>
#include "led.h"

void main(){
  P1DIR |= LED_RED;
  P1OUT &= ~LED_RED;
  or_sr(0x18);
}
