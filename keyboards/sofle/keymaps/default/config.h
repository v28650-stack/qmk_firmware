#pragma once

// Explicitly define the physical encoder pins for the Sofle Rev1 layout
#define ENCODERS_PAD_A { F4, F5 }
#define ENCODERS_PAD_B { F1, F0 }
#define ENCODER_RESOLUTION 4

// Tear down the base firmware's hardcoded RGB encoder definitions
#undef ENCODER_MAP_ENABLE
