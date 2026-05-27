// ... Your 4-layer keymaps matrix lives right above this ...

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Left Side Encoder (Your only encoder)
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false; // Tells QMK to ignore any hardcoded background defaults
}
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270; 
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("MS TR\n"), false);
        oled_write_P(PSTR("Layer\n"), false);
        switch (get_highest_layer(layer_state)) {
            case 0:  oled_write_P(PSTR("BASE \n"), false); break;
            case 1:  oled_write_P(PSTR("LWR  \n"), false); break;
            case 2:  oled_write_P(PSTR("RSE  \n"), false); break;
            default: oled_write_P(PSTR("ADJ  \n"), false); break;
        }
    } else {
        oled_write_P(PSTR("SLAVE\n"), false);
    }
    return false;
}
#endif
