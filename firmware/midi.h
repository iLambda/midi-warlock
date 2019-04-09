#ifndef __MIDI_FIGHTER_MIDI
#define __MIDI_FIGHTER_MIDI

#include <Arduino.h>
#include <stdint.h>

#include "types.h"

#define MIDI_NO_DATA_BYTE                0xFF
#define MIDI_NO_DATA_MASK                0x80

#define MIDI_STATUS_NOTE_OFF             0b10000000
#define MIDI_STATUS_NOTE_ON              0b10010000
#define MIDI_STATUS_CONTROL_CHANGE       0b10110000
#define MIDI_STATUS_PROGRAM_CHANGE       0b11000000
#define MIDI_STATUS_PITCH_WHEEL          0b11100000

class Midi {

  private:
    HardwareSerial* m_uart;

  public:
    Midi(HardwareSerial* uart);

  public:
    void begin();
    void send(const MIDImsg_t& message);

    MIDImsg_t noteOn(uint8_t channel, uint8_t note, uint8_t velocity = 255);
    MIDImsg_t noteOff(uint8_t channel, uint8_t note, uint8_t velocity = 255);
    MIDImsg_t controlChange(uint8_t channel, uint8_t controllerID, uint8_t value);
    MIDImsg_t programChange(uint8_t channel, uint8_t patchID);
    MIDImsg_t pitchWheel(uint8_t channel, uint16_t value);
};


#endif
