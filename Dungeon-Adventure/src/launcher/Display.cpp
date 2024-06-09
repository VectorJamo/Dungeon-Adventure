#include <iostream>

#include "Display.h"
#include "../utils/Macros.h"

int Display::_width;
int Display::_height;

Display::Display(int width, int height, const char* title):_window(nullptr), _renderer(nullptr), _title(title) {
	_width = width;
	_height = height;

	// Create the window object
	_window = SDL_CreateWindow(_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);
	if (_window == nullptr) {
		ASSERT_LOG("Failed to create SDL window.");
		return;
	}

	// Create the renderer object
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr) {
		ASSERT_LOG("Failed to create SDL renderer.");
		return;
	}

	// Enable alpha blending by default
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

	// Initialize SDL Subsystems
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG)) {
		ASSERT_LOG("Failed to initialize SDL Image");
		return;
	}

	if (TTF_Init() != 0) {
		ASSERT_LOG("Failed to initialize SDL TTF");
		return;
	}
}

Display::~Display() {
	// Free up the resources allocated by the renderer and window object
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Display::clear(char r, char g, char b, char a) {
	// Clear the pixel buffer
	SDL_SetRenderDrawColor(_renderer, r, g, b, a);
	SDL_RenderClear(_renderer);
}

void Display::show() {
	// Swap buffers
	SDL_RenderPresent(_renderer);
}
