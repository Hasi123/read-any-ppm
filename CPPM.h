/*
  CPPM.h - Library for reading a CPPM (PPM SUM) stream using interrupts
  Created by David Hasko, 15.01.2023
  Released under the GPL-3.0 license
*/

#ifndef _CPPM_H
#define _CPPM_H

#include "Arduino.h"

#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PB__) \
  || defined(__AVR_ATmega88__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PB__) \
  || defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168PB__) \
  || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__)
#else
#error MCU not compatible
#endif

//if you need higher resolution than what micros() provide, uncomment the next line
//#define CPPM_USE_TIMER1

//Define the pin number and number of channels you need
bool attachCPPM(const uint8_t pin, const uint8_t count = 8);
//Disables the interrupt and frees up some memory
void detachCPPM(void);
//Returns the requested ppm channel value
int16_t CPPMget(const uint8_t channel);
void CPPMintFunc(void);

#endif