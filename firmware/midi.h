#ifndef __MIDI_FIGHTER_MIDI
#define __MIDI_FIGHTER_MIDI

#include <Arduino.h>
#include <stdint.h>

#include "types.h"

class Midi {

  private:
    HardwareSerial* m_uart;

  public:
    Midi(HardwareSerial* uart);

  public:
    void begin();

};


#endif
