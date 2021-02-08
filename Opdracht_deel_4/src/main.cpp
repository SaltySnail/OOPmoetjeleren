#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "init.h"

SDL_Window *window;
SDL_Renderer *renderer;

int main()
{
	double accel[AANTAL_AUTOS];
	int framecounter;
	SDL_Texture *txtr_background;
	blit myBlit;
	init init;
	car myCars[AANTAL_AUTOS];
	stoplicht Stoplichten[AANTAL_STOPLICHTEN];

	//==============//
	//  SDL Config: //	
	//=============//
	 

	txtr_background = myBlit.load_texture(TXTR_INTERSECTION, renderer);		
	
	myCars[0].texture = myBlit.load_texture(TXTR_CAR, renderer);
	myCars[0].spawn(600, 270, 0, 0.1); //rechts
	myCars[1].texture = myBlit.load_texture(TXTR_CAR, renderer);
	myCars[1].spawn(330, 600, 90, 0.1); //onder
	myCars[2].texture = myBlit.load_texture(TXTR_CAR, renderer);
	myCars[2].spawn(0, 330, -180, 0.1); //links
	myCars[3].texture = myBlit.load_texture(TXTR_CAR, renderer);
	myCars[3].spawn(270, 0, -90, 0.1); //boven

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

	while (1)
	{
		SDL_RenderClear(renderer);
		myBlit.background(txtr_background, renderer);
		
		for (int i = 0; i < AANTAL_AUTOS; i++)
		{
			Stoplichten[i].updateTimer();
			myCars[i].update_coords();
			myBlit.angled(myCars[i].texture, myCars[i].getX(), myCars[i].getY(), myCars[i].getAngle(), CAR_ZOOM, renderer);
			myBlit.angled(Stoplichten[i].getTexture(), Stoplichten[i].getX(), Stoplichten[i].getY(), Stoplichten[i].getAngle(), STOPLICHT_ZOOM, renderer);
								
			if (Stoplichten[i].getStoplichtState() == "rood")
			{
				myBlit.angled(Stoplichten[i].lampen[0].getTexture(), Stoplichten[i].lampen[0].getX(), Stoplichten[i].lampen[0].getY(), 0, LAMP_ZOOM, renderer);
				if (myCars[i].getAngle() == 90) //identify cars (i=0)
				{
						if (myCars[i].getY() <= 500 && myCars[i].getY() >= 450) //detectielussen
						{
							myCars[i].setVel(0); //stop voor rood
							accel[i] = 0;
							if (Stoplichten[0].getStoplichtState() == "rood" &&
					          	    Stoplichten[1].getStoplichtState() == "rood" &&
						  	    Stoplichten[2].getStoplichtState() == "rood" &&
						   	    Stoplichten[3].getStoplichtState() == "rood")
							{

								Stoplichten[i].setStoplichtState("groen");
								Stoplichten[i].resetTimer();
								Stoplichten[i].updateTimer();
							}
						}
				}
				if (myCars[i].getAngle() == -90)
				{
						if (myCars[i].getY() >= 100 && myCars[i].getY() <= 150)
						{
							myCars[i].setVel(0);
							accel[i] = 0;
							if (Stoplichten[0].getStoplichtState() == "rood" &&
					          	    Stoplichten[1].getStoplichtState() == "rood" &&
						  	    Stoplichten[2].getStoplichtState() == "rood" &&
						   	    Stoplichten[3].getStoplichtState() == "rood")
							{

								Stoplichten[i].setStoplichtState("groen");
								Stoplichten[i].resetTimer();
								Stoplichten[i].updateTimer();
							}
						}
				}
				if (myCars[i].getAngle() == -180)
				{
						if (myCars[i].getX() >= 100 && myCars[i].getX() <= 150)
						{
							myCars[i].setVel(0);
							accel[i] = 0;	
							if (Stoplichten[0].getStoplichtState() == "rood" &&
					          	    Stoplichten[1].getStoplichtState() == "rood" &&
						  	    Stoplichten[2].getStoplichtState() == "rood" &&
						   	    Stoplichten[3].getStoplichtState() == "rood")
							{

								Stoplichten[i].setStoplichtState("groen");
								Stoplichten[i].resetTimer();
								Stoplichten[i].updateTimer();
							}
						}
				}
				if (myCars[i].getAngle() == 0)
				{	
						if (myCars[i].getX() <= 500 && myCars[i].getX() >= 450)
						{
							myCars[i].setVel(0);
							accel[i] = 0;
							if (Stoplichten[0].getStoplichtState() == "rood" &&
					          	    Stoplichten[1].getStoplichtState() == "rood" &&
						  	    Stoplichten[2].getStoplichtState() == "rood" &&
						   	    Stoplichten[3].getStoplichtState() == "rood")
							{

								Stoplichten[i].setStoplichtState("groen");
								Stoplichten[i].resetTimer();
								Stoplichten[i].updateTimer();
							}
						}
				}
			}

			if (Stoplichten[i].getStoplichtState() == "groen")
			{
				if (accel[i] <= 0.1)
				{
					accel[i] += 0.01;
					myCars[i].setVel(accel[i]);
				}
				myBlit.angled(Stoplichten[i].lampen[2].getTexture(), Stoplichten[i].lampen[2].getX(), Stoplichten[i].lampen[2].getY(), 0, LAMP_ZOOM, renderer);
				if (Stoplichten[i].isTimerNull())
				{
					Stoplichten[i].setStoplichtState("oranje");
					Stoplichten[i].updateTimer();
					
				}
			}

			if (Stoplichten[i].getStoplichtState() == "oranje")
			{
				myBlit.angled(Stoplichten[i].lampen[1].getTexture(), Stoplichten[i].lampen[1].getX(), Stoplichten[i].lampen[1].getY(), 0, LAMP_ZOOM, renderer);
				if (Stoplichten[i].isTimerNull())
				{
					Stoplichten[i].setStoplichtState("rood");
					Stoplichten[i].updateTimer();
				}
			}
			//keep cars in screen:
			if (myCars[i].getX() >= 650)
				myCars[i].setX(-49);
			if (myCars[i].getX() <= -50)
				myCars[i].setX(649);
			if (myCars[i].getY() >= 650)
				myCars[i].setY(-49);
			if (myCars[i].getY() <= -50)
				myCars[i].setY(649);
		}

		SDL_RenderPresent(renderer);
	}
}

