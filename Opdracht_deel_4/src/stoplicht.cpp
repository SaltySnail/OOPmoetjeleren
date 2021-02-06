#include <iostream>
#include "stoplicht.h"

std::string stoplicht::getStoplichtState()
{
	for (int i = 0; i < 3; i++)
	{
		if (lampen[i].getState())
		{
			return lampen[i].getColor();
		}
	}
	return "Lights off";	
}

void stoplicht::setStoplichtState(std::string setColor)
{
	for (int i = 0; i < 3; i++)
	{
		lampen[i].setState(State::off);
		//std::cout << lampen[i].getColor() << std::endl;
		if (lampen[i].getColor() == setColor)
		{
			lampen[i].setState(State::on);
		}
	}
}

void stoplicht::setTexture(SDL_Texture *stoplicht_texture)
{
	texture = stoplicht_texture;
}

SDL_Texture *stoplicht::getTexture()
{
	return texture;
}

void stoplicht::spawn(int setX, int setY, double setAngle)
{
	x = setX;
	y = setY;
	angle = setAngle;
}

int stoplicht::getX()
{
	return x;
}

int stoplicht::getY()
{
	return y;
}

double stoplicht::getAngle()
{
	return angle;
}

void stoplicht::spawnLamps()
{
	if (angle == -90) //i in main == 0 //rechts
	{
		for (int i = 0; i < 3; i++)
		{
			lampen[i].setCoords(x+22*i-22, y);
		}	
	}

	if (angle == 0) //onder
	{
		for (int i = 0; i < 3; i++)
		{	
			lampen[i].setCoords(x, y+22*i-22);
		}
	}

	if (angle == 90) //links
	{
		for (int i = 0; i < 3; i++)
		{
			lampen[i].setCoords(x-22*i+22, y);
		}
	}

	if (angle == 180) //boven
	{
		for (int i = 0; i < 3; i++)
		{
			lampen[i].setCoords(x, y-22*i+22);
		}	
	}
	
}

void stoplicht::initStoplicht()
{
	for (int i = 0; i < 3; i++)
	{
		lampen[i].setColor(i);
		lampen[i].setState(State::off);
	}
	spawnLamps();
}

void stoplicht::resetTimer()
{
	timer = 0;
}

void stoplicht::updateTimer()
{
	if (timer<5000)
		timer++;
	else 
		timer = 0;
}

bool stoplicht::isTimerNull()
{
	if (timer)
		return false;
	else
	        return true;	
}	
