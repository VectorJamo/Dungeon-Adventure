#include "TextField.h"

SDL_Renderer* gui::TextField::_renderer;
gui::TextField::TextField(int x, int y, int width, int height, Font* font, SDL_Renderer* renderer) {
	this->_renderer = renderer;
	_text = " ";
	_label = new Label(x, y, _text.c_str(), font, _renderer);
	_numCharacters = 0;

	_width = width;
	_height = height;

	isMouseOver = false;
	onFocus = false;
}

gui::TextField::~TextField() {
	delete _label;
}

void gui::TextField::setPosition(int x, int y) {
	_label->setPosition(x, y);
}

void gui::TextField::setFont(Font* font) {
	_label->setFont(font);
}

void gui::TextField::setColor(char r, char g, char b, char a) {
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}

void gui::TextField::setTextColor(char r, char g, char b, char a) {
	_label->setTextColor(r, g, b, a);
}

void gui::TextField::render() {
	SDL_SetRenderDrawColor(_renderer, _r, _g, _b, _a);
	SDL_Rect rect = { _label->getXPos() - 2, _label->getYPos() - 2, _width + 2*2, _height + 2*2 };
	SDL_RenderFillRect(_renderer, &rect);

	_label->render();
}

void gui::TextField::setText(const std::string& text) {
	this->_text = text;
	_label->setText(_text.c_str());
}


