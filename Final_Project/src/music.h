#ifndef MUSIC_H
#define MUSIC_H

#include <ioport.h>
#include "xmega_a3bu_xplained.h"

#define STRING_SIX J2_PIN0
#define STRING_FIVE J2_PIN1
#define STRING_FOUR J2_PIN2
#define STRING_THREE J2_PIN4
#define STRING_TWO J2_PIN5
#define STRING_ONE J2_PIN6

struct SongNote {
	port_pin_t port;
	unsigned int delay;
};

extern struct SongNote SAMPLE_SONG[];

extern struct SongNote STAIRWAY[];

extern struct SongNote MISERLOU[];

extern unsigned int SAMPLE_SONG_LENGTH;

void play_song(struct SongNote[], unsigned int);
void play_note(struct SongNote);

#endif
