#ifndef LAMP
#define LAMP

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
	public:
		Color getColor();
		State getState();
		State setState();
};

#endif
