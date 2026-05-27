#pragma once

// Clear baseline hardware overrides to prevent duplication errors
#undef ENCODERS_PAD_A
#undef ENCODERS_PAD_B
#undef ENCODER_RESOLUTION

// Correct native single-pin encoder routes for Sofle Rev1
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODER_RESOLUTION 2

// De-register layout maps to enforce direct user callbacks
#undef ENCODER_MAP_ENABLE
