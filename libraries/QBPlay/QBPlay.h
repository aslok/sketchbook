/*
 * QBPlay.h
 * Заголовочный файл библиотеки QBPlay
 * Библиотека предназначена для воспроизведения мелодий
 * https://en.wikibooks.org/wiki/QBasic/Appendix#PLAY
 *
 * created 10.11.2017
 * modified 13.11.2017
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

#ifndef QBPlay_h
#define QBPlay_h

#include "Arduino.h"

const boolean QBPlay_REPEAT = true;

//    0     1     2     3     4     5     6     7     8     9     10    11
//    C     C#    D     D#    E     F     F#    G     G#    A     A#    B
const unsigned int freq[][12] PROGMEM = {
    { 65,   69,   73,   78,   82,   87,   92,   98,   104,  110,  117,  123  }, // 0 = Большая октава
    { 131,  139,  147,  156,  165,  175,  185,  196,  208,  220,  233,  247  }, // 1 = Малая октава
    { 262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,  494  }, // 2 = 1-я октава
    { 523,  554,  587,  622,  659,  698,  740,  784,  831,  880,  932,  988  }, // 3 = 2-я октава
    { 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976 }, // 4 = 3-я октава
    { 2093, 2218, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951 }, // 5 = 4-я октава
    { 4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902 }, // 6 = 5-я октава
};

class QBPlay{
    public:
        QBPlay(const byte speaker_pin);

        void start(const __FlashStringHelper* melodie_str, boolean melodie_repeat = false);
        unsigned long touch(unsigned long ms = 0);

        // Флаг - воспроизводим или нет
        boolean play = false;
        // Флаг - повтор воспроизведения
        boolean repeat = false;
    private:
        int note_freq(byte num);
        char get_next_chr();
        byte get_next_num();

        // Cтрока с мелодией в памяти
        __FlashStringHelper* melodie;
        // Текущий символ строки
        unsigned int melodie_pos;
        // pin на который подключен спикер
        byte pin;
        // Октава
        byte octave;
        // Темп исполнения милисекунд на целую ноту
        unsigned int tempo;
        // Размер ноты ( 1 = целая, 2 = половинка, 4 = четверть и т.д.)
        byte length;
        // Продолжительность звучания ноты
        byte duration;
        // Текущая нота в полтора раза дольше чем остальные
        boolean dot;

        // Кеширование для последнего прочитанного символа
        unsigned int cache_pos;
};

#endif
