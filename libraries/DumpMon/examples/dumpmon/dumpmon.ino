// This is an example sketch for Simple Dumping Monitor.
// It shows how to use  Simple Dumping Monitor in your sketches.
//
#include <dumpmon.h>        // Include necessary header.

void setup() {
  dumpmonSetup(19200);      // Call setup function to begin Serial communication.
}

void loop() {
  dumpmonLoop();            // Call dump monitor loop function to handle Serial communication.
}
