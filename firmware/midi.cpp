#include "midi.h"

Midi::Midi(HardwareSerial* uart) {
  /* Set UART port */
  this->m_uart = uart;
}

void Midi::begin() {
  /* Initialize UART */
  this->m_uart->begin(31250);
}

void Midi::send(const MIDImsg_t& message) {
  /* Send status & first byte */
  this->m_uart->write(message.status);
  this->m_uart->write(message.data1);
  /* Send second byte iff has data*/
  if (!(message.data2 & MIDI_NO_DATA_MASK)) {
    this->m_uart->write(message.data2);
  }
}

MIDImsg_t Midi::noteOn(uint8_t channel, uint8_t note, uint8_t velocity = 255) {
  /* Return */
  return midiMake(
    MIDI_STATUS_NOTE_ON | (channel & 0x0F),
    note & 0x7F,
    velocity & 0x7F);
}

MIDImsg_t Midi::noteOff(uint8_t channel, uint8_t note, uint8_t velocity = 255) {
  /* Return */
  return midiMake(
    MIDI_STATUS_NOTE_OFF | (channel & 0x0F),
    note & 0x7F,
    velocity & 0x7F);
}

MIDImsg_t Midi::controlChange(uint8_t channel, uint8_t controller, uint8_t value) {
  /* Return */
  return midiMake(
    MIDI_STATUS_CONTROL_CHANGE | (channel & 0x0F),
    controller & 0x7F,
    value & 0x7F);
}

MIDImsg_t Midi::programChange(uint8_t channel, uint8_t patchID) {
  /* Return */
  return midiMake(
    MIDI_STATUS_PROGRAM_CHANGE | (channel & 0x0F),
    patchID & 0x7F,
    MIDI_NO_DATA_BYTE);
}

MIDImsg_t Midi::pitchWheel(uint8_t channel, uint16_t value) {
  /* Return */
  return midiMake(
    MIDI_STATUS_CONTROL_CHANGE | (channel & 0x0F),
    value & 0x7F,
    (value >> 7) & 0x7F);
}
