#include "input.h"

const int KNOB_Pin = 5;
const int KNOBDIR_Pin = 6;
const int KNOBBTN_Pin = 7;

Input::Input() : m_knob(false), m_knobPress(false), m_knobDir(false) {

}

void Input::begin() {
  /* Initialize knob */
  pinMode(KNOB_Pin, INPUT);
  pinMode(KNOBDIR_Pin, INPUT);
  pinMode(KNOBBTN_Pin, INPUT_PULLUP);

}

void Input::update() {
  /* Get knob press */
  m_oldKnobPress = m_knobPress;
  m_knobPress = (digitalRead(KNOBBTN_Pin) == HIGH);

  /* Get knob */
  m_oldKnob = m_knob;
  m_knob = (digitalRead(KNOB_Pin) == HIGH);
  m_knobDir = (digitalRead(KNOBDIR_Pin) == LOW);
}

int8_t Input::getKnob(){
  return m_oldKnob && !m_knob
          ? (m_knobDir ? 1 : -1) : 0;
}

bool Input::isKnobPressed() {
  return !m_knobPress && m_oldKnobPress;
}

bool Input::isKnobReleased() {
  return m_knobPress && !m_oldKnobPress;
}
