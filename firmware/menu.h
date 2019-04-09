#ifndef __MIDI_FIGHTER_MENU
#define __MIDI_FIGHTER_MENU

#include <Arduino.h>
#include <stdint.h>
#include "types.h"
#include "ui.h"

/* An abstract menu */
class Menu {
  public:
    virtual void reset(UI* parent) = 0;
    virtual void update(UI* parent) = 0;
    virtual void draw(UI* parent, bool firstTime = false) = 0;
};

/* A menu that lists items */
class MenuList : public Menu {
  public:
    /* An item of the list */
    struct Item {
      const char* name;
      Menu* target;
    };
    /* The menu alignment */
    enum Align {
      Left,
      Center
    };

  private:
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
