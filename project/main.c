#include <msp430.h>
#include "h/libTimer.h"
#include "led.h"
#include "buzzer.h"

#define SW1 BIT3
#define SWITCHES SW1

void switch_init(){
  P1REN |= SWITCHES;
  P1IE |= SWITCHES;
  P1OUT |= SWITCHES;
}

void led_init(){
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;  
}

void wdt_init(){
  configureClocks();
  enableWDTInterrupts();
}

int main() {

  switch_init();
  buzzer_init();
  led_init();
  wdt_init();

  or_sr(0x18);          // CPU off, GIE on
}

// interrupt handler
static int buttonDown;

void switch_interrupt_handler(){
  char p1val = P1IN;

  P1IES |= (p1val & SWITCHES);
  P1IES &= (p1val | ~SWITCHES);

  if(p1val & SW1){
    P1OUT &= ~LED_GREEN;
    buttonDown = 0;
  } else {
    P1OUT |= LED_GREEN;
    buttonDown = 1;
  }
}

// led states
void redState(){
  
  P1OUT |= LED_RED;

  P1OUT &= ~LED_GREEN;
 
}

void greenState(){

  P1OUT |= LED_GREEN;

  P1OUT &= ~LED_RED;
  
}

void bothState(){
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;
}

void offState(){
  
  P1OUT &= ~LED_RED;

  P1OUT &= ~LED_GREEN;
}

// buzzer notes
void noteA(){
  buzzer_set_period(2093);
}

void noteB(){
  buzzer_set_period(3520);
}

void noteC(){
  buzzer_set_period(2637);
}

void noteD(){
  buzzer_set_period(3951);
}

void noteE(){
  buzzer_set_period(3135);
}

void noteF(){
  buzzer_set_period(2349);
}

int count = 0;
int count2 = 0;

void song1(){
if(count2 < 3){
    if(count >= 100){
      redState();
      noteA();
    }
    if(count >= 200){
      greenState();
      noteB();
    }
    if(count >= 300){
      bothState();
      noteC();
    }
    if(count >= 400){
      offState();
      count = 0;
      count2++;
      noteB();
    }
  }
  if(count2 >= 3){
    if(count >= 100){
      greenState();
      noteD();
    }
    if(count >= 200){
      redState();
      noteE();
    }
    if(count >= 300){
      bothState();
      noteC();
    }
    if(count >= 400){
      offState();
      count = 0;
      count2 = 0;
      noteF();
    }
  }
}

void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if(P1IFG & SWITCHES){
    P1IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

void
__interrupt_vec(WDT_VECTOR) WDT(){
  count++;
  if(buttonDown){
    song1();
  } else {
    offState();
    buzzer_set_period(0);
  }
}
