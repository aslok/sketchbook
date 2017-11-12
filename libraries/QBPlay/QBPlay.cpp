/*
 * QBPlay.cpp
 * Основной файл библиотеки QBPlay
 * Библиотека предназначена для воспроизведения мелодий
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

QBPlay::QBPlay(const byte speaker_pin){
    pin = speaker_pin;
    pinMode(pin, OUTPUT);
}

void QBPlay::start(const __FlashStringHelper* melodie_str){
    play = true;
    melodie = melodie_str;
    melodie_pos = 0;
    octave = 3;
    tempo = 2000;
    length = 4;
    duration = 7;
    cache_pos = 65535;
}

unsigned long QBPlay::touch(unsigned long ms){
    static unsigned long ms_prev = 0;
    static unsigned int ms_wait = 0;
    if (!ms){
        ms = millis();
    }
    if (!play || ms - ms_prev < ms_wait){
        return ms;
    }

    dot = false;
    unsigned int freq = 0;
    boolean done = false;
    while (!freq && !done){
        switch (get_next_chr()){
            case 'M':
                switch (get_next_chr()){
                    case 'S':
                        duration = 6;
                        break;
                    case 'N':
                        duration = 7;
                        break;
                    case 'L':
                        duration = 8;
                        break;
                }
                break;
            case 'T':
                tempo = 240e3 / get_next_num();
                break;
            case 'L':
                length = get_next_num();
                break;
            case 'O':
                octave = get_next_num();
                break;
            case '>':
                if (octave < 6){
                    octave++;
                }
                break;
            case '<':
                if (octave){
                    octave--;
                }
                break;
            case 'P':
                ms_wait = tempo / get_next_num();
                done = true;
                break;
            case 0:
                play = false;
                melodie_pos = 0;
                return ms;
            case 'C':
                freq = note_freq(0);
                break;
            case 'D':
                freq = note_freq(2);
                break;
            case 'E':
                freq = note_freq(4);
                break;
            case 'F':
                freq = note_freq(5);
                break;
            case 'G':
                freq = note_freq(7);
                break;
            case 'A':
                freq = note_freq(9);
                break;
            case 'B':
                freq = note_freq(11);
                break;
        }
    }
    if (freq){
        ms_wait = tempo * (dot ? 1.5 : 1) / length;
        noTone(pin);
        tone(pin, freq, ms_wait * duration / 8);
    }
    ms_prev = millis();
    return ms_prev;
}

int QBPlay::note_freq(byte num){
    unsigned int* freq_ptr;
    boolean no_dot = false;
    switch (get_next_chr()){
        case '#':
        case '+':
            freq_ptr = num < 11 ?
                &freq[octave][num + 1] :
                (octave < 6 ? &freq[octave + 1][0] : NULL);
            break;
        case '-':
            freq_ptr = num ?
                &freq[octave][num - 1] :
                (octave ? &freq[octave - 1][11] : NULL);
            break;
        case '.':
            dot = true;
            freq_ptr = &freq[octave][num];
            break;
        default:
            melodie_pos--;
            no_dot = true;
            freq_ptr = &freq[octave][num];
    }
    if (!dot && !no_dot){
        switch (get_next_chr()){
            case '.':
                dot = true;
                break;
            default:
                melodie_pos--;
        }
    }
    return freq_ptr != NULL ? (int) pgm_read_word_near(freq_ptr) : 0;
}

char QBPlay::get_next_chr(){
    static char cache_chr;
    if (cache_pos != melodie_pos){
        cache_pos = melodie_pos;
        cache_chr = toupper((char) pgm_read_byte_near((char *) melodie + melodie_pos));
    }
    melodie_pos++;
    return cache_chr;
}

byte QBPlay::get_next_num(){
    char out[4];
    char tmp;
    byte out_pos;
    for (out_pos = 0; out_pos < 4 && (tmp = get_next_chr()) && tmp >= '0' && tmp <= '9'; out[out_pos++] = tmp);
    melodie_pos--;
    // Ошибка - в числе ни одной цифры или больше трех цифр
    if (!out_pos || out_pos >= 3){
        return 0;
    }
    out[out_pos] = 0;
    return (byte) atoi(out);
}
