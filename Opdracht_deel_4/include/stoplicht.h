#ifndef STOPLICHT
#define STOPLICHT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lamp.h"

class stoplicht 
{
	private:
		SDL_Texture *texture;
		int x, y, timer;
		double angle;
	public:
		lamp lampen[3];
		SDL_Texture *getTexture();
		void setTexture(SDL_Texture *stoplicht_texture);
		std::string getStoplichtState();
		void  setStoplichtState(std::string setColor);
		void  initStoplicht();
		void  spawn(int setX, int setY, double setAngle);
		void spawnLamps();
		int getX();
		int getY();
		double getAngle();
		void resetTimer();
		void updateTimer();
};

#endif
