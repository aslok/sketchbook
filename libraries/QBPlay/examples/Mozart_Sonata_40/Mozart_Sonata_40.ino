/*
 * Mozart_Sonata_40.ino
 * Файл с примером использования библиотеки QBPlay
 * https://en.wikibooks.org/wiki/QBasic/Appendix#PLAY
 *
 * created 10.11.2017
 * modified 12.11.2017
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
 */

#include "QBPlay.h"
QBPlay* play;
const byte speaker_pin = A3;

const char Mozart_Sonata_40[] PROGMEM = "MNT255L8O4D+DL4DL8D+DL4DL8D+DL4DA+P4L8A+AL4GL8GFL4D+L8D+DL4CCP4L8DCL4CL8DCL4CL8DCL4CAP4L8AGL4F+L8F+D+L4DL8DCL4<A+A+P4L8>A+AL4A>C<F+AGDP4L8A+AL4A>C<F+AGA+L8AGFD+L64<A+>D<A+>D<A+>D<A+>D<A+>D<A+>D<A+>D<A+>D<A+>D<A+>D<A+>D<A+>D<A+>D<A+>D<G>C+<G>C+<G>C+<G>C+<G>C+<G>C+<G>C+<G>C+<G>C+<G>C+<G>C+<G>C+<G>C+<G>C+<F+A>D<F+A>D<F+A>DP4<GA+>C+<GA+>C+<GA+>C+<GA+>C+<GA+>C+<GA+>C+<F+A>D<F+A>D<F+A>DP4<GA+>C+<GA+>C+<GA+>C+<GA+>C+<GA+>C+<GA+>C+<F+A>D<F+A>D<F+A>DP4<GA+>C+<GA+>C+<GA+>C+<GA+>C+<GA+>C+<GA+>C+<F+A>D<F+A>D<F+A>D<GA+>C+<GA+>C+<GA+>C+<F+A>D<F+A>D<F+A>D<GA+>C+<GA+>C+<GA+>C+<F+A>D<F+A>D<F+A>DP4P4L8D+DL4DL8D+DL4DL8D+DL4DA+P4L8A+AL4GL8GFL4D+L8D+DL4CCP4L8FD+L4D+L8FD+L4D+L8FD+L4D+>CP4L8C<A+L4AL8AGL4FL8FD+L2DP4L8GFL4FL8GFL4FL8<GFL4FL8GFL4FL8>GFL4FL8GFL4FL8<GFL4FL8GFL4FL8>D+DL4DL8D+DL4D+L8DCL2DL4D+.L8CL4<A+.L8>DL4C.L8<AL2A+L8A+P8>GFL4FL8GFL4FL8<GFL4FL8GFL4FL8>GFL4FL8GFL4FL8<GFL4FL8GFL4FL8>D+DL4DL8D+DL4DL8D+DL2DL4D+.L8CL4<A+.L8>DL4C.L8<AL4A+L8O5DC<A+AGFD+DC<A+AGFD+L4DL64A+>DF<A+>DF<A+>DF<A+>D+G<A+>D+G<A+>D+GCFACFACFAL8A+A>DC<A+AGFD+DC<A+AGFD+L4DL64A+>DF<A+>DF<A+>DF<A+>DF<A+>D+G<A+>D+G<A+>D+G<A+>D+GCFACFACFACFADGA+DGA+DGA+DGA+<A+>D+>D+G<A+>D+G<A+>DF<A+>DF<A+>DF<A+>DFCD+ACD+ACD+ACD+AL8DG<A+>D+G<A+FA+AF>C<AA+DFA+AF>C<AA+DFA+AF>C<AA+>DC<AA+>DC<AL4A+P4P2>DP2L64<DFA+DFA+DFA+DFA+DFA+DFA+DFA+DFA+DFA+DFA+DFA+DFA+DFA+DFA+DFA+";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Mozart_Sonata_40);
}

void loop(){
    play->touch();
}
