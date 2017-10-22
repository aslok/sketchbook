/*
 * serial_check.ino
 *
 * created 21.10.2017
 * modifid 21.10.2017
 * with Arduino 1.8.3 (tested on Arduino Uno)
 *
 * Copyright 2017 Vitaliy Fust <aslok.zp@gmail.com>
 *
 * This work is licensed under the MIT License (MIT). To view a copy of this
 * license, visit http://opensource.org/licenses/MIT or send a letter to:
 * Open Source Initiative
 * 855 El Camino Real
 * Ste 13A, #270
 * Palo Alto, CA 94301
 * United States.
 *
 *
Sketch uses 1,942 bytes (6.0%) of program storage space. Maximum is 32,256 bytes.
Global variables use 188 bytes (9.2%) of dynamic memory, leaving 1,860 bytes for local variables. Maximum is 2,048 bytes.
 */

void setup(){
    Serial.begin(57600);
}

void loop(){
    Serial.println(analogRead(0));
    delay(800);
}
