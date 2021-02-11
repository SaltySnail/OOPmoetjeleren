#include "blit.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600


void blit::angled(SDL_Texture *txtr, int x, int y, float angle, int zoom, SDL_Renderer *renderer)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(txtr, NULL, NULL, &dest.w, &dest.h);
	if (zoom > 0)
	{
		dest.w *= zoom;
		dest.h *= zoom;
	}
	if (zoom < 0)
	{
		dest.w /= -zoom;
		dest.h /= -zoom;
	}
	dest.x -= dest.w / 2;
	dest.y -= dest.h / 2;
	SDL_RenderCopyEx(renderer, txtr, NULL, &dest, angle, NULL,
		SDL_FLIP_NONE);
}

void blit::background(SDL_Texture *txtr, SDL_Renderer *renderer)
{
		angled(txtr, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0 , 1, renderer);
}

SDL_Texture *blit::load_texture(char *filename, SDL_Renderer *renderer)
{
	SDL_Texture *txtr;
	txtr = IMG_LoadTexture(renderer, filename);
	return txtr;
}
