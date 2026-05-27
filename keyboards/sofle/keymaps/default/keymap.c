#include QMK_KEYBOARD_H
#include "dragon_sprites.h"
#include "bunny_sprites.h"

// Animation state
static uint32_t anim_timer = 0;
static uint8_t current_frame = 0;

// Sprite selection
typedef enum {
    SPRITE_DRAGON = 0,
    SPRITE_BUNNY = 1
} sprite_mode_t;

static sprite_mode_t current_sprite = SPRITE_DRAGON;

// Frame pointers (MUST match the names in the sprite headers)
static const uint8_t *dragon_frames[] = {
    dragon_frame_0,
    dragon_frame_1,
    dragon_frame_2,
    dragon_frame_3,
    dragon_frame_4,
    dragon_frame_5,
    dragon_frame_6,
    dragon_frame_7
};

// Bunny frame pointers
static const char PROGMEM *bunny_frames[] = {
    bunny_frame_0,
    bunny_frame_1,
    bunny_frame_2,
    bunny_frame_3,
    bunny_frame_4,
    bunny_frame_5,
    bunny_frame_6,
    bunny_frame_7
};

#define FRAME_COUNT 8
#define FRAME_DELAY 200  // milliseconds between frames
#define ANIM_SIZE 128    // 32x32 pixels = 1024 bits / 8 = 128 bytes per frame

// Custom keycodes
enum custom_keycodes {
    SPRITE_SW = SAFE_RANGE,  // Switch sprite
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE, XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, MO(1),   KC_SPC,                    KC_ENT,  MO(2),   KC_RGUI, KC_RALT, KC_RCTL
    ),
    [1] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
        _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______
    )
};

// Render current sprite
void render_sprite(void) {
    // Update animation frame
    if (timer_elapsed32(anim_timer) > FRAME_DELAY) {
        anim_timer = timer_read32();
        current_frame = (current_frame + 1) % FRAME_COUNT;
    }
    
    // Display the current sprite at position (0, 0)
    oled_set_cursor(0, 0);
    
    if (current_sprite == SPRITE_DRAGON) {
        oled_write_raw_P(dragon_frames[current_frame], ANIM_SIZE);
    } else {
        oled_write_raw_P(bunny_frames[current_frame], ANIM_SIZE);
    }
}

// Switch between sprites
void switch_sprite(void) {
    current_sprite = (current_sprite == SPRITE_DRAGON) ? SPRITE_BUNNY : SPRITE_DRAGON;
    current_frame = 0;  // Reset animation
    anim_timer = timer_read32();
}

// OLED task
void oled_task_user(void) {
    // Render the sprite animation
    render_sprite();
    
    // Display sprite name on the right side (after the 32px sprite)
    oled_set_cursor(8, 0);
    if (current_sprite == SPRITE_DRAGON) {
        oled_write_P(PSTR("Dragon"), false);
    } else {
        oled_write_P(PSTR("Bunny "), false);
    }
    
    // Display WPM if enabled
    oled_set_cursor(8, 1);
    oled_write_P(PSTR("WPM: "), false);
    uint8_t n = get_current_wpm();
    char wpm_str[4];
    wpm_str[3] = '\0';
    wpm_str[2] = '0' + n % 10;
    wpm_str[1] = '0' + (n /= 10) % 10;
    wpm_str[0] = '0' + n / 10;
    oled_write(wpm_str, false);
}

// Custom keycode handling
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPRITE_SW:
            if (record->event.pressed) {
                switch_sprite();
            }
            return false;
        default:
            return true;
    }
}

// Encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return false;
}
