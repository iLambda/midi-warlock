#ifndef __MIDI_FIGHTER_TYPES
#define __MIDI_FIGHTER_TYPES

#include <Arduino.h>
#include <stdint.h>

#define NB_BUTTONS_ROW 6
#define NB_BUTTONS_COL 5
#define NB_BUTTONS     NB_BUTTONS_ROW * NB_BUTTONS_COL

#define I2C_LCD_ADDRESS                   0x72
#define I2C_EXTERNAL_EEPROM_ADDRESS       0xA0

/*
 * PACKED DATA STRUCTURES
 */

/* A 3-byte color */
typedef union __attribute__((packed)) {
  /* The hex hash */
  uint32_t hash : 24;
  /* The color components */
  struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
  };
} color_t;

inline bool colorEquals(const color_t &a, const color_t &b) {
  return a.r == b.r && a.g == b.g && a.b == b.b;
}

/*
 * UNALIGNED DATA STRUCTURES
 */

typedef struct {
  /* The screen color */
  color_t backlight;
  /* The constrast */
  uint8_t contrast;
} screendata_t;

typedef struct __attribute__((packed)) {
  /* The light */
  uint8_t light : 1;
  /* The button */
  uint8_t pastButton : 1;
  uint8_t button : 1;
} keystate_t;

#endif
