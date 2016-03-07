#ifndef CONFIG_H
#define CONFIG_H

#define F_CPU 28600000

// 1 is best, 10 is nearly unusable
// The higher the number the more channels can be mixed at a time.
// 1 can only handle 1 channel, 5 can handle about 3
#define AUDIO_QUALITY 4

#define true  0x01
#define false 0x00
typedef unsigned char bool;

#endif
