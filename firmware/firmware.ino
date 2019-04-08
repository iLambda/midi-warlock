#include <Wire.h>

#include "input.h"
#include "keys.h"
#include "memory.h"
#include "midi.h"
#include "screen.h"
#include "types.h"

/* The screen */
Screen screen;
/* The input */
Input input;
/* The kbd */
Keys keys;
/* The midi port */
Midi midi(&Serial3);
/* The memory */
Memory externalMemory(I2C_EXTERNAL_EEPROM_ADDRESS);

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

  screen.write("Key : (0;0)");
  keys.setKey(0, 0, true);
}

void loop() {

  for (uint8_t x = 0 ; x < 6 ; x++) {
    for(uint8_t y = 0 ; y < 5 ; y++) {
      auto keystate = keys.getKey(x, y);
      if (!keystate.button && keystate.pastButton) {
        keys.setKey(x, y, !keystate.light);
        screen.clear();
        screen.write(String("Key : (") + x + ";" + y + ")");
      }

    }
  }

  /* Update input */
  input.update();
  keys.update();

}
