#pragma once

// Force QMK's serial driver to use the exact hardware pin mapped to the TRRS/TRS cable jack
#define SERIAL_USART_TX_PIN GP1

// Allow layout mutations via VIA
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 4095
