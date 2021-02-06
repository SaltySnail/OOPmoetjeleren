#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "stoplicht.h"
#include "lamp.h"
#include "gfx_sim.h"
#include "blit.h"
#include "car.h"

#define DELAY_BETWEEN_STATES 1000
#define AANTAL_STOPLICHTEN 4
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define CAR_ZOOM 1
#define STOPLICHT_ZOOM -10
#define LAMP_ZOOM -2
#define AANTAL_AUTOS 4
#define TXTR_INTERSECTION (char *)"textures/intersection.jpg"
#define TXTR_CAR (char *)"textures/car.png"
#define TXTR_STOPLICHT (char *)"textures/stoplicht.png"
#define TXTR_LIGHT_RED (char *)"textures/red_light.png"
#define TXTR_LIGHT_ORANGE (char *)"textures/orange_light.png"
#define TXTR_LIGHT_GREEN (char *)"textures/green_light.png"


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int main()
{
	int framecounter;
	SDL_Texture *txtr_background;
	blit myBlit;
	car myCars[AANTAL_AUTOS];
	stoplicht Stoplichten[AANTAL_STOPLICHTEN];

	//==============//
	//  SDL Config: //	
	//=============//
	 
	unsigned int window_flags = 0;
	unsigned int renderer_flags = SDL_RENDERER_ACCELERATED;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	window = SDL_CreateWindow("Cars go brr", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
		SCREEN_HEIGHT, window_flags);
	if (window == NULL)
	{
		printf("Failed to create window -- Error: %s\n",
			SDL_GetError());
		exit(1);
	}
	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if (renderer == NULL)
	{
		printf("Failed to create renderer -- Error: %s\n",
			SDL_GetError());
		exit(1);
	}
	IMG_Init(IMG_INIT_PNG);	

	txtr_background = myBlit.load_texture(TXTR_INTERSECTION, renderer);		
	
	myCars[0].texture = myBlit.load_texture(TXTR_CAR, renderer);
	myCars[0].spawn(600, 270, 0, 0.01); //rechts
	myCars[1].texture = myBlit.load_texture(TXTR_CAR, renderer);
	myCars[1].spawn(330, 600, 90, 0.01); //onder
	myCars[2].texture = myBlit.load_texture(TXTR_CAR, renderer);
	myCars[2].spawn(0, 330, -180, 0.01); //links
	myCars[3].texture = myBlit.load_texture(TXTR_CAR, renderer);
	myCars[3].spawn(270, 0, -90, 0.01); //boven

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

			myCars[i].update_coords();
			myBlit.angled(myCars[i].texture, myCars[i].getX(), myCars[i].getY(), myCars[i].getAngle(), CAR_ZOOM, renderer);
			myBlit.angled(Stoplichten[i].getTexture(), Stoplichten[i].getX(), Stoplichten[i].getY(), Stoplichten[i].getAngle(), STOPLICHT_ZOOM, renderer);
			if (Stoplichten[i].getStoplichtState() == "rood")
			{
				myBlit.angled(Stoplichten[i].lampen[0].getTexture(), Stoplichten[i].lampen[0].getX(), Stoplichten[i].lampen[0].getY(), 0, LAMP_ZOOM, renderer);
				if (myCars[i].getAngle() == 90) //identify cars (i=0)
				{
						if (myCars[i].getY() <= 500 && myCars[i].getY() >= 400) //detectielussen
							myCars[i].setVel(0); //stop voor rood
				}
				if (myCars[i].getAngle() == -90)
				{
						if (myCars[i].getY() >= 100 && myCars[i].getY() <= 200)
							myCars[i].setVel(0);
				}
				if (myCars[i].getAngle() == -180)
				{
						if (myCars[i].getX() >= 100 && myCars[i].getX() <= 200)
							myCars[i].setVel(0);	
				}
				if (myCars[i].getAngle() == 0)
				{	
						if (myCars[i].getX() <= 500 && myCars[i].getX() >= 400)
							myCars[i].setVel(0);
				}
			}
		}

		for (int i = 0; i < AANTAL_STOPLICHTEN; i++)
		{
			
			//std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_BETWEEN_STATES));	
			//Stoplichten[i].setStoplichtState("groen"); //Controller
			//std::cout << "Stoplicht " << i << " staat op: " << Stoplichten[i].getStoplichtState() << std::endl; //View
			//std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_BETWEEN_STATES));	
			//Stoplichten[i].setStoplichtState("oranje");
			//std::cout << "Stoplicht " << i << " staat op: " << Stoplichten[i].getStoplichtState() << std::endl;
			//std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_BETWEEN_STATES));
			//Stoplichten[i].setStoplichtState("rood");
			//std::cout << "Stoplicht " << i << " staat op: " << Stoplichten[i].getStoplichtState() << std::endl;
		}

		SDL_RenderPresent(renderer);
	}
}
