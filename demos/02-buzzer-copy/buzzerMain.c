#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

int main() {
    configureClocks();
    
    buzzer_init();

    enableWDTInterrupts();


    or_sr(0x18);          // CPU off, GIE on
}

void noteC6(){
  buzzer_set_period(3824);
}

void noteC6_s(){
  buzzer_set_period(3608);
}

void noteD6(){
  buzzer_set_period(3406);
}

int count = 0;
// int count2 = 0;

void
__interrupt_vec(WDT_VECTOR) WDT(){
  count++;
  
  // testing polyphony

  if(count >= 1){
    noteC6();
  }
  if(count >= 2){
    noteD6;
  }
  if(count >= 3){
    count = 0;
  }
  
}
