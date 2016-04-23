#include <util/delay.h>

#include "jets_util.h"
#include "music.h"
#include "solenoid.h"

void play_note(struct SongNote note)
{
	solenoid_high_low(note.port);
	jets_delay_ms(note.delay);
}

void play_chord(struct Chord chord)
{
	unsigned int i;
	for(i = 0; i < chord.numNotes; i++)
	{
		play_note(chord.notes[i]);
		jets_delay_ms(100);
	}
}
