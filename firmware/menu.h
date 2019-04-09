#ifndef __MIDI_FIGHTER_MENU
#define __MIDI_FIGHTER_MENU

#include <Arduino.h>
#include <stdint.h>
#include "types.h"
#include "ui.h"

class Menu {
  public:
    virtual void reset(UI* parent) = 0;
    virtual void update(UI* parent) = 0;
    virtual void draw(UI* parent, bool firstTime = false) = 0;
};

class MenuList : public Menu {
  public:
    struct Item {
      const char* name;
      Menu* target;
    };

    enum Align {
      Left,
      Center
    };

  public:
    const Item* m_items;
    uint8_t m_nbItems;
    uint8_t m_selected;
    Align m_align;
  
  public:
    MenuList(uint8_t nbItems, const Item items[], Align align = Align::Center);
    
  public:
    virtual void reset(UI* parent) override;
    virtual void update(UI* parent) override;   
    virtual void draw(UI* parent, bool firstTime = false) override;
};



#endif
