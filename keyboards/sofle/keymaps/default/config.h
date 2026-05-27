#pragma once

// Clear baseline hardware overrides to prevent duplication errors
#undef ENCODERS_PAD_A
#undef ENCODERS_PAD_B
#undef ENCODER_RESOLUTION

// Force standard RP2040 custom pin layouts
#define ENCODERS_PAD_A { F4, F5 }
#define ENCODERS_PAD_B { F1, F0 }
#define ENCODER_RESOLUTION 4

// De-register layout maps to enforce direct user callbacks
#undef ENCODER_MAP_ENABLE
