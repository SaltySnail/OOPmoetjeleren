#ifndef STOPLICHT
#define STOPLICHT

#include "lamp.h"

class stoplicht 
{
	private:
		int id;
	public:
		lamp lampen[3];
		
		color getStoplichtState();
		void  setStoplichtState(color setColor);
}

#endif
