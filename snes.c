#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include "snes.h"

#define TOGGLE(REG) PLAYER_PORT |= (1 << REG); PLAYER_PORT &= ~(1 << REG)

volatile unsigned short player1 = 0;
volatile unsigned short player2 = 0;

void init_input() {
    DDRA |= (1 << PLAYER1_STROBE) | (1 << PLAYER1_CLOCK);
    DDRA |= (1 << PLAYER2_STROBE) | (1 << PLAYER2_CLOCK);
}

unsigned char get_input() {
    unsigned char i, ret;
    player1 = 0;
    player2 = 0;

    TOGGLE(PLAYER1_STROBE);
    for(i=0; i<16; i++){
        player1 |= (PLAYER_IN & (1 << PLAYER1_DATA)) ? 0 : (1 << i);
        TOGGLE(PLAYER1_CLOCK);
    }
    TOGGLE(PLAYER2_STROBE);
    for(i=0; i<16; i++){
        player2 |= (PLAYER_IN & (1 << PLAYER2_DATA)) ? 0 : (1 << i);
        TOGGLE(PLAYER2_CLOCK);
    }

    if (player1 == 0xFFFF)
        player1 = 0;
    if (player2 == 0xFFFF)
        player2 = 0;

    ret = 0;
    if (player1)
        ret |= PLAYER1;
    if (player2)
        ret |= PLAYER2;
    return ret;
}
