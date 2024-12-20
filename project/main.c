#include <msp430.h>
#include "h/libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switch.h"

extern volatile int count2;

extern void noSurprises(void);
extern void test(void);

static int buttonDown;

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


void switch_interrupt_handler(){
  char p2val = P2IN;

  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);

  if(p2val & SW1){
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

/*
void noSuprises(){
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
*/

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

volatile int count = 0;
volatile int count2 = 0;

void
__interrupt_vec(WDT_VECTOR) WDT(){
  count++;
  if(buttonDown){
    noSurprises();
  } else {
    offState();
    buzzer_set_period(0);
  }

}
