// This is an example sketch for Simple Dumping Monitor.
// It shows how to add Simple Dumping Monitor in Blink example sketch.
//
#include <dumpmon.h>        // Include necessary header.

#define LEDPIN  13

void setup() {
  pinMode(LEDPIN, OUTPUT);
  dumpmonSetup(19200);      // Call setup function to begin Serial communication.
}

void loop() {
  dumpmonLoop();            // Call dump monitor loop function to handle Serial communication.
  digitalWrite(LEDPIN, HIGH);
  delay(500);
  digitalWrite(LEDPIN, LOW);
  delay(500);
}
