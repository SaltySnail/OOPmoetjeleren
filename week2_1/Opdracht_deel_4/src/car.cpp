#include "car.h"

#define PI 3.14159265358979323846

void car::spawn(int setx, int sety, double setangle, double setvel)
{
	x = setx;
        y = sety;
        angle = setangle;
	vel = setvel;	
}

void car::update_coords()
{
	x += vel * -cos(angle*PI/180);
	//std::cout << x << std::endl;
	y += vel * -sin(angle*PI/180);
	//std::cout << y << std::endl;
}

int car::getX()
{
	return x;
}

int car::getY()
{
	return y;
}

double car::getAngle()
{
	return angle;
}

double car::getVel()
{
	return vel;
}

void car::setVel(double setVel)
{
	vel = setVel;
}

void car::setX(int setX)
{
	x = setX;
}

void car::setY(int setY)
{
	y = setY;
}	

void car::initCars(car *myCars, SDL_Renderer *renderer)
{
	blit myBlit;
	myCars[0].texture = myBlit.load_texture(TXTR_CAR, renderer);
	myCars[0].spawn(600, 270, 0, 0.1); //rechts
	myCars[1].texture = myBlit.load_texture(TXTR_CAR, renderer);
	myCars[1].spawn(330, 600, 90, 0.1); //onder
	myCars[2].texture = myBlit.load_texture(TXTR_CAR, renderer);
	myCars[2].spawn(0, 330, -180, 0.1); //links
	myCars[3].texture = myBlit.load_texture(TXTR_CAR, renderer);
	myCars[3].spawn(270, 0, -90, 0.1); //boven
}

void car::autoRespawn()
{
	if (getX() >= 650)
		setX(-49);
	if (getX() <= -50)
		setX(649);
	if (getY() >= 650)
		setY(-49);
	if (getY() <= -50)
		setY(649);
}
