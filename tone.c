#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "tone.h"

#define TANH_RESOLUTION 100.0f
// See line 52 if these are changed...
#define CHANNEL_COUNT 8
#define CHANNEL_RESOLUTION 255

/* f(t, p) = |t%p - (p/2)|/(p/2)
 * This produces a triangle waveform as long as t advances.
 * p is the period defined relative to the width of the sample rate.
 * We can make an optimization realizing that the modulo p is unecessary if t
 * is not an integer, instead we can simply subtract p which will preserve the
 * phase-offset of the waveform for the next sample point.
 */
#define WAVE(X, P, HP) fabsf(((++X < P ? X : (X -= P)) - HP) / HP)
// If active compute sample the waveform.
#define SAMPLE(N, D) (CH_ACT(N) ? D += WAVE(CH_PH(N), CH_P(N), CH_HP(N)) : 0)
// Faster than tanh; takes a float, returns a char.
#define NORMALIZE(X) (tanh_lookup[(unsigned int) (X * TANH_RESOLUTION)])



/* Template definition of a channel
 * chN_p: period of the channel relative to the sample rate (HZ(440))
 * chN_hp: half of chN_p to save two floating point ops per sample (HZ(440)/2)
 * chN_ph: the current phase offset of the waveform
 * chN_act: whether the channel is active
 */
#define DECLARE_CHANNEL(N) \
    volatile float CH_P(N) = 0; \
    volatile float CH_HP(N) = 0; \
    volatile float CH_PH(N) = 0; \
    volatile char CH_ACT(N) = 0

DECLARE_CHANNEL(1);
DECLARE_CHANNEL(2);
DECLARE_CHANNEL(3);
DECLARE_CHANNEL(4);
// DECLARE_CHANNEL(5);
// DECLARE_CHANNEL(6);
// DECLARE_CHANNEL(7);
// DECLARE_CHANNEL(8);

volatile char pscalar = 0;

// CHANNEL_COUNT * TANH_RESOLUTION
// Compiler gives a warning if this is actually the above expression
static unsigned char tanh_lookup[400]; //change back to 800

ISR(TIMER2_OVF_vect) {
    if(!pscalar) {

        float data;
        data = 0;
        SAMPLE(1, data);
        SAMPLE(2, data);
        SAMPLE(3, data);
        SAMPLE(4, data);
        // SAMPLE(5, data);
        // SAMPLE(6, data);
        // SAMPLE(7, data);
        // SAMPLE(8, data);

        OCR0A = NORMALIZE(data);
    }
    pscalar = (pscalar + 1) % TONE_POST_SCALAR;

}

void _init_lookup() {
    int i;
    for (i=0; i<sizeof(tanh_lookup); i++) {
        tanh_lookup[i] = (unsigned char) (tanh(i/TANH_RESOLUTION)
                                          * CHANNEL_RESOLUTION);
    }
}

void init_audio() {
    _init_lookup();
    // Set out OC0A:
    DDRB |= 1 << PB3;

    // Sampler Prescaler: 8
    TCCR2B |= (1 << CS21);
    TIMSK2 |= (1 << TOIE2);

    // Output OC0A on compare
    TCCR0A |= (1 << COM0A1) | (1 << WGM00) ;
    TCCR0B |= (1 << CS00);
}
