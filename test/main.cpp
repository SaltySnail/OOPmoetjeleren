#include <SDL2/SDL.h>
#include <math.h>


#define SCREEN_WIDTH 2000
#define SCREEN_HEIGHT 1000
#define RES 500

class init {
	public:
		const void sdl(SDL_Window **window, SDL_Renderer **renderer);
};
class wave {
	public:
		SDL_Point points[RES];
		int amplitude, time;
		double frequency, phase;
		const void update(void);
};
class input {
	public:
		SDL_Event event;
		SDL_bool update(void);
};
class draw { 
	public: 
		const void lines(SDL_Point *points, int res, SDL_Renderer *renderer);
};
const void wave::update() {
	for (int i = 0; i < RES; i++)
	{
		//time += i;
		time = points[i].x;
		points[i].y = amplitude * sin(frequency * time + phase) + (SCREEN_HEIGHT/2) - amplitude;
	}
}
const void draw::lines(SDL_Point *points, int res, SDL_Renderer *renderer) {	
		for (int i = 1; i < res; i++)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(renderer, points[i-1].x, points[i-1].y, points[i].x, points[i].y);
		}
}
const void init::sdl(SDL_Window **window, SDL_Renderer **renderer) {
	*window = SDL_CreateWindow("Waves", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
}
SDL_bool input::update() {
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
				case SDL_QUIT: 
                        		return SDL_TRUE;
				break;
		    }
                }
		return SDL_FALSE;
}

int main(void) {
	SDL_bool quit = SDL_FALSE;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	wave wave[2];
	init init;
	input input;
	draw draw;
	double x_offset;
	
	wave[0].amplitude = 400;
	wave[0].frequency = 0.05;
	wave[0].phase = 0;

	wave[1].amplitude = 100;
	wave[1].frequency = 0.01;
	wave[1].phase = 1;

	

	for (int i = 0; i < RES; i++) {
		x_offset = SCREEN_WIDTH/(RES-1);
		wave[0].points[i].x = (int)(x_offset*i);
		wave[0].points[i].y = SCREEN_HEIGHT/2;
		wave[1].points[i].x = (int)(x_offset*i);
		wave[1].points[i].y = SCREEN_HEIGHT/2;
	}
	//wave.points[RES-1].x = SCREEN_WIDTH; //1920 / 100 * 100 = 1900 in int land
	init.sdl(&window, &renderer);
	
	while(!quit) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		quit = input.update();
		wave[0].update();
		wave[1].update();
		for (int i = 0; i < RES; i++) {
			wave[1].points[i].y += wave[0].points[i].y;
		}
		wave[0].phase += 0.0005;
		wave[1].phase += 0.0005;
		draw.lines(wave[1].points, RES, renderer);
		SDL_RenderPresent(renderer);
	}
	if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    	SDL_Quit();
	return 0;
}
