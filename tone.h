#ifndef TONE_H
#define TONE_H

#include "config.h"

//INCEDENTALLY PUBLIC API (IDEALLY PRIVATE)
#define CH_P(N) ch##N##_p
#define CH_HP(N) ch##N##_hp
#define CH_ACT(N) ch##N##_act
#define CH_PH(N) ch##N##_ph
// It is unfortunate that we need these to be external, but we need SET_CHANNEL
// and CLEAR_CHANNEL to work which requires these to be external. The reason
// we can't just use a function and a vector of fields is that looking up the
// field in the ISR would be too expensive and we don't trust the compiler to
// unroll the loop. Alternatively looking up once and storing on the stack is
// still too many useless cycles.
#define _EXTERN_CHANNEL(N) \
    extern volatile float CH_P(N); \
    extern volatile float CH_HP(N); \
    extern volatile char CH_ACT(N)
// chN_ph is kept private as there is no reason for anyone to be screwing with
// the phase of the waveform as it is playing. chN_hp is just an unfortunate
// casualty of not wanting to divide chN_p by 2 every time.

_EXTERN_CHANNEL(1);
_EXTERN_CHANNEL(2);
_EXTERN_CHANNEL(3);
_EXTERN_CHANNEL(4);
_EXTERN_CHANNEL(5);
_EXTERN_CHANNEL(6);
_EXTERN_CHANNEL(7);
_EXTERN_CHANNEL(8);


//EH KINDA PUBLIC API
#define TONE_POST_SCALAR AUDIO_QUALITY
#define TONE_PRE_SCALAR 8
#define TONE_SAMPLE_RATE F_CPU / 255 / TONE_PRE_SCALAR / TONE_POST_SCALAR

#endif

// Definition of p relative to the sample rate
#define HZ(F) (TONE_SAMPLE_RATE/F)


//PUBLIC API
#define SET_CHANNEL(N, F) do {\
    CH_ACT(N) = 1; \
    CH_HP(N) = HZ(F)/2.0f; \
    CH_P(N) = HZ(F); \
    } while(0)

#define CLEAR_CHANNEL(N) CH_ACT(N) = 0

void init_audio();
