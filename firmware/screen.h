#ifndef __MIDI_FIGHTER_SCREEN
#define __MIDI_FIGHTER_SCREEN

#include <Arduino.h>
#include <SerLCD.h>
#include <stdint.h>

#include "types.h"

class Screen {

  private:
    SerLCD* m_lcd;
    screendata_t m_data;

  public:
    Screen();

  public:
    void begin();

    void clear();
    void write(const char* text);
    void write(String text);
    void put(char cara);

    void setBacklight(const color_t& color);
    void setBacklight(uint32_t color);
    void setBacklight(uint8_t r, uint8_t g, uint8_t b);
    void setContrast(uint8_t contrast);
    void setCursor(uint8_t x, uint8_t y);

};

#endif
