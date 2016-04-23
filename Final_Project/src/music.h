#ifndef MUSIC_H
#define MUSIC_H

#include <ioport.h>
#include "xmega_a3bu_xplained.h"

#define STRING_SIX J1_PIN0
#define STRING_FIVE J1_PIN1
#define STRING_FOUR J1_PIN2
#define STRING_THREE J1_PIN3
#define STRING_TWO J1_PIN4
#define STRING_ONE J1_PIN5

struct SongNote {
	port_pin_t port;
	unsigned int delay;
};

struct Chord {
	struct SongNote notes[6];
	unsigned int numNotes;
};

void play_note(struct SongNote);
void play_chord(struct Chord);

#endif
