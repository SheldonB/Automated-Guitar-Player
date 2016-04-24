#include <ioport.h>
#include <util/delay.h>

#include "jets_util.h"
#include "xmega_a3bu_xplained.h"

void solenoid_init()
{
	ioport_init();
	ioport_set_pin_dir(J2_PIN0, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(J2_PIN1, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(J2_PIN2, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(J2_PIN4, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(J2_PIN5, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(J2_PIN6, IOPORT_DIR_OUTPUT);
}

void solenoid_high_low(port_pin_t pin) 
{
	ioport_toggle_pin(pin);
	jets_delay_ms(50);
	ioport_toggle_pin(pin);
}