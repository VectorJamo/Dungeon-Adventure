#include "Label.h"
#include <iostream>

namespace gui {
	Font::Font(const char* filePath, int pointSize) : _font(nullptr), _pointSize(pointSize) {
		_font = TTF_OpenFont(filePath, pointSize);
		if (_font == nullptr) {
			std::cout << "Failed to load font" << std::endl;
		}
	}

	Font::~Font() {
		TTF_CloseFont(_font);
	}


	SDL_Renderer* Label::_renderer;
	Label::Label(int x, int y, const char* text, Font* font, SDL_Renderer* renderer) : _x(x), _y(y), _width(0),
		_height(0), _labelTexture(nullptr), _text(text), _font(font) {
		_color.r = 255;
		_color.g = 255;
		_color.b = 255;
		_color.a = 255;

		this->_renderer = renderer;

		createLabelTexture();
	}

	Label::~Label() {
		SDL_DestroyTexture(_labelTexture);
	}

	void Label::createLabelTexture() {
		SDL_Surface* surface = TTF_RenderText_Blended(_font->getFontInstance(), _text, _color);
		_labelTexture = SDL_CreateTextureFromSurface(_renderer, surface);
		if (_labelTexture == nullptr) {
			std::cout << "Failed to create texture from font." << std::endl;
		}

		_width = surface->w;
		_height = surface->h;

		SDL_FreeSurface(surface);
	}

	void Label::setPosition(int x, int y) {
		this->_x = x;
		this->_y = y;
	}

	void Label::setFont(Font* font) {
		this->_font = font;
		if (_labelTexture != nullptr) {
			SDL_DestroyTexture(_labelTexture);
		}
		createLabelTexture();
	}

	void Label::setTextColor(char r, char g, char b, char a) {
		_color.r = r;
		_color.g = g;
		_color.b = b;
		_color.a = a;

		if (_labelTexture != nullptr) {
			SDL_DestroyTexture(_labelTexture);
		}
		createLabelTexture();
	}

	void Label::setText(const char* text) {
		this->_text = text;
		createLabelTexture();
	}

	void Label::render() {
		SDL_Rect dest = { _x, _y, _width, _height };
		SDL_RenderCopy(_renderer, _labelTexture, NULL, &dest);
	}
}

