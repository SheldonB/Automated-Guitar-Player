#include <util/delay.h>
#include "jets_util.h"

/*
Wrapper around the delay method. This method
will allow for dynamic creation of delay. The _delay_ms
function expects a compile time constant, while this method 
can accept a delay at runtime and then delay for that time dynamically. 
*/
void jets_delay_ms(unsigned int delay)
{
	unsigned int i;
	for (i = 0; i < delay/10; i++)
	{
		_delay_ms(10);
	}
}
