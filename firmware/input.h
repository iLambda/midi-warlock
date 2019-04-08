#ifndef __MIDI_FIGHTER_INPUT
#define __MIDI_FIGHTER_INPUT

#include <Arduino.h>
#include <stdint.h>

#include "types.h"

class Input {

  private:
    bool m_oldKnob;
    bool m_oldKnobPress;
    bool m_knob;
    bool m_knobPress;
    bool m_knobDir;

  public:
    Input();

  public:
    void begin();
    void update();

    int8_t getKnob();
    bool isKnobPressed();
    bool isKnobReleased();

};


#endif
