#include <asf.h>
#include <stdio.h>
#include <util/delay.h>

#include "keyboard.h"
#include "solenoid.h"
#include "music.h"
#include "jets_util.h"

#define USART_SERIAL &USARTC0

PROGMEM_DECLARE(char const, main_menu_title[]) = "Select a Song";
PROGMEM_DECLARE(char const, option_one[]) = "Arpeggio";
PROGMEM_DECLARE(char const, option_two[]) = "Stairway to Heaven";
PROGMEM_DECLARE(char const, option_three[]) = "Miserlou";
PROGMEM_DECLARE(char const, option_four[]) = "Play Your Own";

PROGMEM_STRING_T main_menu_strings[] = {
	option_one,
	option_two,
	option_three,
	option_four
};

struct gfx_mono_menu main_menu = {
	main_menu_title,
	main_menu_strings,
	4,
	0
};

void song_menu(uint8_t);
static void play_sample_song(void);
static void play_serial(void);


void song_menu(uint8_t song_choice)
{	
	gfx_mono_draw_filled_rect(0, 0, 128, 32, GFX_PIXEL_CLR);
	gfx_mono_draw_string("Currently Playing: ", 1, 2, &sysfont);
	gfx_mono_draw_progmem_string((char PROGMEM_PTR_T)main_menu_strings[song_choice], 1, 10, &sysfont);

}

static void play_song_with_input(struct SongNote song[], uint8_t song_length) {
	struct keyboard_event key;
	
	while(true) {
		keyboard_get_key_state(&key);

		if((key.keycode == KEYBOARD_ENTER)
			&& (key.type == KEYBOARD_RELEASE))
		{
			break;
		}

		play_song(song, song_length);
	}
}

static void play_serial()
{
	uint8_t recieved_byte;
	bool canContinue = true;

	while(canContinue) {
		recieved_byte = usart_getchar(USART_SERIAL);
		usart_putchar(USART_SERIAL, recieved_byte);
		switch(recieved_byte) {
			case '6':
				solenoid_high_low(STRING_SIX);
				break;
			case '5':
				solenoid_high_low(STRING_FIVE);
				break;
			case '4':
				solenoid_high_low(STRING_FOUR);
				break;
			case '3':
				solenoid_high_low(STRING_THREE);
				break;
			case '2':
				solenoid_high_low(STRING_TWO);
				break;
			case '1':
				solenoid_high_low(STRING_ONE);
				break;
			case '0':
				canContinue = false;
				break;	
		}
	}
}

int main (void)
{
	uint8_t menu_status;
	struct keyboard_event input;

	static usart_rs232_options_t SERIAL_OPTIONS = {
		.baudrate = 57600,
		.charlength = USART_CHSIZE_8BIT_gc,
		.paritytype = USART_PMODE_DISABLED_gc,
		.stopbits = false
	};

	sysclk_init();	
	board_init();
	solenoid_init();
	gfx_mono_init();
	usart_init_rs232(USART_SERIAL, &SERIAL_OPTIONS);

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
				song_menu(0);
				play_song_with_input(SAMPLE_SONG, SAMPLE_SONG_LENGTH);
				break;
			case 1:
				song_menu(1);
				play_song_with_input(STAIRWAY, 6);
				break;
			case 2:
				song_menu(2);
				play_song_with_input(MISERLOU, 1);
				break;
			case 3:
				song_menu(3);
				play_serial();
				break;
		}
	}
}

