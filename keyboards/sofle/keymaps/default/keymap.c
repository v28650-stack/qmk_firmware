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

// Frame pointers
static const char *dragon_frames[] = {
    dragon_frame_0,
    dragon_frame_1,
    dragon_frame_2,
    dragon_frame_3,
    dragon_frame_4,
    dragon_frame_5,
    dragon_frame_6,
    dragon_frame_7,
};

static const char *bunny_frames[] = {
    bunny_frame_0,
    bunny_frame_1,
    bunny_frame_2,
    bunny_frame_3,
    bunny_frame_4,
    bunny_frame_5,
    bunny_frame_6,
    bunny_frame_7,
};

// Keymap layers
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

// OLED animation logic
void render_sprite(void) {
    const char **frames = current_sprite == SPRITE_DRAGON ? dragon_frames : bunny_frames;
    oled_write_raw_P(frames[current_frame], 128 * 4);
}

bool oled_task_user(void) {
    if (timer_elapsed32(anim_timer) > 200) {
        anim_timer = timer_read32();
        current_frame = (current_frame + 1) % 8;
    }

    render_sprite();
    return false;
}

// Encoder update (empty, since we disabled encoders)
bool encoder_update_user(uint8_t index, bool clockwise) {
    return true;
}
