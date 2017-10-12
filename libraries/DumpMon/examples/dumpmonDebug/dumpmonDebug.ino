// This is an example sketch for Simple Dumping Monitor.
// It shows how to use Simple Dumping Monitor in your sketches for symbolic debugging.
//
#include <dumpmon.h>        // Include necessary header.

#define LEDPIN 13           // LED pin is the Digital 13 pin

int count = 0;              // 16-bit integer counter variable
long lcount = 0;            // 32-bit integer counter variable
const char* text = "Debug"; // Text string variable

void setup() {
  pinMode(LEDPIN, OUTPUT);          // We will debug blinking
  dumpmonSetup(19200);              // Call DumpMon setup function
  watch(&count, "count");           // Add integer watch
  watch(&lcount, "lcount");         // Add long integer watch
  watch(&text, "text");             // Add text string watch
  watch(&PORTB, "PORTB");           // Add register watch
}

void loop() {
  ++count;                          // Counters are incrementing
  ++lcount;
  breakpoint("counters watch");     // Call breakpoint with some id
  if (count & 1)                    // Some text processing
    text = "Example";
  else
    text = "Debug";
  breakpoint("text watch");         // Another breakpoint
  if (count & 5)                    // Some fast blinking
    digitalWrite(LEDPIN, HIGH);
  else
    digitalWrite(LEDPIN, LOW);
}