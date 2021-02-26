#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define RES 2560

enum scroll {
	scroll_down = 0,
	scroll_up = 1,
	neutral = 2
};

enum updown {
	up = 0,
	down = 1
};

class init {
	public:
		const void sdl(SDL_Window **window, SDL_Renderer **renderer);
};

class wave {
	public:
		SDL_Point points[RES];
		int time;
		double frequency, phase, amplitude;
		const void update(void);
};

class input {
		SDL_Event event;
	public:
		scroll scroll_wheel;
		updown up_key;
		updown down_key;
		updown left_key;
		updown right_key;		
		//updown getKeystate(const char *key);
		SDL_bool update(void);
};

class draw { 
	public: 
		const void lines(SDL_Point *points, int res, SDL_Renderer *renderer);
};

const void wave::update() {
	for (int i = 0; i < RES; i++)
	{
		time = points[i].x;
		points[i].y = SCREEN_HEIGHT/2 + amplitude * sin(frequency * time + phase);
	}
}

const void draw::lines(SDL_Point *points, int res, SDL_Renderer *renderer) {	
	double red, green, blue;	
		for (int i = 1; i < res; i++)
		{
			red = (double)points[i].x/SCREEN_WIDTH*255;
			green = (double)points[i].y/SCREEN_HEIGHT*255;
			blue = (double)255/res*i;
			SDL_SetRenderDrawColor(renderer, (int)red, (int)green, 255-(int)blue, SDL_ALPHA_OPAQUE);
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
				case SDL_MOUSEWHEEL:
					if (event.wheel.y < 0)
						scroll_wheel = scroll_down;
					if (event.wheel.y > 0)
						scroll_wheel = scroll_up;
				case SDL_KEYUP:
				        if (event.key.keysym.sym == SDLK_RIGHT)
						right_key = up;
					if (event.key.keysym.sym == SDLK_LEFT)
						left_key = up;	
				        if (event.key.keysym.sym == SDLK_UP) 
						up_key = up;
					if (event.key.keysym.sym == SDLK_DOWN)
						down_key = up;	
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
						return SDL_TRUE;
				        if (event.key.keysym.sym == SDLK_RIGHT)
						right_key = down;
					if (event.key.keysym.sym == SDLK_LEFT)
						left_key = down;	
				        if (event.key.keysym.sym == SDLK_UP)
						up_key = down;
					if (event.key.keysym.sym == SDLK_DOWN)
						down_key = down;	
				break;
		    }
                }
		return SDL_FALSE;
}

/*updown input::getKeystate(const char *key) {
	if (key == "right")
	
}*/

int main(void) {
	SDL_bool quit = SDL_FALSE;
	SDL_Window *window;
	SDL_Renderer *renderer;
	init init;
	input input;
	draw draw;
	double x_offset, time_unit = 0.0002;
       	double zoom = 1;
	int waves_amount;

	printf("Hoeveel golfen wil je optellen?\n");
	scanf("%d", &waves_amount);
	wave wave[waves_amount];

	for (int i = 0; i < waves_amount; i++) {
		printf("Wat is golf %d zijn amplitude?\n", i+1);
		scanf("%lf", &wave[i].amplitude);	
		printf("Wat is golf %d zijn frequentie?\n", i+1);	
		scanf("%lf", &wave[i].frequency);
		wave[i].frequency /= 1000;
		printf("Wat is golf %d zijn fase?\n", i+1);	
		scanf("%lf", &wave[i].phase);
		
	}
	
	for (int j = 0; j < waves_amount; j++) {
		for (int i = 0; i < RES; i++) {
			x_offset = SCREEN_WIDTH/RES+1; //2560 / 500 -1
			wave[j].points[i].x = (int)(x_offset*i); 
			wave[j].points[i].y = SCREEN_HEIGHT/2;
		}
	}
	init.sdl(&window, &renderer);
	
	while(!quit) {
		zoom = 1;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		quit = input.update();
		if (input.right_key == down) {
			time_unit += 0.0002;
			input.right_key = up;
		}
		if (input.left_key == down) {
			time_unit -= 0.0002;
			input.left_key = up;
		}
		if (input.up_key == down) { 
			zoom = 1.02;
			for (int i = 0; i < waves_amount; i++) {
				wave[i].amplitude *= zoom;
				wave[i].frequency /= zoom;
			}
			input.up_key = up;

		}
		if (input.down_key == down) {
			zoom = 1.02; 
			for (int i = 0; i < waves_amount; i++) {
				wave[i].amplitude /= zoom;
				wave[i].frequency *= zoom;
			}
			input.down_key = up;
		}

		for (int i = 0; i < waves_amount; i++) {
			wave[i].update();
		}
		for (int j = 1; j < waves_amount; j++) {
			for (int i = 0; i < RES; i++) {
				wave[j].points[i].y += wave[j-1].points[i].y;
				wave[j].points[i].y /= 2;
			}
		}
		for (int i = 0; i < waves_amount; i++) {
			wave[i].phase += time_unit;
		}
		draw.lines(wave[waves_amount-1].points, RES, renderer);
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
