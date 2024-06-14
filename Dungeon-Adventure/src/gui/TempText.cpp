#include "TempText.h"

SDL_Renderer* gui::TempText::_renderer;
gui::TempText::TempText(int x, int y, const char* text, Font* font, int maxAge, SDL_Renderer* renderer) {
	_renderer = renderer;

	_label = new gui::Label(x, y, text, font, _renderer);

	this->maxAge = maxAge;
	currentAge = 0;
}

gui::TempText::~TempText() {
	delete _label;
}

void gui::TempText::tick() {
	currentAge++;
}

void gui::TempText::render() {
	_label->render();
}
