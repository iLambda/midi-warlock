#include "screen.h"
#include "char.h"

Screen::Screen() {
  /* Initialize fields */
  this->m_lcd = new SerLCD();
  this->m_data = {0};
}

void Screen::begin(){
  /* Initialize LCD */
  this->m_lcd->begin(Wire);
  this->m_lcd->disableSystemMessages();
  this->m_lcd->disableSplash();
  this->m_lcd->noDisplay();
  /* Set default params */
  this->setBacklight(0xFF0000);

  /* Add custom chars */
  this->m_lcd->createChar(0, charmap_up);
  this->m_lcd->createChar(1, charmap_down);
  this->m_lcd->createChar(2, charmap_select);
  this->m_lcd->createChar(3, charmap_selectreverse);
  
  /* Clear */
  this->m_lcd->clear();
  delay(2500);
  this->m_lcd->display();
}

void Screen::clear() {
  this->m_lcd->clear();
}

void Screen::write(const char* text) {
  this->m_lcd->print(text);
}

void Screen::write(String text) {
  this->m_lcd->print(text.c_str());
}

void Screen::put(char cara) {
  this->m_lcd->writeChar(cara);
}

void Screen::setBacklight(const color_t& color) {
  /* Check if different */
  if (colorEquals(this->m_data.backlight, color)) {
    return;
  }
  /* Save */
  this->m_data.backlight = color;
  /* Do */
  this->m_lcd->setBacklight(color.r, color.g, color.b);

}

void Screen::setBacklight(uint32_t hash){
  color_t color;
  color.hash = hash;
  this->setBacklight(color);
}

void Screen::setBacklight(uint8_t r, uint8_t g, uint8_t b){
  color_t color;
  color.r = r;
  color.g = g;
  color.b = b;
  this->setBacklight(color);
}

void Screen::setContrast(uint8_t contrast) {
  /* Check if different */
  if (this->m_data.contrast == contrast) {
    return;
  }
  /* Save */
  this->m_data.contrast = contrast;
  /* Do */
  this->m_lcd->setContrast(contrast);
}

void Screen::setCursor(uint8_t x, uint8_t y) {
  this->m_lcd->setCursor(x, y);
}
