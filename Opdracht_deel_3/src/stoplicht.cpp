#include "stoplicht.h"

color stoplicht::getStoplichtState()
{
	for (int i = 0; i < 3; i++)
	{
		if (lamp[i]::getState())
		{
			return lamp[i]::getColor;
		}
	}	
}

void stoplicht::setStoplichtState(color setColor)
{
	for (int i = 0; i < 3; i++)
	{
		lamp[i]::setState(off);
		if (lamp[i]::getColor() == setColor)
		{
			lamp[i]::setState(on);
		}

	}
}
