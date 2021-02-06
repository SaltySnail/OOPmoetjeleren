#ifndef BLIT
#define BLIT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class blit
{
	public:
		SDL_Texture *load_texture(char *filename, SDL_Renderer *renderer);
		void background(SDL_Texture *txtr, SDL_Renderer *renderer);
		void angled(SDL_Texture *txtr, int x, int y, float angle, int zoom, SDL_Renderer *renderer);
};

#endif
