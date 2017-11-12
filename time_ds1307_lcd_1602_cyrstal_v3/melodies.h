#define NO_MELODIE 255

typedef struct note_item {
  int note;
  byte duration;
  byte wait;
};

const note_item melodie_1[] PROGMEM = {
  { NOTE_C4,    25,  32 },
  { NOTE_G3,    12,  16 },
  { NOTE_G3,    12,  16 },
  { NOTE_A3,    25,  32 },
  { NOTE_G3,    25,  32 },
  { NOTE_SPC,   25,  32 },
  { NOTE_B3,    25,  32 },
  { NOTE_C4,    25,  32 },
  { NOTE_END,    0,   0 }
};
const note_item melodie_2[] PROGMEM = {
  { NOTE_F5,    30,  60 },
  { NOTE_F5,    30,  60 },
  { NOTE_G5,    15,  30 },
  { NOTE_F5,    15,  30 },
  { NOTE_DS5,   45,  60 },
  { NOTE_D5,    15,  30 },
  { NOTE_C5,    15,  30 },
  { NOTE_AS4,   45,  60 },
  { NOTE_F4,    45,  60 },
  { NOTE_SPC,   30,  30 },
  { NOTE_F4,    45,  60 },
  { NOTE_AS4,   45,  60 },
  { NOTE_C5,    15,  30 },
  { NOTE_D5,    15,  30 },
  { NOTE_DS5,   45,  60 },
  { NOTE_D5,    15,  30 },
  { NOTE_C5,    15,  30 },
  { NOTE_F5,   135, 180 },
  { NOTE_F5,    30,  60 },
  { NOTE_F5,    30,  60 },
  { NOTE_G5,    15,  30 },
  { NOTE_F5,    15,  30 },
  { NOTE_DS5,   45,  60 },
  { NOTE_D5,    15,  30 },
  { NOTE_C5,    15,  30 },
  { NOTE_AS4,   45,  60 },
  { NOTE_F4,    45,  60 },
  { NOTE_SPC,   30,  30 },
  { NOTE_F4,    45,  60 },
  { NOTE_DS5,   45,  60 },
  { NOTE_D5,    15,  30 },
  { NOTE_C5,    15,  30 },
  { NOTE_F5,    45,  60 },
  { NOTE_D5,    15,  30 },
  { NOTE_C5,    15,  30 },
  { NOTE_AS4,  135,  60 },
  { NOTE_END,    0,   0 }
};
const note_item melodie_3[] PROGMEM = {
  { NOTE_E6,    15,  15 },
  { NOTE_E6,    30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_C6,    15,  15 },
  { NOTE_E6,    30,  30 },
  { NOTE_G6,    60,  60 },
  { NOTE_G5,    60,  60 },
  { NOTE_C6,    45,  45 },
  { NOTE_G5,    15,  45 },
  { NOTE_E5,    30,  45 },
  { NOTE_A5,    30,  30 },
  { NOTE_B5,    15,  30 },
  { NOTE_AS5,   15,  15 },
  { NOTE_A5,    30,  30 },
  { NOTE_G5,    21,  21 },
  { NOTE_E6,    21,  21 },
  { NOTE_G6,    15,  15 },
  { NOTE_A6,    30,  30 },
  { NOTE_F6,    15,  15 },
  { NOTE_G6,    15,  30 },
  { NOTE_E6,    30,  30 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    15,  15 },
  { NOTE_B5,    45,  45 },
  { NOTE_C6,    45,  45 },
  { NOTE_G5,    15,  45 },
  { NOTE_E5,    30,  45 },
  { NOTE_A5,    30,  30 },
  { NOTE_B5,    15,  30 },
  { NOTE_AS5,   15,  15 },
  { NOTE_A5,    30,  30 },
  { NOTE_G5,    21,  21 },
  { NOTE_E6,    21,  21 },
  { NOTE_G6,    15,  15 },
  { NOTE_A6,    30,  30 },
  { NOTE_F6,    15,  15 },
  { NOTE_G6,    15,  30 },
  { NOTE_E6,    30,  30 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    15,  15 },
  { NOTE_B5,    45,  60 },
  { NOTE_G6,    15,  15 },
  { NOTE_FS6,   15,  15 },
  { NOTE_F6,    15,  15 },
  { NOTE_DS6,   30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_GS5,   15,  15 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  30 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    15,  15 },
  { NOTE_SPC,   15,  15 },
  { NOTE_G6,    15,  15 },
  { NOTE_FS6,   15,  15 },
  { NOTE_F6,    15,  15 },
  { NOTE_DS6,   30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_C7,    30,  30 },
  { NOTE_C7,    15,  15 },
  { NOTE_C7,    60,  60 },
  { NOTE_G6,    15,  15 },
  { NOTE_FS6,   15,  15 },
  { NOTE_F6,    15,  15 },
  { NOTE_DS6,   30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_GS5,   15,  15 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  30 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    15,  45 },
  { NOTE_DS6,   30,  45 },
  { NOTE_D6,    45,  45 },
  { NOTE_C6,    60, 120 },
  { NOTE_G6,    15,  15 },
  { NOTE_FS6,   15,  15 },
  { NOTE_F6,    15,  15 },
  { NOTE_DS6,   30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_GS5,   15,  15 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  30 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    15,  15 },
  { NOTE_SPC,   15,  15 },
  { NOTE_G6,    15,  15 },
  { NOTE_FS6,   15,  15 },
  { NOTE_F6,    15,  15 },
  { NOTE_DS6,   30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_C7,    30,  30 },
  { NOTE_C7,    15,  15 },
  { NOTE_C7,    60,  60 },
  { NOTE_G6,    15,  15 },
  { NOTE_FS6,   15,  15 },
  { NOTE_F6,    15,  15 },
  { NOTE_DS6,   30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_GS5,   15,  15 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  30 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    15,  45 },
  { NOTE_DS6,   30,  45 },
  { NOTE_D6,    45,  45 },
  { NOTE_C6,    60, 120 },
  { NOTE_C6,    15,  15 },
  { NOTE_C6,    30,  30 },
  { NOTE_C6,    15,  30 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    30,  30 },
  { NOTE_E6,    15,  15 },
  { NOTE_C6,    30,  30 },
  { NOTE_A5,    15,  15 },
  { NOTE_G5,    60,  60 },
  { NOTE_C6,    15,  15 },
  { NOTE_C6,    30,  30 },
  { NOTE_C6,    15,  30 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    30,  30 },
  { NOTE_E6,    15,  15 },
  { NOTE_SPC,   60,  60 },
  { NOTE_C6,    15,  15 },
  { NOTE_C6,    30,  30 },
  { NOTE_C6,    15,  30 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    30,  30 },
  { NOTE_E6,    15,  15 },
  { NOTE_C6,    30,  30 },
  { NOTE_A5,    15,  15 },
  { NOTE_G5,    60,  60 },
  { NOTE_C6,    15,  15 },
  { NOTE_C6,    30,  30 },
  { NOTE_C6,    15,  30 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    30,  30 },
  { NOTE_E6,    15,  15 },
  { NOTE_SPC,   60,  60 },
  { NOTE_C6,    45,  45 },
  { NOTE_G5,    15,  45 },
  { NOTE_E5,    30,  45 },
  { NOTE_A5,    30,  30 },
  { NOTE_B5,    15,  30 },
  { NOTE_AS5,   15,  15 },
  { NOTE_A5,    30,  30 },
  { NOTE_G5,    21,  21 },
  { NOTE_E6,    21,  21 },
  { NOTE_G6,    15,  15 },
  { NOTE_A6,    30,  30 },
  { NOTE_F6,    15,  15 },
  { NOTE_G6,    15,  30 },
  { NOTE_E6,    30,  30 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    15,  15 },
  { NOTE_B5,    45,  45 },
  { NOTE_C6,    45,  45 },
  { NOTE_G5,    15,  45 },
  { NOTE_E5,    30,  45 },
  { NOTE_A5,    30,  30 },
  { NOTE_B5,    15,  30 },
  { NOTE_AS5,   15,  15 },
  { NOTE_A5,    30,  30 },
  { NOTE_G5,    21,  21 },
  { NOTE_E6,    21,  21 },
  { NOTE_G6,    15,  15 },
  { NOTE_A6,    30,  30 },
  { NOTE_F6,    15,  15 },
  { NOTE_G6,    15,  30 },
  { NOTE_E6,    30,  30 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    15,  15 },
  { NOTE_B5,    45,  60 },
  { NOTE_G6,    15,  15 },
  { NOTE_FS6,   15,  15 },
  { NOTE_F6,    15,  15 },
  { NOTE_DS6,   30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_GS5,   15,  15 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  30 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    15,  15 },
  { NOTE_SPC,   15,  15 },
  { NOTE_G6,    15,  15 },
  { NOTE_FS6,   15,  15 },
  { NOTE_F6,    15,  15 },
  { NOTE_DS6,   30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_C7,    30,  30 },
  { NOTE_C7,    15,  15 },
  { NOTE_C7,    60,  60 },
  { NOTE_G6,    15,  15 },
  { NOTE_FS6,   15,  15 },
  { NOTE_F6,    15,  15 },
  { NOTE_DS6,   30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_GS5,   15,  15 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  30 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    15,  45 },
  { NOTE_DS6,   30,  45 },
  { NOTE_D6,    45,  45 },
  { NOTE_C6,    60, 120 },
  { NOTE_G6,    15,  15 },
  { NOTE_FS6,   15,  15 },
  { NOTE_F6,    15,  15 },
  { NOTE_DS6,   30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_GS5,   15,  15 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  30 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    15,  15 },
  { NOTE_SPC,   15,  15 },
  { NOTE_G6,    15,  15 },
  { NOTE_FS6,   15,  15 },
  { NOTE_F6,    15,  15 },
  { NOTE_DS6,   30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_C7,    30,  30 },
  { NOTE_C7,    15,  15 },
  { NOTE_C7,    60,  60 },
  { NOTE_G6,    15,  15 },
  { NOTE_FS6,   15,  15 },
  { NOTE_F6,    15,  15 },
  { NOTE_DS6,   30,  30 },
  { NOTE_E6,    15,  30 },
  { NOTE_GS5,   15,  15 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  30 },
  { NOTE_A5,    15,  15 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    15,  45 },
  { NOTE_DS6,   30,  45 },
  { NOTE_D6,    45,  45 },
  { NOTE_C6,    60, 120 },
  { NOTE_C6,    15,  15 },
  { NOTE_C6,    30,  30 },
  { NOTE_C6,    15,  30 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    30,  30 },
  { NOTE_E6,    15,  15 },
  { NOTE_C6,    30,  30 },
  { NOTE_A5,    15,  15 },
  { NOTE_G5,    60,  60 },
  { NOTE_C6,    15,  15 },
  { NOTE_C6,    30,  30 },
  { NOTE_C6,    15,  30 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    30,  30 },
  { NOTE_E6,    15,  15 },
  { NOTE_SPC,   60,  60 },
  { NOTE_C6,    15,  15 },
  { NOTE_C6,    30,  30 },
  { NOTE_C6,    15,  30 },
  { NOTE_C6,    15,  15 },
  { NOTE_D6,    30,  30 },
  { NOTE_E6,    15,  15 },
  { NOTE_C6,    30,  30 },
  { NOTE_A5,    15,  15 },
  { NOTE_G5,    60,  60 },
  { NOTE_C6,    15,  15 },
  { NOTE_C6,    30,  30 },
  { NOTE_C6,    15,  30 },
  { NOTE_G5,    15,  15 },
  { NOTE_D6,    30,  30 },
  { NOTE_C6,   240, 240 },
  { NOTE_END,    0,   0 }
};
const note_item melodie_4[] PROGMEM = {
  { NOTE_A4,    25,  25 },
  { NOTE_E3,    25,  25 },
  { NOTE_A4,    25,  25 },
  { NOTE_SPC,   12,  13 },
  { NOTE_A4,    25,  25 },
  { NOTE_E3,    25,  25 },
  { NOTE_A4,    25,  25 },
  { NOTE_SPC,   12,  13 },
  { NOTE_E4,    12,  13 },
  { NOTE_D4,    12,  13 },
  { NOTE_C4,    12,  13 },
  { NOTE_B4,    12,  13 },
  { NOTE_A4,    12,  13 },
  { NOTE_B4,    12,  13 },
  { NOTE_C4,    12,  13 },
  { NOTE_D4,    12,  13 },
  { NOTE_E4,    25,  25 },
  { NOTE_E3,    25,  25 },
  { NOTE_A4,    25,  25 },
  { NOTE_END,    0,   0 }
};
const note_item melodie_5[] PROGMEM = {
  { NOTE_G4,    35,  35 },
  { NOTE_G4,    35,  35 },
  { NOTE_G4,    35,  35 },
  { NOTE_DS4,   25,  25 },
  { NOTE_AS4,   10,  10 },
  { NOTE_G4,    35,  35 },
  { NOTE_DS4,   25,  25 },
  { NOTE_AS4,   10,  10 },
  { NOTE_G4,    70,  70 },
  { NOTE_D5,    35,  35 },
  { NOTE_D5,    35,  35 },
  { NOTE_D5,    35,  35 },
  { NOTE_DS5,   25,  25 },
  { NOTE_AS4,   10,  10 },
  { NOTE_FS4,   35,  35 },
  { NOTE_DS4,   25,  25 },
  { NOTE_AS4,   10,  10 },
  { NOTE_G4,    70,  70 },
  { NOTE_G5,    35,  35 },
  { NOTE_G4,    25,  25 },
  { NOTE_G4,    10,  10 },
  { NOTE_G5,    35,  35 },
  { NOTE_FS5,   25,  25 },
  { NOTE_F5,    10,  10 },
  { NOTE_E5,    10,  10 },
  { NOTE_DS5,   10,  10 },
  { NOTE_E5,    45,  45 },
  { NOTE_GS4,   15,  15 },
  { NOTE_CS5,   35,  35 },
  { NOTE_C5,    25,  25 },
  { NOTE_B4,    10,  10 },
  { NOTE_AS4,   10,  10 },
  { NOTE_A4,    10,  10 },
  { NOTE_AS4,   45,  45 },
  { NOTE_DS4,   15,  15 },
  { NOTE_FS4,   35,  35 },
  { NOTE_DS4,   25,  25 },
  { NOTE_AS4,   10,  10 },
  { NOTE_G4,    75,  75 },
  { NOTE_END,    0,   0 }
};
const note_item* melodies_notes[] = {
  melodie_1,
  melodie_2,
  melodie_3,
  melodie_4,
  melodie_5,
  NULL
};