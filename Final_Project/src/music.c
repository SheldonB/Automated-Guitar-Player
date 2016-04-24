#include <util/delay.h>

#include "jets_util.h"
#include "music.h"
#include "solenoid.h"

struct SongNote SAMPLE_SONG[] = {
	{STRING_SIX, 300},
	{STRING_FIVE, 300},
	{STRING_FOUR, 300},
	{STRING_THREE, 300},
	{STRING_TWO, 300},
	{STRING_ONE, 300}
};

struct SongNote STAIRWAY[] = {
	{STRING_FOUR, 10},
	{STRING_ONE, 800},
	{STRING_TWO, 800},
	{STRING_THREE, 800},
	{STRING_FOUR, 10},
	{STRING_ONE, 800}
};

struct SongNote MISERLOU[] = {
	{STRING_ONE, 100}
};

unsigned int SAMPLE_SONG_LENGTH = 6;


void play_song(struct SongNote song[], unsigned int length)
{
	unsigned int i;
	for (i = 0; i < length; i++)
	{
		play_note(song[i]);
	}	
}

void play_note(struct SongNote note)
{
	solenoid_high_low(note.port);
	jets_delay_ms(note.delay);
}