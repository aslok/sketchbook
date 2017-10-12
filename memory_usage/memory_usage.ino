/*
// *(a + i) можно записать как a[i]
// pa = &a[0];
// pa = a;

sizeof(a) / sizeof(*a)
*/

/**********************************************************************************************************************
Sketch uses 1,536 bytes (10.7%) of program storage space. Maximum is 14,336 bytes.
Global variables use 198 bytes (19.3%) of dynamic memory, leaving 826 bytes for local variables. Maximum is 1,024 bytes.

Sketch uses 4,038 bytes (28.2%) of program storage space. Maximum is 14,336 bytes.
Global variables use 252 bytes (24.6%) of dynamic memory, leaving 772 bytes for local variables. Maximum is 1,024 bytes.
***********************************************************************************************************************/

#include "MemoryFree.h"

void setup() {
  Serial.begin(57600);
  Serial.println();

  Serial.print(F("freeMemory() = "));
  Serial.println(freeMemory());

  char s0[650] = "z";

  char s[11] =     "zxcvbnm,./";
  Serial.println(s);
  Serial.println(sizeof(s) * sizeof(*s));
  Serial.println(s[0]);

  char* s2 = malloc(sizeof(int8_t) * 11);
  s2 =             "qwertyuiop";
  Serial.println(s2);
  Serial.println(sizeof(s2) * sizeof(*s2));
  Serial.println(s2[0]);

  int8_t* s3 = malloc(sizeof(int8_t) * 11);
  s3 =             "asdfghjkl;'";
  Serial.println((char*) s3);
  Serial.println(sizeof(s3) * sizeof(*s3));
  Serial.println((char) s3[0]);

  Serial.println();

  Serial.println((long) &s0, HEX);
  Serial.println((long) &s, HEX);
  Serial.println((long) &s2, HEX);
  Serial.println((long) &s3, HEX);

  Serial.println();

  Serial.println(type(32767));          //  int
  Serial.println(type(32768u));         //  unsigned int
  Serial.println(type(65535u));         //  unsigned int
  Serial.println(type(2147483647));     //  long
  Serial.println(type(2147483648u));    //  unsigned long
  Serial.println(type(4294967295u));    //  unsigned long
  //Serial.println(type(4294967296u));  //

  Serial.println();

  Serial.println(2000000000 + 147483647);
  Serial.println(2000000000 + 147483647 + 1);
  Serial.println(2000000000u + 147483647 + 1);

  Serial.println();

  Serial.println(3600 * 24 / (79755 / -12));
  Serial.println(3600 * 24 / (79755 / (float) -12));
  Serial.println(3600.0 * 24 / (79755 / (float) -12));
}

void loop() {
}

char* type(char a)          { return "char";            }
char* type(char* a)         { return "char*";           }
char* type(int8_t a)        { return "short";           }
char* type(int8_t* a)       { return "short*";          }
char* type(uint8_t a)       { return "byte";            }
char* type(uint8_t* a)      { return "byte*";           }
char* type(int a)           { return "int";             }
char* type(int* a)          { return "int*";            }
char* type(unsigned int a)  { return "unsigned int";    }
char* type(unsigned int* a) { return "unsigned int*";   }
char* type(long a)          { return "long";            }
char* type(long* a)         { return "long*";           }
char* type(unsigned long a) { return "unsigned long";   }
char* type(unsigned long* a){ return "unsigned long*";  }
char* type(float a)         { return "float";           }
char* type(float* a)        { return "float*";          }
char* type(double a)        { return "double";          }
char* type(double* a)       { return "double*";         }

