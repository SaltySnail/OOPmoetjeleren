#include "init.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int main()
{
	double accel[AANTAL_AUTOS];
	int framecounter;
	SDL_Texture *txtr_background;
	blit myBlit;
	init init;
	car myCars[AANTAL_AUTOS];
	stoplicht Stoplichten[AANTAL_STOPLICHTEN];
	
       	init.sdl(&window, &renderer);	
	txtr_background = myBlit.load_texture(TXTR_INTERSECTION, renderer);		
	myCars[0].initCars(myCars, renderer);
	Stoplichten[0].initStoplichten(Stoplichten, renderer);
	
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
				myBlit.angled(Stoplichten[i].lampen[0].getTexture(), Stoplichten[i].lampen[0].getX(), Stoplichten[i].lampen[0].getY(), 0, LAMP_ZOOM, renderer); //rode lamp staat aan
				if (myCars[i].getAngle() == 90) //identify cars (i=0)
				{
						if (myCars[i].getY() <= 500 && myCars[i].getY() >= 450) //detectielussen hitbox
						{
							myCars[i].setVel(0); //stop voor rood
							accel[i] = 0;
							Stoplichten[i].detectielus(Stoplichten, i);
						}
				}
				if (myCars[i].getAngle() == -90)
				{
						if (myCars[i].getY() >= 100 && myCars[i].getY() <= 150)
						{
							myCars[i].setVel(0);
							accel[i] = 0;
							Stoplichten[i].detectielus(Stoplichten, i);
						}
				}
				if (myCars[i].getAngle() == -180)
				{
						if (myCars[i].getX() >= 100 && myCars[i].getX() <= 150)
						{
							myCars[i].setVel(0);
							accel[i] = 0;	
							Stoplichten[i].detectielus(Stoplichten, i);
						}
				}
				if (myCars[i].getAngle() == 0)
				{	
						if (myCars[i].getX() <= 500 && myCars[i].getX() >= 450)
						{
							myCars[i].setVel(0);
							accel[i] = 0;
							Stoplichten[i].detectielus(Stoplichten, i);
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
				myBlit.angled(Stoplichten[i].lampen[2].getTexture(), Stoplichten[i].lampen[2].getX(), Stoplichten[i].lampen[2].getY(), 0, LAMP_ZOOM, renderer); //groene lamp staat aan
				if (Stoplichten[i].isTimerNull())
				{
					Stoplichten[i].setStoplichtState("oranje");
					//Stoplichten[i].updateTimer(); //else the isTimerNull function of every trafficlight would trigger. This is now done with setStoplichtState
				}
			}

			if (Stoplichten[i].getStoplichtState() == "oranje")
			{
				myBlit.angled(Stoplichten[i].lampen[1].getTexture(), Stoplichten[i].lampen[1].getX(), Stoplichten[i].lampen[1].getY(), 0, LAMP_ZOOM, renderer); //oranje lamp staat aan
				if (Stoplichten[i].isTimerNull())
				{
					Stoplichten[i].setStoplichtState("rood");
				}
			}
			myCars[i].autoRespawn();
		}

		SDL_RenderPresent(renderer);
	}
}

