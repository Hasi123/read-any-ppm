/*
  CPPM.cpp - Library for reading a CPPM (PPM SUM) stream using interrupts
  Created by David Hasko, 15.01.2023
  Released under the GPL-3.0 license
*/

#include "Arduino.h"
#include "CPPM.h"

static uint8_t _cppm_count;
static volatile int16_t *_cppm_val;

bool attachCPPM(const uint8_t pin, const uint8_t count) {
  if (pin > 19)
    return false;

  _cppm_count = count;
#if 0
  _cppm_val = (int16_t *)calloc(_cppm_count, sizeof(int16_t));
#else
  //smaller code?
  _cppm_val = (int16_t *)malloc(_cppm_count * sizeof(int16_t));
  memset((void *)_cppm_val, 0, _cppm_count * sizeof(int16_t));
#endif

//configure timer1
#ifdef CPPM_USE_TIMER1
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS11);
#endif

  //configure pin
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  volatile uint8_t *ddrReg = portModeRegister(port);
  volatile uint8_t *pcmskReg = digitalPinToPCMSK(pin);

  *ddrReg &= ~bit;        //INPUT
  *pcmskReg = bit;        //select pin
  PCICR = _BV(port - 2);  //enable pin change interrupt

  return true;
}

void detachCPPM(void) {
  PCICR = 0;
  free((void *)_cppm_val);
}

int16_t CPPMget(const uint8_t channel) {
  if (channel > _cppm_count)
    return -1;
  return _cppm_val[channel];
}

void CPPMintFunc(void) {
  static uint16_t pulse;
  static uint16_t counter;
  static uint8_t channel;

#ifdef CPPM_USE_TIMER1
  counter = TCNT1;
  TCNT1 = 0;
  counter /= (F_CPU / 8000000);
#else
  static uint32_t last_time;
  uint32_t current_micros = micros();
  counter = current_micros - last_time;
  last_time = current_micros;
#endif

  if (counter < 520) {  //must be a pulse if less than 520us
    pulse = counter;
  } else if (counter > 1910) {  //sync pulses over 1910us
    channel = 0;
  } else {  //servo values
    if (channel < _cppm_count) {
      _cppm_val[channel] = counter + pulse;
    }
    channel++;
  }
}

ISR(PCINT0_vect) {
  CPPMintFunc();
}

ISR(PCINT1_vect) {
  CPPMintFunc();
}

ISR(PCINT2_vect) {
  CPPMintFunc();
}
