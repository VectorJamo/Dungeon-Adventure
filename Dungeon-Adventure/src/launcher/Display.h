#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include  <SDL_ttf.h>

class Display {
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	static int _width, _height;
	const char* _title;

public:
	Display(int width, int height, const char* title);
	~Display();

	void clear(char r, char g, char b, char a);
	void show();

	inline static int getWidth() { return _width; }
	inline static int getHeight() { return _height; }
	inline SDL_Renderer* getRendererInstance() { return _renderer; }
};