#ifndef LAMP
#define LAMP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum class Color {
	green,
	orange,
	red
};

enum class State {
	off,
	on
};

class lamp {
	private:
		State state;
		Color color;
		int x, y;
		SDL_Texture *texture;
	public:
		std::string getColor();
		void setColor(int i); //0 = green, 1 = orange, 2 = red
		bool getState();
		void setState(State setState);
		void setCoords(int setX, int setY);
		int getX();
		int getY();
		void setTexture(SDL_Texture *setTexture);
		SDL_Texture *getTexture();
};

#endif
