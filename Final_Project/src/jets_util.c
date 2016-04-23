#include <util/delay.h>
#include "jets_util.h"

void jets_delay_ms(unsigned int delay)
{
	unsigned int i;
	for (i = 0; i < delay/10; i++)
	{
		_delay_ms(10);
	}
}
