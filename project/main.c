#include <msp430.h>
#include "h/libTimer.h"
#include "led.h"
#include "buzzer.h"

int main() {
    P1DIR |= LEDS;
    
    configureClocks();
    
    buzzer_init();

    enableWDTInterrupts();


    or_sr(0x18);          // CPU off, GIE on
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

void
__interrupt_vec(WDT_VECTOR) WDT(){
  count++;

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
