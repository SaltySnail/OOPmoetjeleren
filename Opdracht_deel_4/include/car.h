#ifndef CAR
#define CAR

#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class car 
{
	private:
		double angle, vel, x, y;

	public:
		SDL_Texture *texture;
		void spawn(int setx, int sety, double setangle, double setvel);
		void update_coords();
		int getX();
		int getY();
		double getAngle();
		double getVel();
		void setVel(double setVel);
};

#endif
