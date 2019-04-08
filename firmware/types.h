#ifndef __MIDI_FIGHTER_TYPES
#define __MIDI_FIGHTER_TYPES

#include <Arduino.h>
#include <stdint.h>

#define NB_BUTTONS_ROW 6
#define NB_BUTTONS_COL 5
#define NB_BUTTONS     NB_BUTTONS_ROW * NB_BUTTONS_COL

#define I2C_LCD_ADDRESS                   0x72
#define I2C_EXTERNAL_EEPROM_ADDRESS       0xA0

/*********************************
 *                               *
 *    PACKED DATA STRUCTURES     *
 *                               *
 *********************************/

/*
 * COLOR
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

/*
 * MIDI DATA
 */

/* A midi message */
typedef struct __attribute__((packed)) {
  /* Command */
  union {
    /* The status byte as is */
    uint8_t status;
    /* The command/channel */
    struct {
      /* The channel */
      uint8_t channel : 4;
      /* The command */
      uint8_t command : 4;
    };
  };
  /* The data */
  union {
    /* The data */
    uint16_t data;
    /* The 2 bytes of data */
    struct {
      /* The lower half of data */
      uint8_t data1;
      /* The higher half of data */
      uint8_t data2;
    };
  };
} MIDImsg_t;

/*
 * GLOBAL SETTINGS
 */
typedef struct __attribute__((packed)) {
  /* Allocate 64 unused bytes */
  uint64_t unused;
} settings_t;

/*
 * KEYMAPS
 */

/* The mode of a key */
typedef enum {
  KEY_MODE_TOGGLE = 0,
  KEY_MODE_INSTANT = 1
} keymode_t;

/* A key */
typedef struct __attribute__((packed)) {
  /* The configuration */
  union {
    /* The config byte */
    uint8_t cfg;
    /* The fields */
    struct {
      /* The keymode */
      keymode_t mode : 1;
    };
  };
  /* A midi message */
  MIDImsg_t msg;

} keydata_t;

/* A keymap */
typedef struct __attribute__((packed)) {
  /* The color of the screen */
  color_t backlight;
  /* The keys */
  keydata_t keys[NB_BUTTONS];

} keymap_t;



/*********************************
 *                               *
 *     MISC DATA STRUCTURES      *
 *                               *
 *********************************/

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



/*********************************
 *                               *
 *        HELPER FUNCTIONS       *
 *                               *
 *********************************/

inline bool colorEquals(const color_t &a, const color_t &b) {
  return a.r == b.r && a.g == b.g && a.b == b.b;
}

#endif
