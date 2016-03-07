#include "config.h"
#include <avr/interrupt.h>
#include "tone.h"
#include "snes.h"
#include "sysclock.h"
#include "task.h"
#include "logic.h"


void handle_input() {
    switch (get_input()) {
        case 0:
            clear_p1();
            clear_p2();
            break;

        case PLAYER1:
            clear_p2();
            handle_p1();
            break;

        case PLAYER2:
            clear_p1();
            handle_p2();
            break;

        case PLAYER1 | PLAYER2:
            handle_p1();
            handle_p2();
            break;
    }
}

void init() {
    init_audio();
    init_input();
    sysclock_start();
    sei();
    task_create(handle_input, 10, true);
}
// avr-gcc -Wall -Os -mmcu=atmega644 main.c tone.c snes.c task.c sysclock.c logic.c -o final.hex
// sudo avrdude -c usbtiny -p m644 -B 8 -U lfuse:w:0xA7:m -U final.hex
int main() {
    init();
    while(true) {
        task_update_all();
    }
}
