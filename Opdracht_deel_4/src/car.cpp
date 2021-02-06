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
