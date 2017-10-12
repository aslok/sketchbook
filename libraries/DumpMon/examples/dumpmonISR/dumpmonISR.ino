// This is an example sketch for Simple Dumping Monitor.
// It shows how to use ISR breakpoint functions in your sketches.
//
#include <dumpmon.h>        // Include necessary header.

void setup() {
  dumpmonSetup(19200);      // Call setup function to begin Serial communication.
  // Setup Timer2 overflow interrupt.
  DEV_TIMER2.setClockSelect(Prescaler2::Prescaler_256);
  DEV_TIMER2.setWaveGenMode(Timer2::FastPWM);
  DEV_TICTRL2.overflowIntEnable();
  enableInterrupts();
}

void loop() {
  dumpmonLoop();            // Call dump monitor loop function to handle Serial communication.
}

ISR(TIMER2_OVF_vect)
{
  breakISR(dumpmon::timer2_ovf); // Call breakISR() function with interrupt identifier as parameter.
  // DO NOT use any other dumpmon functions inside ISR() handlers.
}

