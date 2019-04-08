#include "memory.h"

EEPROM24* m_eeprom;
uint8_t m_i2cAddress;

Memory::Memory(uint8_t i2cAddress) {
  /* Initialize address */
  this->m_i2cAddress = i2cAddress;
}

void Memory::begin() {
  /* Initialize eeprom */
  this->m_eeprom = new EEPROM24(this->m_i2cAddress, true);
}

uint8_t Memory::read(uint16_t addr) {
  /* Read */
  return (uint8_t)this->m_eeprom->read(addr);
}
void Memory::write(uint16_t addr, uint8_t data) {
  /* Write */
  this->m_eeprom->write(addr, data);
}

void Memory::writeSafe(uint16_t addr, uint8_t data) {
  /* Read @addr to see if data has been updated */
  if (this->read(addr) != data) {
    /* OK to Write */
    this->write(addr, data);
  }
}
