#ifndef CONTROLS_H
#define CONTROLS_H

#include <wiiuse/wpad.h>

struct GameControls {
    bool up, down, left, right;
    bool interact, cancel, pause;
};

inline GameControls ReadControls() {
    GameControls c = {};

    WPAD_ScanPads();

    u32 held = WPAD_ButtonsHeld(0);
    u32 pressed = WPAD_ButtonsDown(0);

    // D-pad Wii Remote aj Classic Controller
    c.up = held & (WPAD_BUTTON_UP | WPAD_CLASSIC_BUTTON_UP);
    c.down = held & (WPAD_BUTTON_DOWN | WPAD_CLASSIC_BUTTON_DOWN);
    c.left = held & (WPAD_BUTTON_LEFT | WPAD_CLASSIC_BUTTON_LEFT);
    c.right = held & (WPAD_BUTTON_RIGHT | WPAD_CLASSIC_BUTTON_RIGHT);

    // Tlačidlá
    c.interact = pressed & (WPAD_BUTTON_A | WPAD_CLASSIC_BUTTON_A);
    c.cancel = pressed & (WPAD_BUTTON_B | WPAD_CLASSIC_BUTTON_B);
    c.pause = pressed & (WPAD_BUTTON_PLUS | WPAD_CLASSIC_BUTTON_PLUS);

    // Ľavá analógová páčka Classic Controlleru
    WPADData* data = WPAD_Data(0);

    if (data && data->exp.type == EXP_CLASSIC) {
        float x = data->exp.classic.ljs.pos.x;
        float y = data->exp.classic.ljs.pos.y;

        if (x < -0.5f) c.left = true;
        if (x >  0.5f) c.right = true;
        if (y >  0.5f) c.up = true;
        if (y < -0.5f) c.down = true;
    }

    return c;
}

#endif
