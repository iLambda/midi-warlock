#include <Wire.h>

#include "input.h"
#include "keys.h"
#include "memory.h"
#include "menu.h"
#include "midi.h"
#include "screen.h"
#include "types.h"
#include "ui.h"

/* The peripherals */
Screen screen;
Input input;
Keys keys;
Midi midi(&Serial3);
Memory externalMemory(I2C_EXTERNAL_EEPROM_ADDRESS);

/* The UI */
UI ui(&screen, &input);
/* The actual menu */
MenuList keymapMenu { 3, (MenuList::Item[])
  {
    {"Swap", nullptr},
    {"Edit", nullptr},
    {"<BACK>", nullptr}
  }
};

MenuList mainMenu { 3, (MenuList::Item[])
  {
    {"Keymap", &keymapMenu},
    {"Memory", nullptr},
    {"Settings", nullptr}
  }
};

void setup() {
  /* Initialize serial comms */
  Serial.begin(115200);
  Serial.println("Booting up...");

  /* Initialize I2C */
  Wire.begin();

  /* Initialize peripherals */
  externalMemory.begin();
  screen.begin();
  input.begin();
  keys.begin();
  midi.begin();

  /* OK */
  Serial.println("Booted succesfully !");

  /* Start UI*/
  ui.begin(&mainMenu);

  /* Whatever */
  keys.setKey(0, 0, true);
}

void loop() {

  for (uint8_t id = 0 ; id < 30 ; id++) {
    auto keystate = keys.getKey(id);
    if (!keystate.button && keystate.pastButton) {
      keys.setKey(id, !keystate.light);
    }
  }

  /* Update input */
  input.update();
  keys.update();
  ui.update();

}
