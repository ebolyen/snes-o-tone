#include "config.h"
#include "snes.h"
#include "tone.h"
#include "keymap.h"
#include "logic.h"

short p1_key = 3;

short p2_key = 3;

const float notes[108] = {
    16.35f, 17.32f, 18.35f, 19.45f, 20.6f, 21.83f, 23.12f, 24.5f, 25.96f,
    27.5f, 29.14f, 30.87f, //C0 -> B0

    32.7f, 34.65f, 36.71f, 38.89f, 41.2f, 43.65f, 46.25f, 49.0f, 51.91f,
    55.0f, 58.27f, 61.74f, //C1 -> B1

    65.41f, 69.3f, 73.42f, 77.78f, 82.41f, 87.31f, 92.5f, 98.0f, 103.83f,
    110.0f, 116.54f, 123.47f, //C2 -> B2

    130.81f, 138.59f, 146.83f, 155.56f, 164.81f, 174.61f, 185.0f, 196.0f,
    207.65f, 220.0f, 233.08f, 246.94f, //C3 -> B3

    261.63f, 277.18f, 293.66f, 311.13f, 329.63f, 349.23f, 369.99f, 392.0f,
    415.3f, 440.0f, 466.16f, 493.88f, //C4 -> B4

    523.25f, 554.37f, 587.33f, 622.25f, 659.25f, 698.46f, 739.99f, 783.99f,
    830.61f, 880.0f, 932.33f, 987.77f, //C5 -> B5

    1046.5f, 1108.73f, 1174.66f, 1244.51f, 1318.51f, 1396.91f, 1479.98f,
    1567.98f, 1661.22f, 1760.0f, 1864.66f, 1975.53f, //C6 -> B6

    2093.0f, 2217.46f, 2349.32f, 2489.02f, 2637.02f, 2793.83f, 2959.96f,
    3135.96f, 3322.44f, 3520.0f, 3729.31f, 3951.07f, //C7 -> B7

    4186.01f, 4434.92f, 4698.63f, 4978.03f, 5274.04f, 5587.65f, 5919.91f,
    6271.93f, 6644.88f, 7040.0f, 7458.62f, 7902.13f //C8 -> B8
};

// This code is horrible because it was written about 20 minutes before class
void handle_p1() {
    if (player1 & DPAD_U) {
        p1_key = 4;
    } else if (player1 & DPAD_D) {
        p1_key = 2;
    } else {
        p1_key = 3;
    }

    if(player1 & BUTTON_Y) {
        if (player1 & BUTTON_R) {
            SET_CHANNEL(1, notes[p1_key * 12 + 7]);
        } else if (player1 & BUTTON_L) {
            SET_CHANNEL(1, notes[p1_key * 12 + 5]);
        } else {
            SET_CHANNEL(1, notes[p1_key * 12]);
        }
    }

    if(player1 & BUTTON_B) {
        if (player1 & BUTTON_R) {
            SET_CHANNEL(2, notes[p1_key * 12 + 11]);
        } else if (player1 & BUTTON_L) {
            SET_CHANNEL(2, notes[p1_key * 12 + 9]);
        } else {
            SET_CHANNEL(2, notes[p1_key * 12 + 4]);
        }
    }

    if(player1 & BUTTON_X) {
        if (player1 & BUTTON_R) {
            SET_CHANNEL(3, notes[p1_key * 12 + 14]);
        } else if (player1 & BUTTON_L) {
            SET_CHANNEL(3, notes[p1_key * 12 + 12]);
        } else {
            SET_CHANNEL(3, notes[p1_key * 12 + 7]);
        }
    }

    if(player1 & BUTTON_A) {
        if (player1 & BUTTON_R) {
            SET_CHANNEL(4, notes[p1_key * 12 + 18]);
        } else if (player1 & BUTTON_L) {
            SET_CHANNEL(4, notes[p1_key * 12 + 16]);
        } else {
            SET_CHANNEL(4, notes[p1_key * 12 + 11]);
        }
    }
}
// Duplication everywhere!
void handle_p2() {
    if (player2 & DPAD_U) {
        p2_key = 4;
    } else if (player2 & DPAD_D) {
        p2_key = 2;
    } else {
        p2_key = 3;
    }
    if(player2 & BUTTON_Y) {
        if (player2 & BUTTON_R) {
            SET_CHANNEL(5, notes[p2_key * 12 + 7]);
        } else if (player2 & BUTTON_L) {
                SET_CHANNEL(5, notes[p2_key * 12 + 5]);
        }else {
            SET_CHANNEL(5, notes[p2_key * 12]);
        }
    }

    if(player2 & BUTTON_B) {
        if (player2 & BUTTON_R) {
            SET_CHANNEL(6, notes[p2_key * 12 + 11]);
        } else if (player2 & BUTTON_L) {
            SET_CHANNEL(6, notes[p2_key * 12 + 9]);
        } else {
            SET_CHANNEL(6, notes[p2_key * 12 + 4]);
        }
    }

    if(player2 & BUTTON_X) {
        if (player2 & BUTTON_R) {
            SET_CHANNEL(7, notes[p2_key * 12 + 14]);
        } else if (player2 & BUTTON_L) {
            SET_CHANNEL(7, notes[p2_key * 12 + 12]);
        } else {
            SET_CHANNEL(7, notes[p2_key * 12 + 7]);
        }
    }

    if(player2 & BUTTON_A) {
        if (player2 & BUTTON_R) {
            SET_CHANNEL(8, notes[p2_key * 12 + 18]);
        } else if (player2 & BUTTON_L) {
            SET_CHANNEL(8, notes[p2_key * 12 + 16]);
        } else {
            SET_CHANNEL(8, notes[p2_key * 12 + 11]);
        }
    }
}

void clear_p1() {
    CLEAR_CHANNEL(1);
    CLEAR_CHANNEL(2);
    CLEAR_CHANNEL(3);
    CLEAR_CHANNEL(4);
}

void clear_p2() {
    CLEAR_CHANNEL(5);
    CLEAR_CHANNEL(6);
    CLEAR_CHANNEL(7);
    CLEAR_CHANNEL(8);
}
