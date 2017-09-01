//Header file for Arduino Morse Code
/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef MorseTwoButton_h
#define MorseTwoButton_h

#include "Arduino.h"

class MorseTwoButton
{
  public:
    Morse(int pin, int pin);
    void outCode();
  private:
    int _pin;
};

#endif
