#include "midi.h"

Midi::Midi(HardwareSerial* uart) {
  /* Set UART port */
  this->m_uart = uart;
}

void Midi::begin() {
  /* Initialize UART */
  this->m_uart->begin(31250);
}
