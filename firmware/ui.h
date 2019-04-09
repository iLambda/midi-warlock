#ifndef __MIDI_FIGHTER_UI
#define __MIDI_FIGHTER_UI

#include <Arduino.h>
#include <stdint.h>

#include "input.h"
#include "screen.h"
#include "types.h"

class Menu;
class UI {

  struct Backstack {
    Backstack* previous;
    Menu* menu;
  };

  private:
    Screen* m_screen;
    Input* m_input;
    Backstack* m_history;

  public:
    UI(Screen* screen, Input* input);

  public:
    void begin(Menu* menu);
    void update();

  public:
    Screen* getScreen();
    Input* getInput();
    
    void go(Menu* menu);
    void back();

};


#endif
