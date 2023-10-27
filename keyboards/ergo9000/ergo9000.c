#include "print.h"
#include "qp.h"
#include "unicode.h"
#include "ergo9000.h"
#include "qp_sh1106.h"
#include "fonts/hack_nf_12.qff.h"
#include "fonts/hack_nf_18.qff.h"

// Global variables for the display and fonts and renderable state
static painter_device_t      display;
static painter_font_handle_t hack_nf_12;
static painter_font_handle_t hack_nf_18;
static os_variant_t          os = OS_UNSURE;
static char                  os_name[12] = "??";
static const int             os_area_top = 34; // Y position for the OS indicator area
static const int             os_area_bottom = 62; // Y position for the OS indicator area
static const int             os_area_left = 2; // X position for the OS indicator area
static const int             os_area_right  = 30; // X position for the OS indicator area
static const int             mods_area_top  = os_area_top; // Y position for the modifier area
static const int             mods_area_bottom = os_area_bottom; // Y position for the modifier area
static const int             mods_area_left = 60; // X position for the modifier area
static const int             mods_area_right = 126; // X position for the modifier area


void update_os(os_variant_t new_os) {
    // Only update if the OS variant has changed
    // calculate os string on change, so we don't have to do it every frame
    // of the display rendering loop
    os = new_os; // Update the OS variant
    switch (os) {
        case OS_MACOS:
            sprintf(os_name, "");
            set_unicode_input_mode(UNICODE_MODE_MACOS); // Set Unicode input mode for macOS
            break;
        case OS_IOS:
            sprintf(os_name, "?");
            break;
        case OS_WINDOWS:
            sprintf(os_name, "");
            set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE); // Set Unicode input mode for Windows
            break;
        case OS_LINUX:
            sprintf(os_name, "");
            set_unicode_input_mode(UNICODE_MODE_LINUX); // Set Unicode input mode for Linux
            break;
        case OS_UNSURE:
        default:
            sprintf(os_name, "??");
            break;
    }
}

void clear_os_indicator_area(void) {
    qp_rect(display, os_area_left, os_area_top, os_area_right, os_area_bottom, 0, 0, 0, true);
}

void clear_mods_area(void) {
    qp_rect(display, mods_area_left, mods_area_top, mods_area_right, mods_area_bottom, 0, 0, 0, true);
}

void keyboard_post_init_kb(void) {
    if (is_keyboard_master()) {
        display = qp_sh1106_make_i2c_device(128, 64, OLED_DISPLAY_ADDRESS); // Create the display
        hack_nf_12 = qp_load_font_mem(font_hack_nf_12); // Load the 12pt font
        hack_nf_18 = qp_load_font_mem(font_hack_nf_18); // Load the 18ptfont
        qp_init(display, QP_ROTATION_0);                // Initialise the display
        // draw the initial display
        // outside border
        qp_rect(display, 0, 0, 128, 64, 255, 255, 255, true);

        // top-half black area
        qp_rect(display, 2, 2, 126, 30, 0, 0, 0, true);

        // bottom-half black area
        qp_rect(display, 2, 34, 126, 62, 0, 0, 0, true);

        qp_drawtext(display, 16, 12, hack_nf_12, "Starting...");
        qp_flush(display); // Flush the display to show the initial text

        unicode_input_mode_init(); // Initialize Unicode input mode
    }

}

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    update_os(detected_os);
    return true;
}

void render_top_half_text(char text[16], bool flush) {
    // Clear the top section of the display
    qp_rect(display, 2, 2, 126, 30, 0, 0, 0, true);

    // find the right x offset to center the text
    int x_offset = (126 - qp_textwidth(hack_nf_18, text)) / 2;

    qp_drawtext(display, x_offset, 8, hack_nf_18, text);
    if (flush) {
        qp_flush(display); // Flush the display to show the text
    }
}

void render_layer_indicator(bool flush) {
    // get current active layer
    uint8_t active_layer = get_highest_layer(layer_state);

    // map the active layer to a string
    char layer_name[16] = ""; // Buffer to hold the layer name
    switch (active_layer) {
        case _BASE:
            sprintf(layer_name, "Base");
            break;
        case _LOWER:
            sprintf(layer_name, "Lower");
            break;
        case _RAISE:
            sprintf(layer_name, "Raise");
            break;
        case _ADJUST:
            sprintf(layer_name, "Adjust");
            break;
        default:
            sprintf(layer_name, "???");
            break;
    }

    render_top_half_text(layer_name, flush);
}

void render_os_indicator(bool flush) {
    // Clear the bottom-left section of the display
    clear_os_indicator_area();

    // Draw the OS name in the bottom section
    int x_offset = (os_area_right - os_area_left - qp_textwidth(hack_nf_18, os_name)) / 2;
    qp_drawtext(display, x_offset + 2, os_area_top + 5, hack_nf_18, os_name);
    if (flush) {
        qp_flush(display); // Flush the display to show the OS name
    }
}

