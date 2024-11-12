#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

int main() {
    configureClocks();
    
    buzzer_init();

    enableWDTInterrupts();


    or_sr(0x18);          // CPU off, GIE on
}

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
      noteA();
    }
    if(count >= 200){
      noteB();
    }
    if(count >= 300){
      noteC();
    }
    if(count >= 400){
      count = 0;
      count2++;
      noteB();
    }
  }
  if(count2 >= 3){
    if(count >= 100){
      noteD();
    }
    if(count >= 200){
      noteE();
    }
    if(count >= 300){
      noteC();
    }
    if(count >= 400){
      count = 0;
      count2 = 0;
      noteF();
    }
  }
}
