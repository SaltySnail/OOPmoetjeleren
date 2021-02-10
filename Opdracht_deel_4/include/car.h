#ifndef CAR
#define CAR

#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "blit.h"
#include "init.h"


class car 
{
	private:
		double angle, vel, x, y;

	public:
		SDL_Texture *texture;
		void spawn(int setx, int sety, double setangle, double setvel);
		void update_coords();
		void setX(int setX);
		void setY(int setY);
		int getX();
		int getY();
		double getAngle();
		double getVel();
		void setVel(double setVel);
		void initCars(car *myCars, SDL_Renderer *renderer);
		void autoRespawn();
};

#endif
