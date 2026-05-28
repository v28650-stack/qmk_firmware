#pragma once

// If your firmware already defines split settings, keep this minimal

#define TAPPING_TERM 180

// Recommended for Sofle-style boards
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

// If OLED exists in your build (safe to leave even if unused)
#ifdef OLED_ENABLE
#define OLED_TIMEOUT 30000
#endif
