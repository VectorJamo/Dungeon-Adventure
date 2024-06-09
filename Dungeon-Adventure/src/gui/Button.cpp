#include "Button.h"

SDL_Renderer* gui::Button::_renderer;
gui::Button::Button(int x, int y, const char* text, Font* font, SDL_Renderer* renderer) {
	this->_renderer = renderer;
	_label = new Label(x, y, text, font, renderer);
	_r = 255;
	_g = 255;
	_b = 255;
	_a = 255;
	_label->setTextColor(0, 0, 0, 255);

	_paddingX = 0;
	_paddingY = 0;

	_hasOutline = false;
	_outlineThickness = 2;
}

gui::Button::~Button() {
	delete _label;
}

void gui::Button::setPosition(int x, int y) {
	_label->setPosition(x + _paddingX, y + _paddingY);
}

void gui::Button::setFont(Font* font) {
	_label->setFont(font);
}

void gui::Button::setTextColor(char r, char g, char b, char a) {
	_label->setTextColor(r, g, b, a);
}

void gui::Button::setOutlineColor(char r, char g, char b, char a) {
	_outlineR = r;
	_outlineG = g;
	_outlineB = b;
	_outlineA = a;
	_hasOutline = true;
}

void gui::Button::setOutlineThickness(int thickness) {
	_outlineThickness = thickness;
}

void gui::Button::setColor(char r, char g, char b, char a) {
	this->_r = r;
	this->_g = g;
	this->_b = b;
	this->_a = a;
}

void gui::Button::setPaddingX(int paddingX) {
	int paddingChange = paddingX - this->_paddingX;
	this->_paddingX = paddingX;
	_label->setPosition(_label->getXPos() + paddingChange, _label->getYPos());
}

void gui::Button::setPaddingY(int paddingY) {
	int paddingChange = paddingY - this->_paddingY;
	this->_paddingY = paddingY;
	_label->setPosition(_label->getXPos(), _label->getYPos() + paddingChange);
}

void gui::Button::update(SDL_Event& ev) {
}
void gui::Button::render() {
	SDL_SetRenderDrawColor(_renderer, _r, _g, _b, _a);
	SDL_Rect rect = { _label->getXPos() - _paddingX, _label->getYPos() - _paddingY, _label->getWidth() + 2 * _paddingX, _label->getHeight() + 2 * _paddingY };
	SDL_RenderFillRect(_renderer, &rect);

	if (_hasOutline) {
		SDL_SetRenderDrawColor(_renderer, _outlineR, _outlineG, _outlineB, _outlineA);
		for (int i = _outlineThickness; i > 0; i--) {
			SDL_Rect outlineRect = { _label->getXPos() - _paddingX - i, _label->getYPos() - _paddingY - i, (_label->getWidth() + 2 * _paddingX) + 2*i, (_label->getHeight() + 2 * _paddingY) + 2*i };
			SDL_RenderDrawRect(_renderer, &outlineRect);
		}
	}

	_label->render();
}
