#include <iostream>
#include <string>
#include "lamp.h"

std::string lamp::getColor()
{
	switch(color)
	{
	case Color::red:
		return "rood";
	case Color::orange:
		return "oranje";
	case Color::green:
		return "groen";
	}
	return 0;
}

void lamp::setColor(int i)
{
	color = (Color)i;
}

bool lamp::getState()
{
	return (bool)state;
}

void lamp::setState(State setState)
{
	state = setState;
}

void lamp::setCoords(int setX, int setY)
{
	x = setX;
	y = setY;
}

int lamp::getX()
{
	return x;
}
		
int lamp::getY()
{
	return y;
}

void lamp::setTexture(SDL_Texture *setTexture)
{
	texture = setTexture; 
}

SDL_Texture *lamp::getTexture()
{
	return texture;
}
