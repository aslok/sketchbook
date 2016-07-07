void setup(){
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
  randomSeed(micros() + readVcc() + analogRead(A4) + analogRead(A5) + analogRead(A6) + analogRead(A7));
}

void loop(){
	long result_float = random(3);
	boolean result = result_float < 1.8;
	digitalWrite(result ? 3 : 2, HIGH);

	while (true);
}

double readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif

  delay(75); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

  /* измерив Vcc с помощью вольтметра и нашей функции readVcc().
   * Далее заменяем константу 1125.3 новой переменной:
   * scale_constant = internal1.1Ref * 1023
   * где
   * internal1.1Ref = 1.1 * Vcc1 (показания_вольтметра) / Vcc2 (показания_функции_readVcc())
   * internal1.1Ref = 1.1 * 4930 / 5138 = 1.05546905410666
   * scale_constant = 1.05546905410666 * 1023 = 1079.74484235111318
   * Это калиброванное значение будет хорошим показателем
   * для измерений AVR чипом, но может зависеть от изменений
   * температуры
   */
   
  // return 1125.3 / result; // Vcc in volts
  return 1079.744842 / result;
}