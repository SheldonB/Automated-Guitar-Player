#include <asf.h>
#include <util/delay.h>

#define STRING_SIX J1_PIN0
#define STRING_FIVE J1_PIN1
#define STRING_FOUR J1_PIN2
#define STRING_THREE J1_PIN3
#define STRING_TWO J1_PIN4
#define STRING_ONE J1_PIN5


int main (void)
{
	sysclk_init();	
	board_init();
	ioport_init();

	ioport_set_pin_dir(J1_PIN0, IOPORT_DIR_OUTPUT);
	ioport_set_pin_low(J1_PIN0);

	ioport_set_pin_dir(J1_PIN1, IOPORT_DIR_OUTPUT);
	ioport_set_pin_low(J1_PIN1);

	ioport_set_pin_dir(J1_PIN2, IOPORT_DIR_OUTPUT);
	ioport_set_pin_low(J1_PIN2);

	ioport_set_pin_dir(J1_PIN3, IOPORT_DIR_OUTPUT);
	ioport_set_pin_low(J1_PIN3);

	ioport_set_pin_dir(J1_PIN4, IOPORT_DIR_OUTPUT);
	ioport_set_pin_low(J1_PIN4);

	while(true) {
		ioport_toggle_pin(J1_PIN0);
		_delay_ms(60);
	}
}
