#pragma once

#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 4095

// Fix for Pico SDK macro conflicts
#undef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// Include Pico SDK pin definitions
#include "pico/stdlib.h"

// Encoder configuration for RP2040 Helios
#define ENCODERS_PAD_A { GP18 }
#define ENCODERS_PAD_B { GP19 }
