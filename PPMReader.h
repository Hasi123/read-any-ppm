/*
PPMReader library based on https://github.com/Hasi123/read-any-ppm
Works with Servo library

Paweł (DzikuVx) Spychalski 2017
https://quadmeup.com

License: GNU GPL v3
*/

#ifndef PPMReader_h
#define PPMReader_h

#include "Arduino.h"

#define PMM_CHANNEL_COUNT 16

class PPMReader
{
  public:
    PPMReader(int pin, int interrupt);
    int get(uint8_t channel);
    static void handler();
    static int ppm[PMM_CHANNEL_COUNT];
  private:
    int _pin;
    int _interrupt;
};

int PPMReader::ppm[PMM_CHANNEL_COUNT];

#endif