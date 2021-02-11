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

void stoplicht::updateTimer()
{
	if (timer<2500)
		timer++;
	else 
		timer = 0;
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
	updateTimer();
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

void stoplicht::resetTimer()
{
	timer = 0;
}


bool stoplicht::isTimerNull()
{
	if (timer)
		return false;
	else
	        return true;	
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

void stoplicht::detectielus(stoplicht *Stoplichten, int i)
{
	for (int j = 0; j < AANTAL_STOPLICHTEN; j++)
	{
		if (Stoplichten[j].getStoplichtState() == "rood")
		{
			if (j == AANTAL_STOPLICHTEN-1)
			{
				//Stoplichten[i].
					setStoplichtState("groen");
				//Stoplichten[i].
					resetTimer();
				//Stoplichten[i].
					updateTimer();
			}
		}
		else
		{	
			break;
		}
	}
}

void stoplicht::initStoplichten(stoplicht *Stoplichten, SDL_Renderer *renderer)
{
	blit myBlit;

	Stoplichten[0].spawn(420, 200, -90); //rechts
	Stoplichten[1].spawn(400, 420, 0); //onder
	Stoplichten[2].spawn(180, 400, 90); //links
	Stoplichten[3].spawn(200, 180, 180); //boven


	for (int i = 0; i < AANTAL_STOPLICHTEN; i++)
	{
		Stoplichten[i].lampen[0].setTexture(myBlit.load_texture(TXTR_LIGHT_RED, renderer));
		Stoplichten[i].lampen[1].setTexture(myBlit.load_texture(TXTR_LIGHT_ORANGE, renderer));
		Stoplichten[i].lampen[2].setTexture(myBlit.load_texture(TXTR_LIGHT_GREEN, renderer));
		Stoplichten[i].initStoplicht();
		Stoplichten[i].setTexture(myBlit.load_texture(TXTR_STOPLICHT, renderer));
		Stoplichten[i].setStoplichtState("rood");
	}
}	
