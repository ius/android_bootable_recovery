#include <linux/input.h>

#include "recovery_ui.h"
#include "common.h"
#include "extendedcommands.h"

// If a target lacks a suitable select button, use spare keys
// to select menu items. Otherwise use these keys as back buttons
int device_handle_spare_key()
{
#ifdef BOARD_HAS_NO_SELECT_BUTTON
    return SELECT_ITEM;
#else
    if (ui_menu_level > 0) {
        return GO_BACK;
    } else {
        return NO_ACTION;
    }
#endif
}

int device_handle_key(int key_code, int visible) {
    if (visible) {
        switch (key_code) {
            case KEY_CAPSLOCK:
            case KEY_DOWN:
            case KEY_VOLUMEDOWN:
            case KEY_MENU:
                return HIGHLIGHT_DOWN;

            case KEY_LEFTSHIFT:
            case KEY_UP:
            case KEY_VOLUMEUP:
            case KEY_HOME:
                return HIGHLIGHT_UP;

            case KEY_POWER:
                return device_handle_spare_key();

            case KEY_LEFTBRACE:
            case KEY_ENTER:
            case BTN_MOUSE:
            case KEY_CAMERA:
            case KEY_F21:
            case KEY_SEND:
                return SELECT_ITEM;
            
            case KEY_END:
            case KEY_BACKSPACE:
            case KEY_SEARCH:
                return device_handle_spare_key();

            case KEY_BACK:
                if (ui_menu_level > 0) {
                    return GO_BACK;
                }
        }
    }

    return NO_ACTION;
}
