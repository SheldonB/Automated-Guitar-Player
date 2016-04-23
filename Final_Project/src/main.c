#include <asf.h>
#include <stdio.h>
#include <util/delay.h>

#include "keyboard.h"
#include "solenoid.h"
#include "music.h"

PROGMEM_DECLARE(char const, main_menu_title[]) = "Select a Song";
PROGMEM_DECLARE(char const, option_one[]) = "Simple Beat";
PROGMEM_DECLARE(char const, option_two[]) = "Stairway to Heaven";
PROGMEM_DECLARE(char const, option_three[]) = "Play Your Own";

PROGMEM_STRING_T main_menu_strings[] = {
	option_one,
	option_two,
	option_three
};

struct gfx_mono_menu main_menu = {
	main_menu_title,
	main_menu_strings,
	3,
	0
};

void song_menu(uint8_t, uint8_t);

void song_menu(uint8_t song_choice, uint8_t tempo)
{
	char tempo_str[50];
	
	gfx_mono_draw_filled_rect(0, 0, 128, 32, GFX_PIXEL_CLR);
	gfx_mono_draw_string("Currently Playing: ", 1, 2, &sysfont);
	gfx_mono_draw_progmem_string((char PROGMEM_PTR_T)main_menu_strings[song_choice], 1, 10, &sysfont);
	snprintf(tempo_str, 50, "Tempo: %d", tempo);
	gfx_mono_draw_string(tempo_str, 1, 20, &sysfont);
}

static void simple_beat() {
	struct keyboard_event key;
	uint8_t tempo = 100;

	struct SongNote noteOne = {
		STRING_SIX,
		10
	};

	struct SongNote noteTwo = {
		STRING_FIVE,
		10
	};
	
	song_menu(0, tempo);
	while(true) {
		keyboard_get_key_state(&key);

		if((key.keycode == KEYBOARD_ENTER)
			&& (key.type == KEYBOARD_RELEASE))
		{
			break;
		}
		else if((key.keycode == KEYBOARD_UP)
			&& (key.type == KEYBOARD_RELEASE))
		{
			tempo += 50;
			song_menu(0, tempo);
		}
		else if((key.keycode == KEYBOARD_DOWN)
			&& (key.type == KEYBOARD_RELEASE))
		{
			tempo -= 50;
			song_menu(0, tempo);
		}
		play_note(noteOne);
		_delay_ms(1000);
		play_note(noteTwo);
	}
}

int main (void)
{
	uint8_t menu_status;
	struct keyboard_event input;

	sysclk_init();	
	board_init();
	solenoid_init();
	gfx_mono_init();
	
	gpio_toggle_pin(NHD_C12832A1Z_BACKLIGHT);

	while(true) 
	{
		gfx_mono_menu_init(&main_menu);

		do {
			do {
				keyboard_get_key_state(&input);
			} while (input.type != KEYBOARD_RELEASE);

			menu_status = gfx_mono_menu_process_key(&main_menu, input.keycode);
		} while (menu_status == GFX_MONO_MENU_EVENT_IDLE);

		switch(menu_status) {
			case 0:
			simple_beat();
			break;
		}
	}
}

