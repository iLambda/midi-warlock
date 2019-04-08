#ifndef __MIDI_FIGHTER_MEMORY
#define __MIDI_FIGHTER_MEMORY

#include <Arduino.h>
#include <EEPROM24.h>
#include <stdint.h>

#include "types.h"

class Memory {

  private:
    EEPROM24* m_eeprom;
    uint8_t m_i2cAddress;

  public:
    Memory(uint8_t i2cAddress);

  public:
    void begin();

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);

};


#endif
