#include "keys.h"

const int LIGHTSER_Pin = 10;
const int LIGHTRCLK_Pin = 9;
const int LIGHTSRCLK_Pin = 8;
const int BUTTONSER_Pin = 4;
const int BUTTONRCLK_Pin = 2;
const int BUTTONSRCLK_Pin = 3;

Keys::Keys() {
  /* Default states */
  this->m_lights = 0x00;
  this->m_buttons = 0x00;
}

void Keys::begin() {
  /* Initialize lights */
  pinMode(LIGHTSER_Pin, OUTPUT);
  pinMode(LIGHTRCLK_Pin, OUTPUT);
  pinMode(LIGHTSRCLK_Pin, OUTPUT);
  
  /* Initialize buttons */
  pinMode(BUTTONSER_Pin, INPUT);
  pinMode(BUTTONRCLK_Pin, OUTPUT);
  pinMode(BUTTONSRCLK_Pin, OUTPUT);

  /* Reset */
  this->write();
}

void Keys::write() {
  /* Lower RCLK : send data */
  digitalWrite(LIGHTRCLK_Pin, LOW);
  /* Send all data */
  for(int8_t i = 29; i >= -2; i--){
    /* Clock low */
    digitalWrite(LIGHTSRCLK_Pin, LOW);
    /* Data */
    digitalWrite(LIGHTSER_Pin, !!(this->m_lights & (((uint32_t)1) << (i % 32))) ? HIGH : LOW);
    /* Clock high */
    digitalWrite(LIGHTSRCLK_Pin, HIGH);
  }
  /* Raise RCLK : stop sending data */
  digitalWrite(LIGHTRCLK_Pin, HIGH);

}

void Keys::read() {
  /* Pulse the latch pin */
  digitalWrite(BUTTONSRCLK_Pin, HIGH);
  delayMicroseconds(20);
  digitalWrite(BUTTONSRCLK_Pin, LOW);

  /* Reset data */
  this->m_oldButtons = this->m_buttons;
  this->m_buttons = 0;

  /* Get all data */
  uint8_t tmp = 0;
  for (int8_t i = 0; i < 4; i++) {
    for (int8_t j = 5; j >= -2; j--) {
      /* Lower clock */
      digitalWrite(BUTTONRCLK_Pin, LOW);
      delayMicroseconds(2);
      /* Read data */
      uint32_t value = digitalRead(BUTTONSER_Pin) == HIGH ? 0 : 1;
      this->m_buttons |= (value << ((i << 3) + j));
      /* Up clock */
      digitalWrite(BUTTONRCLK_Pin, HIGH);
    }
  }
}


void Keys::update() {
  /* Check */
  if (this->m_lights != this->m_oldLights) {
    /* Write */
    this->write();
  }
  /* Read */
  this->read();
  
  /* Iterate */
  this->m_oldLights = this->m_lights;
}

keystate_t Keys::getKey(uint8_t col, uint8_t row) {
  /* Make a keystate */
  keystate_t keystate;
  
  /* Gather the bit number : (row * 8) + col */
  uint8_t lightbitid = ((row & 0x07) << 3) + (col & 0x07);
  keystate.light = !!(this->m_lights & (((uint32_t)1) << lightbitid));
  
  /* Gather the bit number : (row * 8) + col */
  uint8_t buttonbitid = ((row & 0x07) << 3) + (col & 0x07);
  keystate.button = !!(this->m_buttons & (((uint32_t)1) << buttonbitid));
  keystate.pastButton = !!(this->m_oldButtons & (((uint32_t)1) << buttonbitid));
  /* Return */
  return keystate;
}

void Keys::setKey(uint8_t col, uint8_t row, bool state) {
  /* Gather the bit number : (row * 8) + col */
  uint8_t bitid = ((row & 0x07) << 3) + (col & 0x07);
  /* Set light state : clear bit and then xor bit */
  this->m_lights &= ~(((uint32_t)1) << bitid);
  this->m_lights |= ((((uint32_t)1) << bitid) * (!!state));
}
