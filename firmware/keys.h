#ifndef __MIDI_FIGHTER_KEYBOARD
#define __MIDI_FIGHTER_KEYBOARD

#include <Arduino.h>
#include <stdint.h>

#include "types.h"

class Keys {

  private:
    uint32_t m_oldLights;
    uint32_t m_lights;
    uint32_t m_oldButtons;
    uint32_t m_buttons;

  public:
    Keys();

  private:
    void write();
    void read();

  public:
    void begin();
    void update();

    keystate_t getKey(uint8_t id);
    keystate_t getKey(uint8_t col, uint8_t row);
    void setKey(uint8_t id, bool light);
    void setKey(uint8_t col, uint8_t row, bool light);

};

#endif