void render_mods_area(bool flush) {
    // Clear the modifier area
    clear_mods_area();

    char output_str[17] = ""; // Buffer to hold the active modifier keys

    int mods = get_mods(); // Get the current modifier keys
    int osm = get_oneshot_mods(); // Get the current oneshot modifier keys

    // check if any mods are active
    if (mods == 0 && osm == 0) {
        // No modifier keys are active, display a placeholder
        sprintf(output_str, "    ");
    } else {
        // Display active modifier keys
        if (mods & MOD_MASK_GUI || osm & MOD_MASK_GUI) {
            strcat(output_str, "󰘳");
        } else {
            strcat(output_str, " "); // No GUI key
        }
        if (mods & MOD_MASK_ALT || osm & MOD_MASK_ALT) {
            strcat(output_str, "󰘵");
        } else {
            strcat(output_str, " "); // No ALT key
        }
        if (mods & MOD_MASK_CTRL || osm & MOD_MASK_CTRL) {
            strcat(output_str, "󰘴");
        } else {
            strcat(output_str, " "); // No CTRL key
        }
        if (mods & MOD_MASK_SHIFT || osm & MOD_MASK_SHIFT) {
            strcat(output_str, "󰘶");
        } else {
            strcat(output_str, " "); // No SHIFT key
        }
    }

    // Draw the modifier keys in the area
    qp_drawtext(display, mods_area_left + 4, mods_area_top + 5, hack_nf_18, output_str);
    if (flush) {
        qp_flush(display); // Flush the display to show the modifier keys
    }
}


void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        static uint32_t last_draw = 0;
        if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
            last_draw = timer_read32();

            render_layer_indicator(false);
            render_os_indicator(false);
            render_mods_area(false);
            // Flush the display to show the updated text
            qp_flush(display);
        }
    }
}

bool process_os_dependant_key(uint16_t mac_keycode, uint16_t win_keycode) {
    switch (os) {
        case OS_MACOS:
        case OS_IOS:
            tap_code16(mac_keycode);
            return false;
        case OS_WINDOWS:
        case OS_LINUX:
        case OS_UNSURE:
        default:
            tap_code16(win_keycode);
            return false;
    }
}

bool send_os_dependent_unicode_string(const char *str) {
    switch (os) {
        case OS_MACOS:
        case OS_IOS:
            tap_code16(LCTL(KC_SPC)); // Enter Unicode input mode
            wait_ms(50); // Wait for a short duration to ensure the key is registered
            send_unicode_string(str);
            tap_code16(LCTL(KC_SPC)); // Exit Unicode input mode
            break;
        case OS_WINDOWS:
        case OS_LINUX:
        case OS_UNSURE:
        default:
            send_unicode_string(str); // Send Unicode string for Windows/Linux/Unsure
            break;
    }
    return false; // Prevent further processing
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (is_keyboard_master() && record->event.pressed) {
        printf("Keycode: %04X\n", keycode); // Print the keycode for debugging
        switch (keycode) {
            case QK_BOOT:
                // Handle bootloader keycode
                qp_power(display, true);
                render_top_half_text("BOOTLOADER", true);
                bootloader_jump();
                return false; // Prevent further processing
            case SW_OS:
                // Handle custom keycode to switch target OS
                // increment the OS variant by 1, wrapping around to OS_UNSURE
                if (os == OS_IOS) {
                    os = OS_UNSURE; // Wrap around to OS_UNSURE
                } else {
                    os = os + 1; // Increment OS variant
                }
                update_os(os); // Update the OS name
                return false;  // Prevent further processing
            case KC_CUT:
                return process_os_dependant_key(LGUI(KC_X), LCTL(KC_X));
            case KC_COPY:
                return process_os_dependant_key(LGUI(KC_C), LCTL(KC_C));
            case KC_PASTE:
                return process_os_dependant_key(LGUI(KC_V), LCTL(KC_V));
            case KC_UNDO:
                if (get_mods() & MOD_MASK_SHIFT) {
                    // if Shift is held, send Cmd+Shift+Z on MacOS or Ctrl+Y on Windows/Linux
                    unregister_mods(MOD_MASK_SHIFT); // Ensure SHIFT is not held
                    return process_os_dependant_key(LGUI(KC_Z), LCTL(KC_Y));
                } else {
                    return process_os_dependant_key(LGUI(KC_Z), LCTL(KC_Z));
                }
            case KC_SELECT:
                return process_os_dependant_key(LGUI(KC_A), LCTL(KC_A));
            case KC_FIND:
                return process_os_dependant_key(LGUI(KC_F), LCTL(KC_F));
            case WK_NEXT:
                tap_code16(LAG(KC_RIGHT));
                return false; // Prevent further processing
            case WK_PREV:
                tap_code16(LAG(KC_LEFT));
                return false; // Prevent further processing
            case WK_ALL:
                return process_os_dependant_key(LCTL(KC_UP), LGUI(KC_TAB));
            case DS_NEXT:
                tap_code16(LCAG(KC_RIGHT));
                return false; // Prevent further processing
            case DS_PREV:
                tap_code16(LCAG(KC_LEFT));
                return false; // Prevent further processing
            case FLIP_TABLE:
                send_os_dependent_unicode_string("(╯°□°)╯︵┻━┻");
                return false; // Prevent further processing
            case SRSLY:
                send_os_dependent_unicode_string("ಠ_ಠ");
                return false; // Prevent further processing
            case SHRUG:
                send_os_dependent_unicode_string("¯\\_(ツ)_/¯");
                return false; // Prevent further processing
            default:
                return true; // Allow other keycodes to be processed normally
        }
    }
    return true; // Process the keycode
}
