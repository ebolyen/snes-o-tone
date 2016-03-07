#ifndef SNES_H
#define SNES_H

#define PLAYER1 0x01
#define PLAYER2 0x02

#define PLAYER_IN PINA
#define PLAYER_PORT PORTA

#define PLAYER1_DATA   0
#define PLAYER1_STROBE 1
#define PLAYER1_CLOCK  2

#define PLAYER2_DATA   3
#define PLAYER2_STROBE 4
#define PLAYER2_CLOCK  5

#define BUTTON_R      0x0800
#define BUTTON_L      0x0600
#define BUTTON_X      0x0200
#define BUTTON_A      0x0100

#define DPAD_R        0x0080
#define DPAD_L        0x0040
#define DPAD_D        0x0020
#define DPAD_U        0x0010

#define BUTTON_START  0x0008
#define BUTTON_SELECT 0x0004
#define BUTTON_Y      0x0002
#define BUTTON_B      0x0001

extern volatile unsigned short player1;
extern volatile unsigned short player2;

unsigned char get_input();
void init_input();

#endif
