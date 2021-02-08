#ifndef INIT
#define INIT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "stoplicht.h"
#include "lamp.h"
#include "gfx_sim.h"
#include "blit.h"
#include "car.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
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

class init
{
	private:
	public:
		void sdl(SDL_Window **window, SDL_Renderer **renderer);
};

#endif
